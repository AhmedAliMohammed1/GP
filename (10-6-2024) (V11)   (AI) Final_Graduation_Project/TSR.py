import torch
import numpy as np
import cv2
# from time import time
# from ultralytics import YOLO
from serial_communication import *
import os
import supervision as sv
import serial
import time
from shared_resources import *
from sound_system import *


######################################################################################################################################

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

def load_model():
    from ultralytics import YOLO
    model = YOLO("Abdelrahman12.pt")  # load a pretrained YOLOv8n model
    model.fuse()
    return model

######################################################################################################################################

def predict(model, frame):
    results = model(frame)
    return results

######################################################################################################################################

def plot_bboxes(results, frame, CLASS_NAMES_DICT):
    class_id = 99  # if no signs detected
    xyxys = []
    confidences = []
    class_ids = []

    for result in results[0]:
        boxes = result.boxes.cpu().numpy()
        class_id = boxes.cls[0]
        conf = boxes.conf[0]
        xyxy = boxes.xyxy[0]

        xyxys.append(result.boxes.xyxy.cpu().numpy())
        confidences.append(result.boxes.conf.cpu().numpy())
        class_ids.append(result.boxes.cls.cpu().numpy().astype(int))

    detections = sv.Detections(
        xyxy=results[0].boxes.xyxy.cpu().numpy(),
        confidence=results[0].boxes.conf.cpu().numpy(),
        class_id=results[0].boxes.cls.cpu().numpy().astype(int),
    )

    labels = [f"#{class_id} {CLASS_NAMES_DICT[class_id]} {confidence:0.2f}" 
    for _, _, confidence, class_id, tracker_id in detections]

    frame = sv.BoxAnnotator(sv.ColorPalette.default(), thickness=3, text_thickness=3, text_scale=1.5).annotate(scene=frame, detections=detections, labels=labels)

    return frame, class_id

######################################################################################################################################

def TSR_ON():

 capture_index = tsr_camera[0]
    #from shared_resources import shared_ser[0] , TSR_STATUS , laptop_port , baud_rate , web_cam_id , external_cam_id , TSR_ON_FLAG , TSR_OFF_FLAG , TSR_START_OF_FRAME , TSR_END_OF_FRAME
 os.chdir(os.path.dirname(os.path.abspath(__file__)))
 TSR_COUNTER=1
 cap = cv2.VideoCapture(capture_index)
 while True:
   
  while(TSR_STATUS[0]==TSR_OFF_FLAG):
    if(TSR_COUNTER==0) :
     try:
      cap.release()
    #  cv2.destroyAllWindows()     
      cv2.destroyWindow('TSR')
    #  print("TSR OFF")
      TSR_COUNTER=1
     except :
        pass
    time.sleep(1)



  while(TSR_STATUS[0]==TSR_ON_FLAG):
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    print("Using Device: ", device)
    model = load_model()
    CLASS_NAMES_DICT = model.model.names

    cap = cv2.VideoCapture(capture_index)
    # assert cap.isOpened()
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

    counter = 0
    number_of_frames = 15

    signs_flags = [99]
    most_repeated_flag_each_n_frames = 99
    most_repeated_flag_to_sent = 99

    while True:
     while counter < number_of_frames and TSR_STATUS[0]==TSR_ON_FLAG:
        #  start_time = time()

         try:
          ret, frame = cap.read()
          frame = adjust_brightness_dynamic(frame)
          frame = cv2.resize(frame,(500,500))
          assert ret
          results = predict(model, frame)
          bboxes_return = plot_bboxes(results, frame, CLASS_NAMES_DICT)
          frame = bboxes_return[0]
          class_flag = bboxes_return[1]
        #  end_time = time()
        #  fps = 1 / np.round(end_time - start_time, 2)

        #  cv2.putText(frame, f'FPS: {int(fps)}', (20, 70), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (0, 255, 0), 2)
          cv2.imshow('TSR', frame)
          signs_flags.append(int(class_flag))
          counter += 1
          cv2.waitKey(1)
         except:
            TSR_CAMERA_FAILED_SOUND[0] = True
            GLOBAL_FLAG[0] = CAR_OFF_FLAG
            play_mp3("roadcamera.mp3")
            CAMERA_ERROR[0] = True
            time.sleep(1)
            TSR_CAMERA_FAILED_SOUND[0] = False
            time.sleep(3)
            #here sounddddd camera failed
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
            
     most_repeated_flag_each_n_frames = max(signs_flags, key=signs_flags.count)
     counter = 0
     signs_flags.clear()

     data_to_send = str(most_repeated_flag_each_n_frames)
     TSR_FLAG[0] = most_repeated_flag_each_n_frames

     try:
      shared_ser[0].write(TSR_START_OF_FRAME.encode('utf-8'))                #START OF 30 FRAME  (0x23)
      shared_ser[0].write(data_to_send.encode('utf-8'))
      shared_ser[0].write(TSR_END_OF_FRAME.encode('utf-8'))                  #END OF 30 FRAME    (0x2A)
      SERIAL_CONNECTION_IS_OK[0] = True
     except:
      SERIAL_CONNECTION_IS_OK[0] = False
      CHECK_PORT()
    #   GLOBAL_FLAG[0] = CAR_OFF_FLAG
      
     if(TSR_STATUS[0]==TSR_OFF_FLAG):
            TSR_COUNTER=0
            break

        #  TSR_STATUS[0]=TSR_ON_FLAG   #reset
        #  break


