import mediapipe as mp
import os
import cv2
from src import utils
import math
import numpy as np
from shared_resources import *
from sound_system import *
import time
from PIL import Image
os.chdir(os.path.dirname(os.path.abspath(__file__)))

capture_index = dms_camera

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

def adjust_brightness_dynamic(image):
    brightness = calculate_brightness(image)
    
    target_brightness = 130  
    
    brightness_diff = target_brightness - brightness
    
    adjusted = cv2.convertScaleAbs(image, beta=brightness_diff)
    
    return adjusted

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

def DMS_EYE_DETECTION():

    eyes_are_closed = True
    person_found    = False
    dms_counter     = 1
    dms_filter_steps = 20
    sum_of_ratios = 0
    temp_open_eyes = 0
    temp_closed_eyes = 0
    temp_force_stop = 0
    temp_no_person = 0
    dms_wait_seconds = 15 
    dms_camera_counter=0
    while True:

        time.sleep(2) 
        map_face_mesh = mp.solutions.face_mesh
        with map_face_mesh.FaceMesh(min_detection_confidence =0.5, min_tracking_confidence=0.5) as face_mesh:

            while (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG):
                if(dms_camera_counter==0):
                    camera = cv2.VideoCapture(dms_camera)
                    dms_camera_counter=1
                ret, frame = camera.read() # getting frame from camera 
                # frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                # frame = Image.fromarray(frame)
                # frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
                # frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
                # frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
                frame = adjust_brightness_dynamic(frame)
                
                if not ret: 
                    break # no more frames break
        
                frame_height, frame_width= frame.shape[:2]
                rgb_frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
                results  = face_mesh.process(rgb_frame)

                if results.multi_face_landmarks:         #eye detected

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

                cv2.imshow('frame', frame)
                cv2.waitKey(1)
                if (dms_counter == dms_filter_steps) and (person_found == True) and (eyes_are_closed == False) and (temp_open_eyes == 0):   #PERSON WITH OPEN EYES
    
                    shared_ser.write(DMS_START_OF_FRAME.encode('utf-8'))                
                    shared_ser.write(DMS_OPEN_EYES.encode('utf-8'))
                    shared_ser.write(DMS_END_OF_FRAME.encode('utf-8'))
                    #print("open eye")
                    temp_open_eyes = 1
                    temp_closed_eyes = 0
                    temp_force_stop = 0
                    temp_no_person = 0
                    dms_counter = 1

                elif (dms_counter == dms_filter_steps) and (person_found == True) and (eyes_are_closed == True) and (temp_closed_eyes == 0):   #PERSON WITH CLOSED EYES
                    
                    shared_ser.write(DMS_START_OF_FRAME.encode('utf-8'))                
                    shared_ser.write(DMS_CLOSED_EYES.encode('utf-8'))
                    shared_ser.write(DMS_END_OF_FRAME.encode('utf-8'))
                    #print("closed eye")
                    temp_closed_eyes = 1
                    temp_open_eyes = 0
                    temp_force_stop = 0
                    temp_no_person = 0
                    dms_counter = 1
                    start_time = time.time()

                elif (temp_closed_eyes == 1) and ( (time.time() - start_time) >= dms_wait_seconds) and (temp_force_stop == 0):   #PERSON WITH CLOSED EYES , check for num of seconds

                    shared_ser.write(DMS_START_OF_FRAME.encode('utf-8'))                
                    shared_ser.write(DMS_FORCE_STOP.encode('utf-8'))
                    shared_ser.write(DMS_END_OF_FRAME.encode('utf-8'))
                    #print("force stop")
                    dms_counter = 1
                    sum_of_ratios = 0
                    temp_force_stop = 1
                
                elif (dms_counter == dms_filter_steps) and (person_found == False) and (temp_no_person == 0):
                    
                    shared_ser.write(DMS_START_OF_FRAME.encode('utf-8'))                
                    shared_ser.write(DMS_NO_PERSON.encode('utf-8'))
                    shared_ser.write(DMS_END_OF_FRAME.encode('utf-8'))
                    #print("force stop")
                    temp_closed_eyes = 0
                    temp_open_eyes = 0
                    temp_force_stop = 0
                    temp_no_person = 1
                    dms_counter = 1

                elif ((dms_counter == dms_filter_steps) and (temp_force_stop == 1) and (DMS_STATUS[0] == DMS_RELEASE_ACTION)):
                    play_mp3("warning alarm.mp3")
                    time.sleep(2)
                    dms_counter = 1

                elif (dms_counter == dms_filter_steps):
                    dms_counter = 1
            if(dms_camera_counter==1):
            #  time.sleep(1) 
             camera.release()
            #  time.sleep(1) 
            #  cv2.destroyAllWindows()
             cv2.destroyWindow('frame')
            #  time.sleep(1) 
             dms_camera_counter=0
# DMS_EYE_DETECTION()