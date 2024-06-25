from deepface import DeepFace
import mediapipe as mp
import os
import datetime
import cv2
import requests
from PIL import Image
from src import utils
import math
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import load_model
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
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.edge.service import Service
from selenium.webdriver.edge.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
os.chdir(os.path.dirname(os.path.abspath(__file__)))



LEFT_EYE =[ 362, 382, 381, 380, 374, 373, 390, 249, 263, 466, 388, 387, 386, 385,384, 398 ]
LEFT_EYEBROW =[ 336, 296, 334, 293, 300, 276, 283, 282, 295, 285 ]

RIGHT_EYE=[ 33, 7, 163, 144, 145, 153, 154, 155, 133, 173, 157, 158, 159, 160, 161 , 246 ]  
RIGHT_EYEBROW=[ 70, 63, 105, 66, 107, 55, 65, 52, 53, 46 ]

#################################################################################################################

def Cameras_Initialize():


    while True:

        initial_frames = []
        
        for camera_id in range(0,MAX_NUM_OF_CAMERAS):
            cap = cv2.VideoCapture(camera_id)
            if cap.isOpened():
                ret , frame = cap.read()
                initial_frames.append(frame)
            else:
                os.system("cls")
                cap.release()
                camera_id = camera_id - 1
                break
        if(camera_id == 2):
         for index , frame in enumerate(initial_frames) :
            cv2.imshow("ID > " + str(index) , frame)
            
         cv2.waitKey(1)

        if(camera_id == 2):
        
         camera_code = input("Please enter the camera code at this sequence (road)(driver) camera ids >>>   ")
         camera_code.strip()
         initial_frames.clear()
        
         try:
            road_camera_id = int(camera_code[0])
            driver_camera_id = int(camera_code[1])

            # print(road_camera_id , driver_camera_id)
            # time.sleep(10)
            
            if (road_camera_id > camera_id) or (driver_camera_id > camera_id) or (len(camera_code) != camera_id) or (road_camera_id == driver_camera_id) :
                deliberately_go_to_exception = 5/0
                
            else:

                check_user_camera[0]        = driver_camera_id
                add_user_camera[0]          = driver_camera_id
                delete_user_camera[0]       = driver_camera_id
                tsr_camera[0]               = road_camera_id
                dms_camera[0]               = driver_camera_id
                gesture_control_camera[0]   = driver_camera_id
                cv2.destroyAllWindows()
                os.system("cls")
                break
            
         except:
            os.system("cls")
            print("\nCODE ERROR !!! PLEASE TRY AGAIN")
            time.sleep(3)

            os.system("cls")


        elif (camera_id <= 0 ):
            os.system("cls")
            print("\nNO CAMERAS ARE CONNECTED")
            time.sleep(3)

            os.system("cls")
        
        elif (camera_id == 1 ):
            os.system("cls")
            print("\nONLY 1 CAMERA IS CONNECTED")
            time.sleep(3)

            os.system("cls")

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

def GET_LIVE_LOCATION():
# Get the directory of the current script
 script_dir = os.path.dirname(os.path.abspath(__file__))

# Path to the ChromeDriver executable (assuming it's in the same directory as the script)
 driver_path = os.path.join(script_dir, 'msedgedriver.exe')


# chrome_options = Options()
# chrome_options.add_argument("--headless")  # Run in headless mode


# Set up the WebDriver
 service = Service(driver_path)
 driver = webdriver.Edge(service=service)
# driver.set_window_size(100,100)


 try:
    # Open Google Maps

    driver.get("https://www.google.com/maps")
    # print("Page title:", driver.title)

    # Wait for the page to load completely
    WebDriverWait(driver, 30).until(EC.presence_of_element_located((By.CSS_SELECTOR, 'body')))
    
#     time.sleep(20)
# # Debugging: Print all buttons to find the correct one
#     buttons = driver.find_elements(By.TAG_NAME, 'button')
#     for button in buttons:
#         print(button.get_attribute('aria-label'))
        
    # Define selectors for different languages
    selectors = {
        "English": 'button[aria-label="From your device"]',
        "Arabic": 'button[aria-label="موقعك الجغرافي"]'  # NORMAL MODE
       #"Arabic": 'button[aria-label="عرض موقعك"]'        # HEADLESS MODE 

    }

    # Determine the language and select the appropriate selector
    page_language = driver.execute_script("return document.documentElement.lang")
    # print("Page language:", page_language)

    if "ar" in page_language:
        selector = selectors["Arabic"]
    else:
        selector = selectors["English"]

    wait = WebDriverWait(driver, 60)
    my_location_button = wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, selector)))
    
    # print("Found the 'My location' button")

    # Click on the "My location" button
    my_location_button.click()
    # print("Clicked the 'My location' button")
    # Allow some time for the location to be updated
    time.sleep(5)  
    # Get the current URL
    current_url = driver.current_url

    # print("Current Location URL:", current_url)

    split_link = current_url.split("@")
    website = split_link[0] + "place/"
    geographic_coordinates = split_link[1]

    split_geographic_coordinates = geographic_coordinates.split(",")
    Latitude  = float(split_geographic_coordinates[0])
    Longitude = float(split_geographic_coordinates[1])
    Zoom      = int(float(split_geographic_coordinates[2][0:2]))

    Latitude_direction = "N"
    Longitude_direction = "E"

    if(Latitude>0):
        Latitude_direction = "N"
    elif(Latitude<0):
        Latitude_direction = "S"
        
    if(Longitude>0):
        Longitude_direction = "E"
    elif(Longitude<0):
        Longitude_direction = "W"
        
    Latitude_degrees = int(Latitude)
    Latitude_minutes = int((Latitude - Latitude_degrees) * 60)
    Latitude_seconds = (((Latitude - Latitude_degrees) * 60) - Latitude_minutes ) * 60
    
    Longitude_degrees = int(Longitude)
    Longitude_minutes = int((Longitude - Longitude_degrees) * 60)
    Longitude_seconds = (((Longitude - Longitude_degrees) * 60) - Longitude_minutes ) * 60
    
    Latitude_with_degrees  = str(Latitude_degrees) + "%C2%B0" + str(Latitude_minutes) + "%27" + str(Latitude_seconds) + '%22'
    Longitude_with_degrees = str(Longitude_degrees) + "%C2%B0" + str(Longitude_minutes) + "%27" + str(Longitude_seconds) + '%22'
    modified_url = website + Latitude_with_degrees + Latitude_direction + "+" + Longitude_with_degrees + Longitude_direction

    return modified_url , Zoom

    # print("Current Location URL:", modified_url)

 except Exception as e:
    return "NOT_FOUND" , 0
    # print(f"An error occurred: {e}")
    # Take a screenshot for debugging
    # screenshot_path = os.path.join(script_dir, 'error_screenshot.png')
    # driver.save_screenshot(screenshot_path)
    # print(f"Screenshot saved to {screenshot_path}")

 finally:
    # Close the browser
    driver.quit()


#################################################################################################################

def send_mails(sender_email , sender_password , recipient_emails , mail_subject , mail_body , attached_image_path):

    message = MIMEMultipart()
    message["From"] = sender_email
    message["To"] = ", ".join(recipient_emails)
    message["Subject"] = mail_subject

    message.attach(MIMEText(mail_body, "plain"))

    with open(attached_image_path, "rb") as attachment:
       image_part = MIMEImage(attachment.read(), name="image.jpg")
       message.attach(image_part)
    
    with smtplib.SMTP("smtp.gmail.com", 587) as server:
           server.starttls()
           server.login(sender_email, sender_password)
           text = message.as_string()
           server.sendmail(sender_email, recipient_emails, text)

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

def check_internet():
    try:
        requests.get('http://www.google.com', timeout=2)
        return True
    #except requests.ConnectionError:
    except:
        return False

#################################################################################################################

def remove_last_line():
    print("\033[F\033[K", end="")
    print("")
    print("\033[F\033[K", end="")

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

    capture_index = check_user_camera[0]
    warnings.filterwarnings('ignore')
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    real_fake_frames = 15

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

        try:

         ret, frame = cap.read()
         if flip_frames == True :
          frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
          frame = Image.fromarray(frame)
          frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
          frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
          frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
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

        except:
            return [-5],-5


    is_real = int(max(frame_label,key=frame_label.count))


    if (is_real == 1):         #real face or no faces  (no faces must be label 2 but this is bug in [.predict] function )
                               # so i will make additional analysis to differentiate between the 2 cases
        is_real = True
        # print("real one test")
        time.sleep(2)
        # if ((max(real_or_empty,key=real_or_empty.count)) > frame_npArray_threshold ):   #if no face in frame , (threshold value is based on manual tests)
        #     print("real person but no person")
        #     time.sleep(2)
        #     is_real=False

    elif(is_real == 2):
        is_real=False

    frame_label.clear()
    real_or_empty.clear()
    cap.release()

    return last_frame,is_real


#################################################################################################################

def verified_or_not(frame):
    # capture_index = check_user_camera[0]
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    unknown_driver_id = 99       
    face_id = unknown_driver_id
    collected_ids = []
    driver_names = load_names("database.txt")
    driver_name = "Driver Name : UNKNOWN"
    database_path = "database"
    name_sound = 'NONE'
    eyes_are_closed = True
    wait_frames_untill_capture = 0


    ################################################### take photo live from camera #######################################################

    # cap = cv2.VideoCapture(capture_index)

    while True:

            # ret, frame = cap.read()
            # if flip_frames == True :
            #  frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            #  frame = Image.fromarray(frame)
            #  frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
            #  frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
            #  frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
            # frame = adjust_brightness_dynamic(frame)

#frame = change_brightness(frame,BRIGHTNESS[0], 0)

            # cv2.imshow('Live Frame', frame)
            # cv2.waitKey(1) #time in ms between each frame before capture
            # wait_frames_untill_capture -=1

            if(wait_frames_untill_capture == 0 ):

                #wait_frames_untill_capture = 20    #reset
                # t1 = time.time()
                #filter1 = DeepFace.find(img_path = frame, db_path = database_path , model_name="DeepFace" , enforce_detection=False)
                filter2 = DeepFace.find(img_path = frame, db_path = database_path , model_name="Facenet512", enforce_detection=False)
                # print (time.time() - t1)
                # t1 = time.time()
                filter3 = DeepFace.find(img_path = frame, db_path = database_path , model_name="Dlib", enforce_detection=False)
                
                # print (time.time() - t1)
                # time.sleep(5)
                # t1 = time.time()
                filter4 = DeepFace.find(img_path = frame, db_path = database_path , model_name="SFace", enforce_detection=False)
                # print (time.time() - t1)
                # time.sleep(5)
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
                        # print('2  ',identity_name)

                        collected_ids.append(int((identity_name.split("-"))[0]))

                    else:
                        collected_ids.append(unknown_driver_id)
#######################################################################################################################################
                
########################################################### filter 3 result ###########################################################

                for match in filter3 :

                    if (len(match['identity']) > 0):   # to make sure that there are faces detected
                        #print("found")
                        (identity_name,ext) = os.path.splitext(os.path.basename(str(match['identity'][0])))
                        # print('3  ',identity_name)
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
                        # print('4  ',identity_name)

                        collected_ids.append(int((identity_name.split("-"))[0]))
                        
                        #time.sleep(5000)
                    else:
                        collected_ids.append(unknown_driver_id)
########################################################## get face id ###############################################################

                face_id = max(collected_ids, key=collected_ids.count)

                if (collected_ids.count(face_id)) <= 2 :  # if it repeats less than half of filters , send flag of FALSE face detection
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

    # print("eyes are ciosed" + str(eyes_are_closed))

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

#################################################################################################################

# def send_mail(mail_subject , mail_body , attached_photo_path):

#     os.chdir(os.path.dirname(os.path.abspath(__file__)))

#     sender_email = "ecotronicscrafters@gmail.com"
#     sender_password = "bdvb cidy cqdv isht"
#     recipient_emails = load_names("mails.txt")

    
# ############################################################ Email setting ##########################################################################

#     # Create the email message
#     message = MIMEMultipart()
#     message["From"] = sender_email
#     message["To"] = ", ".join(recipient_emails)
#     message["Subject"] = mail_subject

#         # Attach text to the email
#     body = mail_body
#     message.attach(MIMEText(body, "plain"))


#     # Attach image to the email
#     image_path = attached_photo_path
#     with open(image_path, "rb") as attachment:
#         image_part = MIMEImage(attachment.read(), name="image.jpg")
#         message.attach(image_part)

#     with smtplib.SMTP("smtp.gmail.com", 587) as server:
#             server.starttls()
#             server.login(sender_email, sender_password)

#             # Convert the message to a string
#             text = message.as_string()

#             # Send the email
#             server.sendmail(sender_email, recipient_emails, text,)

       

######################################################################################################################################

def HAND_GESTURE():
 gesture_frames = 20
 collected_gestures = []
 mpHands = mp.solutions.hands
 hands = mpHands.Hands(max_num_hands=1, min_detection_confidence=0.95)
 mpDraw = mp.solutions.drawing_utils

 model = load_model('mp_hand_gesture')
 f = open('gesture.names', 'r')
 classNames = f.read().split('\n')
 f.close()
 #print(classNames)

 capture_index = gesture_control_camera[0]
 cap = cv2.VideoCapture(capture_index)

 while gesture_frames > 0 :
   
    try:
     _, frame = cap.read()
     if flip_frames == True :
             frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
             frame = Image.fromarray(frame)
             frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
             frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
             frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)

     x, y, c = frame.shape

     frame = adjust_brightness_dynamic(frame)

     framergb = cv2.flip(frame, 1)
     framergb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

     result = hands.process(framergb)

     className = ''

     if result.multi_hand_landmarks:
        landmarks = []
        for handslms in result.multi_hand_landmarks:
            for lm in handslms.landmark:
                # print(id, lm)
                lmx = int(lm.x * x)
                lmy = int(lm.y * y)

                landmarks.append([lmx, lmy])

            # mpDraw.draw_landmarks(frame, handslms, mpHands.HAND_CONNECTIONS)

            prediction = model.predict([landmarks])
            os.system("cls")
            print(" CHOOSE OPTION\n (KEYBOARD)  HOLD 'a'              >> ADD USER\n (KEYBOARD)  HOLD 'd'              >> DELETE USER\n (DASHBOARD) POWER SWITCH          >> CAR ON\n")

            # print(prediction)
            classID = np.argmax(prediction)
            className = classNames[classID]
            collected_gestures.append(className)
     gesture_frames = gesture_frames -1
    #  cv2.imshow("Live Frame" , frame)
     cv2.waitKey(1)

    except:
        return "camerafailed"
 
 try:
    max_repeated_gesture = max(collected_gestures, key=collected_gestures.count)
    collected_gestures.clear()
 except:
    max_repeated_gesture = " "

#  cv2.putText(frame, className, (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 
#                    1, (0,0,255), 2, cv2.LINE_AA)

 return max_repeated_gesture

######################################################################################################################################

def CHECK_USER():

    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    unknown_driver_id = 99
    trials = 3
    USERS_FOUND[0] = False
    driver_names = load_names("database.txt")
    sender_email = "ecotronicscrafters@gmail.com"
    sender_password = "bdvb cidy cqdv isht"
    recipient_emails = load_names("mails.txt")

    for user in driver_names:
        
       if (user != "NONE"):
          
         USERS_FOUND[0] = True
         break
       

    while(trials>0):

     
     if(USERS_FOUND[0]==True):
    
      frame , real_face = real_or_fake()
      if(real_face != -5):

       frame , face_id ,  date_text , time_text , driver_name , current_datetime , name_sound , eyes_are_closed = verified_or_not(frame)


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

    #   print("real face  " + str(real_face))
    #   print("verified  " + str(verified_person))
       shown_frame = frame.copy()
       saved_frame = frame.copy()

       saved_frame = overlay_text(saved_frame , date_text , time_text , driver_name)

       mail_subject , mail_body , attached_image_path = save_data_local(face_id , saved_frame , current_datetime)

    #   print("hereee1")
       if ( check_internet() == True ):

        try:

         if(verified_person == False):

            location , map_zoom = GET_LIVE_LOCATION()

            if(map_zoom > 14):
                    mail_body = f"Attempt to unlock the car from this location\n\n{location}"

         send_mails(sender_email , sender_password , recipient_emails , mail_subject , mail_body , attached_image_path)
        
        except:
         pass

       shown_frame = overlay_emoji(shown_frame , verified_person)
    #   print("hereee2")
       cv2.imshow("Live Frame" , shown_frame)
       cv2.waitKey(3000)
       cv2.destroyAllWindows()
      #print(trials)
    #print("finish")

      else:
        return 99 , False , "camerafailed"

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
# HAND_GESTURE()