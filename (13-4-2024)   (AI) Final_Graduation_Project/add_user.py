import cv2
import time
import datetime
import os
import re
from deepface import DeepFace
from src import utils
import math
import mediapipe as mp
import numpy as np
import imutils
from src import BoundingBox
from src import f_detector
from validate_email_address import validate_email
from random import randint , choice
import string
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.base import MIMEBase
from email import encoders
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

def adjust_brightness_dynamic(image):
    brightness = calculate_brightness(image)
    
    target_brightness = 130  
    
    brightness_diff = target_brightness - brightness
    
    adjusted = cv2.convertScaleAbs(image, beta=brightness_diff)
    
    return adjusted

#################################################################################################################

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
    positions_counter = 0
    num_of_positions  = 3
    frames_counter = 0
    position_frames_taken_counter = 0
    position_frames_saved_counter = 30
    temp_saved_positions = []
    positions_text = ["please look forward to camera" ,
                      "please turn your face to the right slowly" ,
                      "please turn your face to the left slowly"]
    positions = ["frontal" , "right" , "left"]
    position = "NONE"
    eyes_are_closed = True
    driver_names = load_names("database.txt")
    recipient_emails = load_names("mails.txt")

    for user in driver_names:
       if (user != "NONE"):
          USERS_FOUND[0] = True
          break

    if(USERS_FOUND[0] == True):
     cap = cv2.VideoCapture(capture_index)
     ret, frame = cap.read()
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

     with smtplib.SMTP("smtp.gmail.com", 587) as server:
        server.starttls()
        server.login(sender_email, sender_password)

        # Convert the message to a string
        text = message.as_string()

        # Send the email
        server.sendmail(sender_email, recipient_emails, text)

     print("A verification code has already been sent to verified user mails\n")


    while(code_trials>0):
     
     if(USERS_FOUND[0] == True):
      user_code = input("Please enter the verification code : ")

     else:
      user_code = verification_code

     if(user_code == verification_code):
      code_trials = 0

      detector = f_detector.detect_face_orientation()

      camera = cv2.VideoCapture(capture_index)  # 0 corresponds to the default camera (can be changed if multiple cameras are available)

        # Open a window to show frames
      cv2.namedWindow('Camera', cv2.WINDOW_NORMAL)

      while(positions_counter < num_of_positions):

            

        # Capture frames until 'Esc' key is pressed
        #while True:
            ret, frame = camera.read()
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
            
            if (frames_counter >= 20) and (position_frames_taken_counter < 10) and (position == positions[positions_counter]) and (eyes_are_closed == False): 
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

      # Prompt for the filename in the terminal
      cv2.destroyAllWindows()
      camera.release()
      os.system('cls')
      new_username = input("\nEnter The new username >>  ")
            
      while(mail_trials>0):

                    new_username_mail = input("Enter The new username mail >>  ")

                    email_regex = re.compile(r"[^@]+@[^@]+\.[^@]+")

                    if(bool(re.match(email_regex, new_username_mail))== True):
            
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
                     #DeepFace.find(img_path = frame, db_path = database_path , model_name="Facenet512", enforce_detection=False)
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
                     if(mail_trials==0):
                        print(f"INVALID MAIL , you don't have any trials")
                     else:
                        print(f"INVALID MAIL , try again , you still have {mail_trials} trials")
                     cv2.waitKey(3000)
                     os.system('cls')
                #break           # break the while(true) of taking frames.

     else:
        code_trials-=1
        if(code_trials==0):
            print(f"WRONG CODE , you don't have any trials")
        else:
            print(f"WRONG CODE , try again , you still have {code_trials} trials")
        cv2.waitKey(3000)
        os.system('cls')
    

#############################################################################################################
# ADD_USER()