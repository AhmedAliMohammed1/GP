import mediapipe as mp
import os
import cv2
from src import utils
import math
import numpy as np
from shared_resources import *
from serial_communication import *
from sound_system import *
import time
import requests
import tensorflow as tf
from tensorflow.keras.models import load_model
from PIL import Image
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.base import MIMEBase
from email import encoders
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

def calculate_brightness(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    brightness = gray.mean()
    
    return brightness

#################################################################################################################

def load_names(filename):
    try:
        with open(filename, "r") as file:
            names = file.read().splitlines()
        return names
    except FileNotFoundError:
        return []

#################################################################################################################

def adjust_brightness_dynamic(image):
    brightness = calculate_brightness(image)
    
    target_brightness = 130  
    
    brightness_diff = target_brightness - brightness
    
    adjusted = cv2.convertScaleAbs(image, beta=brightness_diff)
    
    return adjusted

#################################################################################################################

def dms_send_mails(sender_email , sender_password , recipient_emails , mail_subject , mail_body):

    message = MIMEMultipart()
    message["From"] = sender_email
    message["To"] = ", ".join(recipient_emails)
    message["Subject"] = mail_subject

    message.attach(MIMEText(mail_body, "plain"))

    with smtplib.SMTP("smtp.gmail.com", 587) as server:
           server.starttls()
           server.login(sender_email, sender_password)
           text = message.as_string()
           server.sendmail(sender_email, recipient_emails, text)

#################################################################################################################

def check_internet():
    try:
        requests.get('http://www.google.com', timeout=2)
        return True
    #except requests.ConnectionError:
    except :
        return False

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

def DMS_EYE_DETECTION_AND_GESTURE_CONTROL():

    capture_index = dms_camera[0]


    eyes_are_closed = True
    person_found    = False
    dms_counter     = 1
    dms_filter_steps = 20
    sum_of_ratios = 0
    temp_open_eyes = 0
    temp_closed_eyes = 0
    temp_force_stop = 0
    temp_no_person = 0
    dms_wait_seconds = 5 
    dms_camera_counter=0
    gesture_counter = 20
    sender_email = "ecotronicscrafters@gmail.com"
    sender_password = "bdvb cidy cqdv isht"
    mail_subject = "SLEEPING DRIVER !!!"
    recipient_emails = load_names("mails.txt")
    collected_gestures = []
    mpHands = mp.solutions.hands
    hands = mpHands.Hands(max_num_hands=1, min_detection_confidence=0.95)
    mpDraw = mp.solutions.drawing_utils
    model = load_model('mp_hand_gesture')
    f = open('gesture.names', 'r')
    classNames = f.read().split('\n')
    f.close()

    while True:

        time.sleep(2) 
        map_face_mesh = mp.solutions.face_mesh
        with map_face_mesh.FaceMesh(min_detection_confidence =0.5, min_tracking_confidence=0.5) as face_mesh:

            while (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG):
                if(dms_camera_counter==0):
                    camera = cv2.VideoCapture(capture_index)
                    dms_camera_counter=1
                try:
                 ret, frame = camera.read() # getting frame from camera 
                 if flip_frames == True:
                  frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                  frame = Image.fromarray(frame)
                  frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
                  frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
                  frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
                 frame = adjust_brightness_dynamic(frame)
                
                 if not ret: 
                    break # no more frames break
        
                 frame_height, frame_width= frame.shape[:2]
                 rgb_frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
                 results  = face_mesh.process(rgb_frame)

                 x, y, c = frame.shape
                 frame = cv2.flip(frame, 1)
                 frame = adjust_brightness_dynamic(frame)
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
                        classID = np.argmax(prediction)
                        className = classNames[classID]
                        collected_gestures.append(className)
                        max_repeated_gesture = max(collected_gestures, key=collected_gestures.count)
                        gesture_counter = gesture_counter - 1

                
                 if (gesture_counter == 0) and (max_repeated_gesture == CAR_OFF_GESTURE):

                    try:
                        shared_ser[0].write(GESTURE_START_OF_FRAME.encode('utf-8'))               
                        shared_ser[0].write(str(GESTURE_CAR_OFF_FLAG).encode('utf-8'))
                        shared_ser[0].write(GESTURE_END_OF_FRAME.encode('utf-8')) 
                        CAR_STATUS[0] = CAR_OFF_FLAG
                        collected_gestures.clear()
                        gesture_counter = 20  #reset
                        GLOBAL_FLAG[0] = CAR_OFF_FLAG
                        SERIAL_CONNECTION_IS_OK[0] = True
                    except:
                        SERIAL_CONNECTION_IS_OK[0] = False
                        CHECK_PORT()
                        # GLOBAL_FLAG[0] = CAR_OFF_FLAG

                 elif (gesture_counter == 0) and (max_repeated_gesture != CAR_OFF_GESTURE):
                        collected_gestures.clear()
                        gesture_counter = 20  #reset

                 cv2.imshow('frame', frame)
                 cv2.waitKey(1)

                except:
                  time.sleep(3)
                  DMS_CAMERA_FAILED_SOUND[0] = True
                  GLOBAL_FLAG[0] = CAR_OFF_FLAG
                  play_mp3("drivercamera.mp3")
                  time.sleep(1)
                  DMS_CAMERA_FAILED_SOUND[0] = False
                  CAMERA_ERROR[0] = True
                  time.sleep(3)
                  try:
                        shared_ser[0].write(GESTURE_START_OF_FRAME.encode('utf-8'))               
                        shared_ser[0].write(str(GESTURE_CAR_OFF_FLAG).encode('utf-8'))
                        shared_ser[0].write(GESTURE_END_OF_FRAME.encode('utf-8')) 
                        SERIAL_CONNECTION_IS_OK[0] = True
                  except:
                        SERIAL_CONNECTION_IS_OK[0] = False
                        CHECK_PORT()
                  break
                        # GLOBAL_FLAG[0] = CAR_OFF_FLAG
                if results.multi_face_landmarks:                                         #eye detected

                    mesh_coords = landmarksDetection(frame, results, False)
                    ratio = blinkRatio(frame, mesh_coords, RIGHT_EYE, LEFT_EYE)
                    dms_counter = dms_counter + 1
                    sum_of_ratios = sum_of_ratios + ratio
                    ratio = sum_of_ratios / dms_filter_steps
                    #print(ratio)
                    #print(dms_counter)
                    #time.sleep(2)

                    

                    if (ratio > EYE_THRESHOLD) and (dms_counter == dms_filter_steps):

                         person_found    = True
                         eyes_are_closed = True
                         #dms_counter = 1
                         sum_of_ratios = 0

                    elif (ratio < EYE_THRESHOLD) and (dms_counter == dms_filter_steps):

                         person_found    = True
                         eyes_are_closed = False
                         #dms_counter = 1
                         sum_of_ratios = 0

            
                else:   # no eyes detected
                    person_found    = False
                    eyes_are_closed = True
                    dms_counter = dms_counter + 1
                    # dms_counter = 1
                    sum_of_ratios = 0

                
                if (dms_counter == dms_filter_steps) and (person_found == True) and (eyes_are_closed == False) and (temp_open_eyes == 0):   #PERSON WITH OPEN EYES

                  try:
                    shared_ser[0].write(DMS_START_OF_FRAME.encode('utf-8'))                
                    shared_ser[0].write(DMS_OPEN_EYES.encode('utf-8'))
                    shared_ser[0].write(DMS_END_OF_FRAME.encode('utf-8'))
                    #print("open eye")
                    temp_open_eyes = 1
                    temp_closed_eyes = 0
                    temp_force_stop = 0
                    temp_no_person = 0
                    dms_counter = 1
                    SLEEP_DRIVER[0] = False
                    SERIAL_CONNECTION_IS_OK[0] = True
                  except:
                    SERIAL_CONNECTION_IS_OK[0] = False
                    CHECK_PORT()
                    # GLOBAL_FLAG[0] = CAR_OFF_FLAG

                elif (dms_counter == dms_filter_steps) and (person_found == True) and (eyes_are_closed == True)  :   #PERSON WITH CLOSED EYES
                    
                  try:
                    if (temp_closed_eyes == 0):
                     shared_ser[0].write(DMS_START_OF_FRAME.encode('utf-8'))                
                     shared_ser[0].write(DMS_CLOSED_EYES.encode('utf-8'))
                     shared_ser[0].write(DMS_END_OF_FRAME.encode('utf-8'))
                     start_time = time.time()
                    #print("closed eye")
                    SLEEP_DRIVER[0] = True
                    temp_closed_eyes = 1
                    temp_open_eyes = 0
                    # temp_force_stop = 0
                    temp_no_person = 0
                    dms_counter = 1
                    
                    SERIAL_CONNECTION_IS_OK[0] = True
                    if(DMS_STATUS[0] == DMS_RELEASE_ACTION):
                        play_mp3("warning alarm.mp3")
                        time.sleep(2)
                  except:
                    SERIAL_CONNECTION_IS_OK[0] = False
                    CHECK_PORT()
                    # GLOBAL_FLAG[0] = CAR_OFF_FLAG
                
                elif (dms_counter == dms_filter_steps) and (person_found == False) and (temp_no_person == 0):
                    
                  try:
                    shared_ser[0].write(DMS_START_OF_FRAME.encode('utf-8'))                
                    shared_ser[0].write(DMS_NO_PERSON.encode('utf-8'))
                    shared_ser[0].write(DMS_END_OF_FRAME.encode('utf-8'))
                    #print("force stop")
                    temp_closed_eyes = 0
                    temp_open_eyes = 0
                    temp_force_stop = 0
                    temp_no_person = 1
                    dms_counter = 1
                    SERIAL_CONNECTION_IS_OK[0] = True
                  except:
                    SERIAL_CONNECTION_IS_OK[0] = False
                    CHECK_PORT()
                    # GLOBAL_FLAG[0] = CAR_OFF_FLAG

                elif ((dms_counter == dms_filter_steps) and (temp_force_stop == 1) and (DMS_STATUS[0] == DMS_RELEASE_ACTION)):
                    play_mp3("warning alarm.mp3")
                    time.sleep(2)
                    dms_counter = 1

                elif (dms_counter == dms_filter_steps):
                    dms_counter = 1
 
                

                if (temp_closed_eyes == 1) and ( (time.time() - start_time) >= dms_wait_seconds) and (temp_force_stop == 0):   #PERSON WITH CLOSED EYES , check for num of seconds

                 try:
                    shared_ser[0].write(DMS_START_OF_FRAME.encode('utf-8'))                
                    shared_ser[0].write(DMS_FORCE_STOP.encode('utf-8'))
                    shared_ser[0].write(DMS_END_OF_FRAME.encode('utf-8'))

                    internet_connection = check_internet()

                    if (internet_connection == True):
                        
                        location , map_zoom = GET_LIVE_LOCATION()

                        if(map_zoom > 14):

                            mail_body = f"The driver in danger\nYou can find the driver in this location\n\n{location}"
                            dms_send_mails(sender_email , sender_password , recipient_emails , mail_subject , mail_body)


                    #print("force stop")
                    dms_counter = 1
                    sum_of_ratios = 0
                    temp_force_stop = 1
                    SERIAL_CONNECTION_IS_OK[0] = True
                 except:
                    shared_ser[0].write(DMS_FORCE_STOP.encode('utf-8'))
                    SERIAL_CONNECTION_IS_OK[0] = False
                    CHECK_PORT()
                    # GLOBAL_FLAG[0] = CAR_OFF_FLAG


            if(dms_camera_counter==1):
             try:
            #  time.sleep(1) 
              camera.release()
            #  time.sleep(1) 
            #  cv2.destroyAllWindows()
              cv2.destroyWindow('frame')
            #  time.sleep(1) 
              dms_camera_counter=0

             except:
                pass
# DMS_EYE_DETECTION()