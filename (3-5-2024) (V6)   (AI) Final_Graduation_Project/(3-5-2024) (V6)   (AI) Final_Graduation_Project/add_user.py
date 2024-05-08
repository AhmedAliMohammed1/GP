import cv2
import time
import datetime
import os
import re
import requests
from pytimedinput import timedInput
from PIL import Image
from deepface import DeepFace
from src import utils
import argparse
import warnings
import math
import mediapipe as mp
import numpy as np
import imutils
from src import BoundingBox
from src import f_detector
from src.anti_spoof_predict import AntiSpoofPredict
from src.generate_patches import CropImage
from src.utility import parse_model_name
from validate_email_address import validate_email
from random import randint , choice
import string
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.base import MIMEBase
from email import encoders
from sound_system import *
from shared_resources import *
os.chdir(os.path.dirname(os.path.abspath(__file__)))
capture_index = add_user_camera
LEFT_EYE =[ 362, 382, 381, 380, 374, 373, 390, 249, 263, 466, 388, 387, 386, 385,384, 398 ]
LEFT_EYEBROW =[ 336, 296, 334, 293, 300, 276, 283, 282, 295, 285 ]

RIGHT_EYE=[ 33, 7, 163, 144, 145, 153, 154, 155, 133, 173, 157, 158, 159, 160, 161 , 246 ]  
RIGHT_EYEBROW=[ 70, 63, 105, 66, 107, 55, 65, 52, 53, 46 ]

#################################################################################################################

def landmarksDetection(img, results, draw=False):
    img_height, img_width= img.shape[:2]
    # list[(x,y), (x,y)....]
    mesh_coord = [(int(point.x * img_width), int(point.y * img_height)) for point in results.multi_face_landmarks[0].landmark]
    if draw :
        [cv2.circle(img, p, 2, (0,255,0), -1) for p in mesh_coord]
    
    # returning the list of tuples for each landmarks 
    return mesh_coord

#################################################################################################################

# Euclaidean distance 
def euclaideanDistance(point, point1):
    x, y = point
    x1, y1 = point1
    distance = math.sqrt((x1 - x)**2 + (y1 - y)**2)
    return distance

#################################################################################################################

# Blinking Ratio
def blinkRatio(img, landmarks, right_indices, left_indices):
    # Right eyes 
    # horizontal line 
    rh_right = landmarks[right_indices[0]]
    rh_left = landmarks[right_indices[8]]
    # vertical line 
    rv_top = landmarks[right_indices[12]]
    rv_bottom = landmarks[right_indices[4]]


    # LEFT_EYE 
    # horizontal line 
    lh_right = landmarks[left_indices[0]]
    lh_left = landmarks[left_indices[8]]

    # vertical line 
    lv_top = landmarks[left_indices[12]]
    lv_bottom = landmarks[left_indices[4]]

    rhDistance = euclaideanDistance(rh_right, rh_left)
    rvDistance = euclaideanDistance(rv_top, rv_bottom)

    lvDistance = euclaideanDistance(lv_top, lv_bottom)
    lhDistance = euclaideanDistance(lh_right, lh_left)

    if((rvDistance != 0) and (lvDistance != 0) ):
      reRatio = rhDistance/rvDistance
      leRatio = lhDistance/lvDistance

    ratio = (reRatio+leRatio)/2
    return ratio 

#################################################################################################################

def save_names(names, filename):
    with open(filename, "w") as file:
        for name in names:
            file.write(name + "\n")

#################################################################################################################

def load_names(filename):
    try:
        with open(filename, "r") as file:
            names = file.read().splitlines()
        return names
    except FileNotFoundError:
        return []

#################################################################################################################

def generate_random_code(length=6):
    chars=string.ascii_letters + string.digits
    return ''.join(choice(chars) for _ in range(length))

#################################################################################################################

def calculate_brightness(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    brightness = gray.mean()
    
    return brightness

#################################################################################################################

def check_internet():
    try:
        requests.get('http://www.google.com', timeout=2)
        return True
    except requests.ConnectionError:
        return False

#################################################################################################################

def adjust_brightness_dynamic(image):
    brightness = calculate_brightness(image)
    
    target_brightness = 130  
    
    brightness_diff = target_brightness - brightness
    
    adjusted = cv2.convertScaleAbs(image, beta=brightness_diff)
    
    return adjusted

#################################################################################################################


def added_user_real_or_fake(added_user_frames):

    warnings.filterwarnings('ignore')
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    frame_label = []
    real_or_empty = []
    frame_npArray_threshold = 0.01

    model_test = AntiSpoofPredict(device_id=0)  # Adjust the device_id as needed
    image_cropper = CropImage()
    model_dir = "./resources/anti_spoof_models"  # Adjust the path as needed
    device_id = 0
    
   

    for frame in added_user_frames :


        # frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        # frame = Image.fromarray(frame)
        # frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
        # frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
        # frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)

        frame = adjust_brightness_dynamic(frame)
        #frame = change_brightness(frame,BRIGHTNESS[0], 0)


        image_bbox = model_test.get_bbox(frame)
        prediction = np.zeros((1, 3))
        test_speed = 0
        for model_name in os.listdir(model_dir):
            h_input, w_input, model_type, scale = parse_model_name(model_name)
            param = {
                "org_img": frame,
                "bbox": image_bbox,
                "scale": scale,
                "out_w": w_input,
                "out_h": h_input,
                "crop": True,
            }
            if scale is None:
                param["crop"] = False
            img = image_cropper.crop(**param)
            start = time.time()
            prediction += model_test.predict(img, os.path.join(model_dir, model_name))
            test_speed += time.time()-start

            real_or_empty.append(prediction[0][2])   #to differentiate if empty image or real face


        label = np.argmax(prediction)
        value = prediction[0][label]/2

        frame_label.append(label)
        
        


    is_real = int(max(frame_label,key=frame_label.count))


    if (is_real == 1) and (frame_label.count(is_real) > 25):         #real face or no faces  (no faces must be label 2 but this is bug in [.predict] function )
                               # so i will make additional analysis to differentiate between the 2 cases
        is_real = True
       

        # if ((max(real_or_empty,key=real_or_empty.count)) > frame_npArray_threshold ):   #if no face in frame , (threshold value is based on manual tests)
        #     is_real=False
          
    
    elif (is_real == 1) and (frame_label.count(is_real) <= 25):
        is_real = False
      

    elif(is_real == 2):
        is_real=False
   

    frame_label.clear()
    real_or_empty.clear()

    return is_real


#################################################################################################################

def added_user_verified_or_not(added_user_frames):

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    unknown_driver_id = 99       
    face_id = unknown_driver_id
    collected_ids = []
    max_repeated_IDs = []
    max_repeated_id = unknown_driver_id
    database_path = "database"


    ################################################### take photo live from camera #######################################################


    for frame in added_user_frames:

            # frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            # frame = Image.fromarray(frame)
            # frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
            # frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
            # frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
            frame = adjust_brightness_dynamic(frame)

            #frame = change_brightness(frame,BRIGHTNESS[0], 0)


                #wait_frames_untill_capture = 20    #reset

            #filter1 = DeepFace.find(img_path = frame, db_path = database_path , model_name="DeepFace" , enforce_detection=False)
            filter2 = DeepFace.find(img_path = frame, db_path = database_path , model_name="Facenet512", enforce_detection=False,)
            filter3 = DeepFace.find(img_path = frame, db_path = database_path , model_name="Dlib", enforce_detection=False)
            filter4 = DeepFace.find(img_path = frame, db_path = database_path , model_name="SFace", enforce_detection=False)

########################################################### filter 1 result ###########################################################
                
            # for match in filter1 :

                #     if (len(match['identity']) > 0):   # to make sure that there are faces detected
                #         #print("found")
                #         (identity_name,ext) = os.path.splitext(os.path.basename(str(match['identity'][0])))
                #         #print('1  ',identity_name)

                #         collected_ids.append(int((identity_name.split("-"))[0]))

                #     else:
                #         collected_ids.append(unknown_driver_id)
######################################################################################################################################

########################################################### filter 2 result ###########################################################

            for match in filter2 :

                    if (len(match['identity']) > 0):   # to make sure that there are faces detected
                        #print("found")
                        (identity_name,ext) = os.path.splitext(os.path.basename(str(match['identity'][0])))
                        #print('2  ',identity_name)

                        collected_ids.append(int((identity_name.split("-"))[0]))

                    else:
                        collected_ids.append(unknown_driver_id)
#######################################################################################################################################
                
########################################################### filter 3 result ###########################################################

            for match in filter3 :

                    if (len(match['identity']) > 0):   # to make sure that there are faces detected
                        #print("found")
                        (identity_name,ext) = os.path.splitext(os.path.basename(str(match['identity'][0])))
                        #print('3  ',identity_name)
                        #time.sleep(5000)

                        collected_ids.append(int((identity_name.split("-"))[0]))

                    else:
                        collected_ids.append(unknown_driver_id)
#######################################################################################################################################

########################################################### filter 4 result ###########################################################

            for match in filter4 :

                    if (len(match['identity']) > 0):   # to make sure that there are faces detected
                        #print("found")
                        (identity_name,ext) = os.path.splitext(os.path.basename(str(match['identity'][0])))
                        #print('4  ',identity_name)

                        collected_ids.append(int((identity_name.split("-"))[0]))
                        
                        #time.sleep(5000)
                    else:
                        collected_ids.append(unknown_driver_id)
########################################################## get face id ###############################################################

            face_id = max(collected_ids, key=collected_ids.count)

            if (collected_ids.count(face_id)) <= 2 :  # if it repeats less than half of filters , send flag of FALSE face detection
                    face_id = unknown_driver_id

            collected_ids.clear()
            max_repeated_IDs.append(face_id)
                #print('f  ',face_id)
            # print(face_id)
            # time.sleep(2)

    max_repeated_id = max(max_repeated_IDs , key=max_repeated_IDs.count)

    if(max_repeated_id == unknown_driver_id):
        is_verified = False
    else:
        is_verified = True

    max_repeated_IDs.clear()
    
    return is_verified

#############################################################################################################

def ADD_USER ():

    
    USERS_FOUND[0] = False
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    sender_email = "ecotronicscrafters@gmail.com"
    sender_password = "bdvb cidy cqdv isht"
    font_size = 1
    font_color = (0, 255, 0)  # Green color
    font_thickness = 3
    font = cv2.FONT_HERSHEY_SIMPLEX
    database_path = "database"
    theft_folder = 'unknown'
    unknown_driver_id = 99
    new_username_id = unknown_driver_id
    new_username_index = 0
    verification_code = generate_random_code()
    code_trials = 3
    mail_trials = 3
    name_trials = 3
    name_is_valid = False
    positions_counter = 0
    num_of_positions  = 3
    frames_counter = 0
    position_frames_taken_counter = 0
    position_frames_saved_counter = 30
    time_out = False
    time_out_sec = 60
    internet_connection = True
    repeated_mail = False
    is_real = True
    is_verified = False
    temp_saved_positions = []
    positions_text = ["please look forward to camera" ,
                      "please turn your face to the right slowly" ,
                      "please turn your face to the left slowly"]
    positions = ["frontal" , "right" , "left"]
    position = "NONE"
    eyes_are_closed = True
    driver_names = load_names("database.txt")
    recipient_emails = load_names("mails.txt")
    instruction_sound = ["look_forward.mp3" , "turn_right.mp3" , "turn_left.mp3"]
    for user in driver_names:
       if (user != "NONE"):
          USERS_FOUND[0] = True
          break

    if(USERS_FOUND[0] == True):
     cap = cv2.VideoCapture(capture_index)
     ret, frame = cap.read()
    #  frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    #  frame = Image.fromarray(frame)
    #  frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
    #  frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
    #  frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
     frame = adjust_brightness_dynamic(frame)
     current_datetime = datetime.datetime.now()
     date_text = f"Date: {current_datetime.date().strftime('%d-%m-%Y')}"
     time_text = f"Time: {current_datetime.time().strftime('%I:%M:%S %p')}"
     cv2.putText(frame, date_text, (10, 50), font, font_size, font_color, font_thickness, cv2.LINE_AA)
     cv2.putText(frame, time_text, (10, 80), font, font_size, font_color, font_thickness, cv2.LINE_AA)
     cv2.putText(frame, "ADD USER", (int(frame.shape[1]/2) - 50, int(frame.shape[0]/2)), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2, cv2.LINE_AA)
     photo_name = 'add_user.jpg'
     unknown_photo_path = os.path.join(theft_folder, f'adduser_{current_datetime.strftime("%Y%m%d%H%M%S")}.jpg')
     cv2.imwrite(unknown_photo_path, frame)
     cv2.destroyAllWindows()
     cap.release()

     #Create the email message
     message = MIMEMultipart()
     message["From"] = sender_email
     message["To"] = ", ".join(recipient_emails)
     message["Subject"] = "ADD USER !!!"
     # Attach text to the email
     body = "Attempt to add user\nThe verification code for completion adding proecss is (" + str(verification_code) + ")"
     message.attach(MIMEText(body, "plain"))
     #Attach image to the email
     image_path = unknown_photo_path
     with open(image_path, "rb") as attachment:
        image_part = MIMEImage(attachment.read(), name="image.jpg")
        message.attach(image_part)
     
     if (check_internet() == True):

      try:

        with smtplib.SMTP("smtp.gmail.com", 587) as server:
           server.starttls()
           server.login(sender_email, sender_password)

        # Convert the message to a string
           text = message.as_string()

        # Send the email
           server.sendmail(sender_email, recipient_emails, text)   #mail_edit
        internet_connection = True

      except:
            internet_connection = False
     else:
            internet_connection = False


     if(internet_connection == True):
        os.system("cls")
        print("A verification code has already been sent to verified user mails\n")

     elif(internet_connection == False):
        os.system("cls")
        print("(OFFLINE MODE) A verification code has already been sent to your local database\n")
        with open("offline_mode.txt", "w") as file:
                file.write(verification_code)
                


    while((code_trials>0) and (time_out == False)):
     
     if(USERS_FOUND[0] == True):
      user_code , time_out = timedInput("Please enter the verification code : " , timeout= time_out_sec)

     else:
      user_code = verification_code

     if(user_code == verification_code) and (time_out == False):
      code_trials = 0

      detector = f_detector.detect_face_orientation()

      camera = cv2.VideoCapture(capture_index)  # 0 corresponds to the default camera (can be changed if multiple cameras are available)

        # Open a window to show frames
      cv2.namedWindow('Camera', cv2.WINDOW_NORMAL)

      t1 = time.time()

      while((positions_counter < num_of_positions) and (time_out == False)):

        #while True:
            ret, frame = camera.read()
            # frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            # frame = Image.fromarray(frame)
            # frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
            # frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
            # frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
            frame = adjust_brightness_dynamic(frame)
            if not ret:
                print("Error reading frame")
                break

            frame = cv2.flip(frame, 1)
            frame = imutils.resize(frame,width=720)

            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            boxes,names = detector.face_orientation(gray)

            if (len(names)>0):
                position = names[0]
            else:
                position = "NONE"
            
            #if (frames_counter < 60):
            frame2 = frame.copy()
            cv2.putText(frame,positions_text[positions_counter],(10,50),cv2.FONT_ITALIC,1,(0,255,255),2)
            #frame = BoundingBox.bounding_box(frame,boxes,names)            
            cv2.imshow('Camera', frame)
            frames_counter = frames_counter + 1

            map_face_mesh = mp.solutions.face_mesh
            with map_face_mesh.FaceMesh(min_detection_confidence =0.5, min_tracking_confidence=0.5) as face_mesh:
        
             frame_height, frame_width= frame2.shape[:2]
             rgb_frame = cv2.cvtColor(frame2, cv2.COLOR_RGB2BGR)
             results  = face_mesh.process(rgb_frame)
             if results.multi_face_landmarks:
                 mesh_coords = landmarksDetection(frame2, results, False)
                 ratio = blinkRatio(frame2, mesh_coords, RIGHT_EYE, LEFT_EYE)
            
                 #print(ratio)
                 if ratio >EYE_THRESHOLD:
                     eyes_are_closed = True
                 else:
                     eyes_are_closed = False
            
             else:
                 eyes_are_closed = True        # no eyes detected
            #time.sleep(3)
            cv2.waitKey(1)
            
            if((time.time() - t1) >= time_out_sec):

                time_out=True
                break


            if(frames_counter == 2):
                play_mp3(instruction_sound[positions_counter])
                time.sleep(2)

            # print(position_frames_taken_counter)
            if (frames_counter >= 5) and (position_frames_taken_counter < 10) and (position == positions[positions_counter]) and (eyes_are_closed == False): 
                #cv2.destroyAllWindows()
                #camera.release()
                temp_saved_positions.append(frame2)
                position_frames_taken_counter = position_frames_taken_counter + 1
                # frame2 = frame.copy()
                # frame2 = BoundingBox.bounding_box(frame2,boxes,names)
                # cv2.imshow('Camera', frame2)
                # cv2.waitKey(1)
                # time.sleep(2)
                #break
            elif (position_frames_taken_counter >= 10):
                
                frames_counter = 0
                position_frames_taken_counter = 0
                positions_counter = positions_counter+1
                t1 = time.time()   #reset
                play_mp3("take_shot.mp3")
                time.sleep(1)

      # Prompt for the filename in the terminal
      cv2.destroyAllWindows()
      camera.release()
      os.system('cls')


      if (time_out == False):
        
        is_real = added_user_real_or_fake(temp_saved_positions)
        if(is_real == True) and (USERS_FOUND[0]==True):
            is_verified = added_user_verified_or_not(temp_saved_positions[0:10])
        elif(is_real == True) and (USERS_FOUND[0]==False) :
            is_verified = False
        elif(is_real == False):
            is_verified = False

      while (name_trials > 0) and (time_out == False) and (is_verified== False) and (is_real == True) : #the added user mustn't be added before (not in database before)
         os.system('cls')
         new_username , time_out = timedInput("\nEnter The new username >>  " , timeout=time_out_sec)
         new_username = new_username.title()

         if (time_out == False) and (new_username.isspace() == False) and (new_username != "") and (new_username.startswith(" ") == False):
            name_trials  = 0
            name_is_valid = True
            break
         
         elif (time_out == False) and ( (new_username.isspace() == True) or (new_username == "") or (new_username.startswith(" ") == True) ):
            name_trials = name_trials - 1
            os.system("cls")
            if(name_trials == 0):
             os.system("cls")
             print(f"\nINVALID NAME !! , YOU DON'T HAVE ANY trials")
             time.sleep(5)
            else:
             print(f"\nINVALID NAME !! , YOU STILL HAVE {name_trials} trials")
             time.sleep(5)
         
         
         os.system("cls")

            
      while((mail_trials>0) and (time_out == False) and (name_is_valid == True) and (is_verified== False) and (is_real == True)):

                   new_username_mail , time_out = timedInput("Enter The new username mail >>  " , timeout= time_out_sec)

                   new_username_mail = new_username_mail.strip().lower()

                   if (time_out == False):

                    for mail in recipient_emails:
                        
                        mail.strip().lower()

                        if (new_username_mail == mail):
                            repeated_mail = True
                            break
                        else:
                            repeated_mail = False

                    email_regex = re.compile(r"[^@]+@[^@]+\.[^@]+")

                    if(bool(re.match(email_regex, new_username_mail))== True) and (repeated_mail == False):
            
                     for index , name in enumerate(driver_names):   #find the empty index
                         if(name == 'NONE'):
                             new_username_index = index
                             break
                         new_username_index = new_username_index+1
        
                     new_username_id = new_username_index + 1

                     if(new_username_index == len(driver_names)):  # to avoid out of range
                        driver_names.append(new_username)
                        recipient_emails.append(new_username_mail)
                     else:
                        driver_names[new_username_index] = new_username
                        recipient_emails[new_username_index] = new_username_mail

                     save_names(driver_names,"database.txt")
                     save_names(recipient_emails,"mails.txt")
                     mail_trials = 0


                     while (position_frames_saved_counter > 0):
                        path = database_path  
                        #full_path = f"{path}/{str(new_username_id)+-+str(positions_counter)}.jpg"
                        full_path = f"{path}/{new_username_id}-{position_frames_saved_counter}.jpg"

                        cv2.imwrite(full_path, temp_saved_positions[position_frames_saved_counter-1])

                        position_frames_saved_counter = position_frames_saved_counter - 1

                     os.system('cls')
                     #frame = temp_saved_positions[0]
                     #DeepFace.find(img_path = frame, db_path = database_path , model_name="DeepFace" , enforce_detection=False)
                     DeepFace.find(img_path = frame, db_path = database_path , model_name="Facenet512", enforce_detection=False)
                     DeepFace.find(img_path = frame, db_path = database_path , model_name="Dlib", enforce_detection=False)
                     DeepFace.find(img_path = frame, db_path = database_path , model_name="SFace", enforce_detection=False)
                     os.system('cls')
                     print(f"\n{new_username} is added successfully\nYour ID is {new_username_id}")
                     save_names(driver_names,"database.txt")
                     save_names(recipient_emails,"mails.txt")
                     mail_trials = 0
                     cv2.waitKey(3000)
                     os.system('cls')

                        #break
                     #else:
                      #  print("Snapshot not saved. Please provide a valid filename.")
                        #break

                    else:
                     mail_trials-=1
                     os.system("cls")

                     if(repeated_mail == True):
                        
                        print("\n SORRY! THIS MAIL WAS ADDED BEFORE ")

                     if(mail_trials==0):
                        
                        print(f"\n INVALID MAIL , you don't have any trials")
                     else:
                        
                        print(f"\n INVALID MAIL , try again , you still have {mail_trials} trials")
                     cv2.waitKey(5000)
                     os.system('cls')
                #break           # break the while(true) of taking frames.

     elif (time_out == False):
        code_trials-=1
        if(code_trials==0):
            os.system("cls")
            print(f"WRONG CODE , you don't have any trials")
        elif(time_out == True):
            break
        else:
            os.system("cls")
            print(f"WRONG CODE , try again , you still have {code_trials} trials")
        cv2.waitKey(3000)
        os.system('cls')
    
    if (internet_connection == False):  #no internet connection
        with open("offline_mode.txt", "w") as file:
            file.write("")
        internet_connection = True  #reset
    
    if (time_out == True):  #time out happened
        os.system('cls')
        print("\n TIME OUT !\n")
        time.sleep(3)
        os.system('cls')
        time_out = False  #reset

    elif (is_verified == True) and (is_real== True):  #repeated user
        os.system('cls')
        print("\n SORRY! THIS USER WAS ADDED BEFORE \n")
        time.sleep(3)
        os.system('cls')
        is_verified = False  #reset

    elif (is_real== False)  and (time_out == False):  #repeated user
        os.system('cls')
        print("\n SORRY! THIS USER IS FAKE \n")
        time.sleep(3)
        os.system('cls')
        is_verified = False  #reset

#############################################################################################################
# ADD_USER()