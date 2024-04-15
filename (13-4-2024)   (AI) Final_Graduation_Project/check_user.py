from deepface import DeepFace
import mediapipe as mp
import os
import datetime
import cv2
from src import utils
import math
import numpy as np
import argparse
import warnings
import time
from src.anti_spoof_predict import AntiSpoofPredict
from src.generate_patches import CropImage
from src.utility import parse_model_name
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.base import MIMEBase
from email import encoders
from shared_resources import *

capture_index = check_user_camera

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

def change_brightness(image, alpha, beta):

    new_image = cv2.convertScaleAbs(image, alpha=alpha, beta=beta)
    return new_image

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

def overlay_emoji(frame , verified_person):

    if verified_person == True:   #TRUE (REAL)
        emoji_image = "smile.png"
    else:         #FALSE (FAKE | EMPTY)
        emoji_image = "angry.png"

    emoji = cv2.imread(emoji_image, cv2.IMREAD_UNCHANGED)

    # Check if the emoji image is loaded successfully
    if emoji is None:
        print(f"Error: Unable to load emoji image '{emoji_image}'")
        return

    h, w, channels = emoji.shape

    # Resize emoji to be larger and centered in the frame
    target_size = (frame.shape[0] // 2, frame.shape[1] // 2)
    emoji_resized = cv2.resize(emoji, target_size)

    # If the emoji has an alpha channel, use it; otherwise, use a constant alpha value
    if channels == 4:
        alpha_channel = emoji_resized[:, :, 3] / 255.0
    else:
        alpha_channel = 0.5  # Default alpha value

    # Calculate position to center the emoji in the frame
    y = (frame.shape[0] - emoji_resized.shape[0]) // 2
    x = (frame.shape[1] - emoji_resized.shape[1]) // 2

    # Overlay emoji on the frame at the calculated position
    rows, cols, _ = emoji_resized.shape
    roi = frame[y:y + rows, x:x + cols]

    # Ensure both arrays have the same shape before overlaying
    emoji_resized_rgb = emoji_resized[:, :, :3]

    # Convert alpha_channel to 3 channels if it is a NumPy array
    if isinstance(alpha_channel, np.ndarray) and len(alpha_channel.shape) == 2:
        alpha_channel = alpha_channel[:, :, np.newaxis]

    overlay = (1 - alpha_channel) * roi + alpha_channel * emoji_resized_rgb

    frame[y:y + rows, x:x + cols] = overlay.astype(np.uint8)

    return frame

#################################################################################################################

def real_or_fake():

    warnings.filterwarnings('ignore')
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    real_fake_frames = 20

    frame_label = []
    real_or_empty = []
    frame_npArray_threshold = 0.01

    model_test = AntiSpoofPredict(device_id=0)  # Adjust the device_id as needed
    image_cropper = CropImage()
    model_dir = "./resources/anti_spoof_models"  # Adjust the path as needed
    device_id = 0
    
    cap = cv2.VideoCapture(capture_index)  # You may need to adjust the camera index (0 or 1) based on your setup
    frame_count = 0
    last_frame = None
    show_emoji = False

    while frame_count < real_fake_frames :
        ret, frame = cap.read()

        frame = adjust_brightness_dynamic(frame)
        #frame = change_brightness(frame,BRIGHTNESS[0], 0)


        if not ret:
            print("Failed to capture frame.")
            break

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

        frame_count += 1

        label = np.argmax(prediction)
        value = prediction[0][label]/2

        frame_label.append(label)

        cv2.imshow("Live Frame", frame)
        last_frame = frame.copy()  # Save a copy of the current frame

        cv2.waitKey(1)


    is_real = int(max(frame_label,key=frame_label.count))


    if (is_real == 1):         #real face or no faces  (no faces must be label 2 but this is bug in [.predict] function )
                               # so i will make additional analysis to differentiate between the 2 cases
        is_real = True

        if ((max(real_or_empty,key=real_or_empty.count)) > frame_npArray_threshold ):   #if no face in frame , (threshold value is based on manual tests)
            is_real=False

    elif(is_real == 2):
        is_real=False

    frame_label.clear()
    real_or_empty.clear()
    cap.release()

    return last_frame,is_real


#################################################################################################################

def verified_or_not():

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    unknown_driver_id = 99       
    face_id = unknown_driver_id
    collected_ids = []
    driver_names = load_names("database.txt")
    driver_name = "Driver Name : UNKNOWN"
    database_path = "database"
    name_sound = 'NONE'
    eyes_are_closed = True
    wait_frames_untill_capture = 10


    ################################################### take photo live from camera #######################################################

    cap = cv2.VideoCapture(capture_index)

    while True:

            ret, frame = cap.read()

            frame = adjust_brightness_dynamic(frame)

            #frame = change_brightness(frame,BRIGHTNESS[0], 0)

            cv2.imshow('Live Frame', frame)
            cv2.waitKey(1) #time in ms between each frame before capture
            wait_frames_untill_capture -=1

            if(wait_frames_untill_capture == 0 ):

                #wait_frames_untill_capture = 20    #reset

                # filter1 = DeepFace.find(img_path = frame, db_path = database_path , model_name="DeepFace" , enforce_detection=False)
                # filter2 = DeepFace.find(img_path = frame, db_path = database_path , model_name="Facenet512", enforce_detection=False)
                filter3 = DeepFace.find(img_path = frame, db_path = database_path , model_name="Dlib", enforce_detection=False)
                filter4 = DeepFace.find(img_path = frame, db_path = database_path , model_name="SFace", enforce_detection=False)

# ########################################################### filter 1 result ###########################################################
                
#                 for match in filter1 :

#                     if (len(match['identity']) > 0):   # to make sure that there are faces detected
#                         #print("found")
#                         (identity_name,ext) = os.path.splitext(os.path.basename(str(match['identity'][0])))
#                         #print('1  ',identity_name)

#                         collected_ids.append(int((identity_name.split("-"))[0]))

#                     else:
#                         collected_ids.append(unknown_driver_id)
#######################################################################################################################################

# ########################################################### filter 2 result ###########################################################

#                 for match in filter2 :

#                     if (len(match['identity']) > 0):   # to make sure that there are faces detected
#                         #print("found")
#                         (identity_name,ext) = os.path.splitext(os.path.basename(str(match['identity'][0])))
#                         #print('2  ',identity_name)

#                         collected_ids.append(int((identity_name.split("-"))[0]))

#                     else:
#                         collected_ids.append(unknown_driver_id)
# #######################################################################################################################################
                
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

                if (collected_ids.count(face_id)) < 2 :  # if it repeats less than half of filters , send flag of FALSE face detection
                    face_id = unknown_driver_id

                collected_ids.clear()
                #print('f  ',face_id)

                if(face_id != unknown_driver_id):  #verified user
                    driver_name = "Driver Name : " + driver_names[face_id - 1]
                    name_sound = driver_names[face_id - 1]


########################################################## calculate time , date of captured photo ###############################################################

                current_datetime = datetime.datetime.now()
                date_text = f"Date: {current_datetime.date().strftime('%d-%m-%Y')}"
                time_text = f"Time: {current_datetime.time().strftime('%I:%M:%S %p')}"
                break  #while true

    map_face_mesh = mp.solutions.face_mesh
    with map_face_mesh.FaceMesh(min_detection_confidence =0.5, min_tracking_confidence=0.5) as face_mesh:
        
        frame_height, frame_width= frame.shape[:2]
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
        results  = face_mesh.process(rgb_frame)
        if results.multi_face_landmarks:
            mesh_coords = landmarksDetection(frame, results, False)
            ratio = blinkRatio(frame, mesh_coords, RIGHT_EYE, LEFT_EYE)
            
            #print(ratio)
            if ratio >EYE_THRESHOLD:
                eyes_are_closed = True
            else:
                eyes_are_closed = False
            
        else:
            eyes_are_closed = True        # no eyes detected


    return frame , face_id ,  date_text , time_text , driver_name , current_datetime , name_sound , eyes_are_closed

#################################################################################################################

def overlay_text(frame , date_text , time_text , driver_name):

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    font_size = 1
    font_color = (0, 255, 0)  # Green color
    font_thickness = 3
    font = cv2.FONT_HERSHEY_SIMPLEX

    cv2.putText(frame, date_text, (10, 50), font, font_size, font_color, font_thickness, cv2.LINE_AA)
    cv2.putText(frame, time_text, (10, 80), font, font_size, font_color, font_thickness, cv2.LINE_AA)
    cv2.putText(frame, driver_name, (10, 110), font, font_size, font_color, font_thickness, cv2.LINE_AA)

    return frame


#################################################################################################################

def save_data_local(face_id , frame , current_datetime):

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    unknown_driver_id = 99       
    collected_ids = []
    driver_names = load_names("database.txt")
    recipient_emails = load_names("mails.txt")
    database_path = "database"
    drivers_folder = 'drivers'
    theft_folder = 'unknown'

    if(face_id == unknown_driver_id):   #unverified

                    photo_name = 'unknown.jpg'
                    unknown_photo_path = os.path.join(theft_folder, f'unknown_{current_datetime.strftime("%Y%m%d%H%M%S")}.jpg')
                    cv2.imwrite(unknown_photo_path, frame)

                    mail_subject = "CAR ALERT !!!"
                    mail_body = "Attempt to unlock the car"
                    attached_photo_path = unknown_photo_path

    else:  #verified

                    photo_name = 'driver.jpg'
                    driver_photo_path = os.path.join(drivers_folder, f'driver_{current_datetime.strftime("%Y%m%d%H%M%S")}.jpg')
                    cv2.imwrite(driver_photo_path, frame)
                    mail_subject = "CAR ALERT !!!"
                    mail_body = "Attempt to unlock the car"
                    attached_photo_path = driver_photo_path

    return mail_subject , mail_body , attached_photo_path

    ######################################################################################################################################



#################################################################################################################

def send_mail(mail_subject , mail_body , attached_photo_path):

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    sender_email = "ecotronicscrafters@gmail.com"
    sender_password = "bdvb cidy cqdv isht"
    recipient_emails = load_names("mails.txt")

    
############################################################ Email setting ##########################################################################

    # Create the email message
    message = MIMEMultipart()
    message["From"] = sender_email
    message["To"] = ", ".join(recipient_emails)
    message["Subject"] = mail_subject

        # Attach text to the email
    body = mail_body
    message.attach(MIMEText(body, "plain"))


    # Attach image to the email
    image_path = attached_photo_path
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

       

######################################################################################################################################


def CHECK_USER():

    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    unknown_driver_id = 99
    trials = 3
    USERS_FOUND[0] = False
    driver_names = load_names("database.txt")

    for user in driver_names:
        
       if (user != "NONE"):
          
         USERS_FOUND[0] = True
         break
       

    while(trials>0):

     
     if(USERS_FOUND[0]==True):
    
      frame , real_face = real_or_fake()
      frame , face_id ,  date_text , time_text , driver_name , current_datetime , name_sound , eyes_are_closed = verified_or_not()


      if (real_face == True):  #REAL
        
          if ((face_id == unknown_driver_id) or (eyes_are_closed == True)):   #unverified
              verified_person = False
              trials-=1
          else :                                #verified
              verified_person = True
              trials=0

      elif(real_face == False):  #FAKE
          trials-=1
          face_id = unknown_driver_id
          driver_name = "Driver Name : UNKNOWN"
          verified_person = False
    
      shown_frame = frame.copy()
      saved_frame = frame.copy()

      saved_frame = overlay_text(saved_frame , date_text , time_text , driver_name)

      mail_subject , mail_body , attached_photo_path = save_data_local(face_id , saved_frame , current_datetime)

      #send_mail(mail_subject , mail_body , attached_photo_path)

      shown_frame = overlay_emoji(shown_frame , verified_person)

      cv2.imshow("Live Frame" , shown_frame)
      cv2.waitKey(3000)
      cv2.destroyAllWindows()
      #print(trials)
    #print("finish")
     else:
         face_id = unknown_driver_id
         verified_person = False
         name_sound = "NONE"
         os.system("cls")
         print("\nNO USERS FOUND")
         time.sleep(3)
         os.system("cls")
         break
         
    return face_id , verified_person , name_sound


# CHECK_USER()