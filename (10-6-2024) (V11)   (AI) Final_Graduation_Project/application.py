from add_user import *
from delete_user import *
from check_user import *
from serial_communication import *
#from shared_resources import baud_rate , laptop_port , CAR_STATUS , DMS_STATUS , ADD_USER_IS_ON , DELETE_USER_IS_ON , CAR_ON_FLAG , CAR_OFF_FLAG , FACE_ID_START_OF_FRAME , FACE_ID_END_OF_FRAME , DMS_TAKE_ACTION , DMS_RELEASE_ACTION , TSR_ON_FLAG , TSR_OFF_FLAG , ADD_USER_OPTION_FLAG , DELETE_USER_OPTION_FLAG
from shared_resources import *
from sound_system import *
from TSR import *
from DMS import *
import keyboard
import threading
import time
from random import randint , choice
import string
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.base import MIMEBase
from email import encoders
os.chdir(os.path.dirname(os.path.abspath(__file__)))


#####################################################################################################################################

def FINAL_GRADUATION_PROJECT():
 
 sender_email = "ecotronicscrafters@gmail.com"
 sender_password = "bdvb cidy cqdv isht"
 mail_subject = "CAR GUEST !!!"
 recipient_emails = load_names("mails.txt")
 theft_folder = 'unknown'
 time_out_sec = 60
 verified_guest_id = 98
 unknown_driver_id = 99
 guest_id = unknown_driver_id
 driver_name = "unknown"
 font_size = 1
 font_color = (0, 255, 0)  # Green color
 font_thickness = 3
 font = cv2.FONT_HERSHEY_SIMPLEX
 driver_names = load_names("database.txt")
 USERS_FOUND[0] = False

#####################################################################################################################################

 TSR_THREAD                            = threading.Thread(target=TSR_ON)                                 # put TSR algorithm in independent task 
 RECEIVE_GLOBAL_FLAG_THREAD            = threading.Thread(target=RECEIVE_GLOBAL_FLAG)                    # put RECEIVE_GLOBAL_FLAG algorithm in independent task 
 CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD = threading.Thread(target=CONFIGURE_RECEIVED_GLOBAL_FLAG)         # put CONFIGURE_RECEIVED_GLOBAL_FLAG algorithm in independent task 
 SOUND_STSYTEM_THREAD                  = threading.Thread(target=SOUND_ON)                               # put SOUND_STSYTEM algorithm in independent task 
 DMS_EYE_DETECTION_THREAD              = threading.Thread(target=DMS_EYE_DETECTION_AND_GESTURE_CONTROL)  # put DMS_EYE_DETECTION_AND_GESTURE_CONTROL algorithm in independent task 
#  VOICE_CONTROL_THREAD                  = threading.Thread(target=OFFLINE_VOICE_CONTROL)                # put VOICE_CONTROL algorithm in independent task 

 Cameras_Initialize()
 CHECK_PORT()

 RECEIVE_GLOBAL_FLAG_THREAD.start()                                                # run 24 hours (run at background and won't stop at all)
 time.sleep(2)
 CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD.start()                                     # run 24 hours (run at background and won't stop at all)
 time.sleep(2)
 TSR_THREAD.start()                                                    # start TSR task (run at background)
 time.sleep(2)
 SOUND_STSYTEM_THREAD.start()                                          # start SOUND task (run at background)
 time.sleep(2) 
 DMS_EYE_DETECTION_THREAD.start()
 time.sleep(3) 
#  VOICE_CONTROL_THREAD.start()
#  time.sleep(55) 


#  START_SYSTEM[0]      =        0
#  GLOBAL_FLAG[0]       =        0
#  TSR_STATUS[0]        =        TSR_ON_FLAG
#  CAR_STATUS[0]        =        CAR_OFF_FLAG
#  DMS_STATUS[0]        =        DMS_TAKE_ACTION
#  ADD_USER_IS_ON[0]    =        False
#  DELETE_USER_IS_ON[0] =        False
#  TSR_FLAG[0]          =        99
#  CAR_IS_ON[0]         =        False 
#  if keyboard.is_pressed('a'):                                                      # only to initialize this func and avoid its initial delay
#     os.system('cls')              


 while True :
    
                                                                        # super loop for all system

     if(START_SYSTEM[0] == 0):            # TO SHOW THE OPTIONS ONLY AT INITIALIZATION OF SYSTEM

        CHECK_PORT()
        USERS_FOUND[0] = False
        internet_connection = True
        time_out = False
        code_trials = 3
        verified_person = False
        verification_code = generate_random_code()
        mail_body = "Attempt to unlock the car by a guest\nThe verification code for completion logging in proecss is (" + str(verification_code) + ")"
        driver_names = load_names("database.txt")
    
        for user in driver_names:
            if (user != "NONE"):
                USERS_FOUND[0] = True
                break                                                         

    #   TSR_THREAD                            = threading.Thread(target=TSR_ON)                               # put TSR algorithm in independent task 
    #   RECEIVE_GLOBAL_FLAG_THREAD            = threading.Thread(target=RECEIVE_GLOBAL_FLAG)                  # put RECEIVE_GLOBAL_FLAG algorithm in independent task 
    #   CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD = threading.Thread(target=CONFIGURE_RECEIVED_GLOBAL_FLAG)       # put CONFIGURE_RECEIVED_GLOBAL_FLAG algorithm in independent task 
    #   SOUND_STSYTEM_THREAD                  = threading.Thread(target=SOUND_ON)                             # put SOUND_STSYTEM algorithm in independent task 


    #   RECEIVE_GLOBAL_FLAG_THREAD.start()                                                # run 24 hours (run at background and won't stop at all)
    #   time.sleep(2)
    #   CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD.start()                                     # run 24 hours (run at background and won't stop at all)
        # time.sleep(5)
        os.system('cls')
        print(" CHOOSE OPTION\n (KEYBOARD)  HOLD 'a'              >> ADD USER\n (KEYBOARD)  HOLD 'd'              >> DELETE USER\n (DASHBOARD) POWER SWITCH          >> CAR ON\n")
        START_SYSTEM[0] = 1                                                          # PREVENT OPTIONS TO BE PRINTED MORE THAN ONCE                                                  

        
     gesture_class = HAND_GESTURE()
    #  gesture_class = "none"

     CHECK_PORT()


     if(CAMERA_ERROR[0] == True):
        Cameras_Initialize()
        START_SYSTEM[0] = 0
        CAMERA_ERROR[0] = False
        continue    #back to the beginning of the super loop again


     if(gesture_class == "camerafailed"):
        START_SYSTEM[0] = 0
        play_mp3("drivercamera.mp3")
        CAMERA_ERROR[0] = True
        time.sleep(1)

        continue    #back to the beginning of the super loop again
     

     if keyboard.is_pressed('a') or gesture_class == ADD_GESTURE: 
            ADD_USER_IS_ON[0] = True
    
     elif keyboard.is_pressed('d') or gesture_class == DELETE_GESTURE:  
            DELETE_USER_IS_ON[0] = True 


     if (ADD_USER_IS_ON[0] == True) :                                                  # Check if the 'a' key is pressed
         CHECK_PORT()
         START_SYSTEM[0] = 0                                                       # RESET THIS VARIABLE TO SHOW OPTIONS AGAIN
         os.system('cls')
         print("\n PLEASE WAIT FOR ADDING PROCESS ......\n\n")                                                  # to stop check user to be on (recieve car on flag) while add user is on
         ADD_USER()
         ADD_USER_IS_ON[0] = False
        #  BLOCK_VOICE[0] = False  


     elif (DELETE_USER_IS_ON[0] == True):                                                # Check if the 'd' key is pressed
         CHECK_PORT()
         START_SYSTEM[0] = 0                                                       # RESET THIS VARIABLE TO SHOW OPTIONS AGAIN
         DELETE_USER_IS_ON[0] = True
         os.system('cls')
         print("\n PLEASE WAIT FOR DELETING PROCESS ......\n\n")                                                 # to stop check user to be on (recieve car on flag) while add user is on
         DELETE_USER()
         DELETE_USER_IS_ON[0] = False                                              # reset after finish deleting
        #  BLOCK_VOICE[0] = False 


     elif (CAR_STATUS[0] == CAR_ON_FLAG or gesture_class == CAR_ON_GESTURE):

        CHECK_PORT()
        # print("passssssssssss")

        if (gesture_class == CAR_ON_GESTURE):

            CAR_STATUS[0] = CAR_ON_FLAG
            GLOBAL_FLAG[0] = CAR_ON_FLAG
            driver_name = "As a guest"

            try:
              shared_ser[0].write(GESTURE_START_OF_FRAME.encode('utf-8'))               
              shared_ser[0].write(str(GESTURE_CAR_ON_FLAG).encode('utf-8'))
              shared_ser[0].write(GESTURE_END_OF_FRAME.encode('utf-8'))

              SERIAL_CONNECTION_IS_OK[0] = True

            except:
                # GLOBAL_FLAG[0] = CAR_OFF_FLAG
                CHECK_PORT()
                SERIAL_CONNECTION_IS_OK[0] = False
                
            if (SERIAL_CONNECTION_IS_OK[0] == True):

             capture_index = check_user_camera[0]
             try:
              cap = cv2.VideoCapture(capture_index)
             
              ret, frame = cap.read()

              if flip_frames == True :
                frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                frame = Image.fromarray(frame)
                frame = frame.transpose(Image.FLIP_TOP_BOTTOM)
                frame = frame.transpose(Image.FLIP_LEFT_RIGHT)
                frame = cv2.cvtColor(np.array(frame), cv2.COLOR_RGB2BGR)
                
              frame = adjust_brightness_dynamic(frame)

              current_datetime = datetime.datetime.now()
              date_text = f"Date: {current_datetime.date().strftime('%d-%m-%Y')}"
              time_text = f"Time: {current_datetime.time().strftime('%I:%M:%S %p')}"
              cv2.putText(frame, date_text, (10, 50), font, font_size, font_color, font_thickness, cv2.LINE_AA)
              cv2.putText(frame, time_text, (10, 80), font, font_size, font_color, font_thickness, cv2.LINE_AA)
              cv2.putText(frame, "GUEST", (10, 130), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2, cv2.LINE_AA)
              photo_name = 'unknown.jpg'
              unknown_photo_path = os.path.join(theft_folder, f'unknown_{current_datetime.strftime("%Y%m%d%H%M%S")}.jpg')
              attached_image_path = unknown_photo_path
              cv2.imwrite(unknown_photo_path, frame)
              cv2.destroyAllWindows()
              cap.release()
             except:
                  
                  play_mp3("drivercamera.mp3")
                  CAMERA_ERROR[0] = True
                  time.sleep(1)
                  GLOBAL_FLAG[0] = CAR_OFF_FLAG
                  START_SYSTEM[0] = 0
                  try:
                        shared_ser[0].write(GESTURE_START_OF_FRAME.encode('utf-8'))               
                        shared_ser[0].write(str(GESTURE_CAR_OFF_FLAG).encode('utf-8'))
                        shared_ser[0].write(GESTURE_END_OF_FRAME.encode('utf-8')) 
                        SERIAL_CONNECTION_IS_OK[0] = True
                        continue
                  except:
                        SERIAL_CONNECTION_IS_OK[0] = False
                        CHECK_PORT()
                        continue
             
        
             if (check_internet() == True) and (USERS_FOUND[0] == True):
                
                try:
                    location , map_zoom = GET_LIVE_LOCATION()
                    if(map_zoom > 14):
                                 mail_body = f"Attempt to unlock the car by a guest from this location\n\n {location}\n\nThe verification code for completion logging in proecss is (" + str(verification_code) + ")"
                    
                    send_mails(sender_email , sender_password , recipient_emails , mail_subject , mail_body , attached_image_path)
                    internet_connection = True
                except:
                    internet_connection = False
                    
             else:
                internet_connection = False
    
                
             os.system("cls")

             if(internet_connection == True):
                print("A verification code has already been sent to verified user mails\n")
                
             elif(internet_connection == False):
                print("(OFFLINE MODE) A verification code has already been sent to your local database\n")
                with open("offline_mode.txt", "w") as file:
                    file.write(verification_code)
            
             while((code_trials>0) and (time_out == False)):

                user_code , time_out = time_out_input("Please enter the verification code : " , timeout= time_out_sec)
                
                if(user_code == verification_code) and (time_out == False):
                    verified_person = True
                    guest_id = verified_guest_id
                    code_trials = 0
                    os.system("cls")

                elif (time_out == False):
                    guest_id = unknown_driver_id
                    verified_person = False
                    code_trials-=1
                    if(code_trials==0):
                        os.system("cls")
                        print(f"WRONG CODE , you don't have any trials")
                    else:
                        os.system("cls")
                        print(f"WRONG CODE , try again , you still have {code_trials} trials")
                    cv2.waitKey(3000)
                    os.system('cls')

             if (time_out == True):  #time out happened
                guest_id = unknown_driver_id
                verified_person = False
                os.system('cls')
                print("\n TIME OUT !\n")
                cv2.waitKey(3000)
                os.system('cls')
                time_out = False  #reset

             if (internet_connection == False):  #no internet connection
                with open("offline_mode.txt", "w") as file:
                    file.write("")
                    internet_connection = True  #reset

             try:
               SEND_FACE_ID(guest_id)
               SERIAL_CONNECTION_IS_OK[0] = True
             except:
               SERIAL_CONNECTION_IS_OK[0] = False
               CHECK_PORT()
            #    GLOBAL_FLAG[0] = CAR_OFF_FLAG



        else:
        #  START_SYSTEM[0] =  2                                                      # RESET THIS VARIABLE TO SHOW OPTIONS AGAIN
         os.system('cls')
         print("\n PLEASE WAIT FOR CHECKING LOG IN PROCESS ......\n\n")
         face_id , verified_person , driver_name = CHECK_USER()                                  # return if person is verified or not after (3 times) check
        #  face_id , verified_person , driver_name = 1 , True , "Abdelrahman Osama"                                  # return if person is verified or not after (3 times) check
         time.sleep(1)

        #  print("check out")
         try:
           SEND_FACE_ID(face_id)  
           SERIAL_CONNECTION_IS_OK[0] = True                                                   # send face id
         except:
            SERIAL_CONNECTION_IS_OK[0] = False
            CHECK_PORT()
            # GLOBAL_FLAG[0] = CAR_OFF_FLAG

        if (verified_person == True) and ( SERIAL_CONNECTION_IS_OK[0] == True):                                             # already verified person
             say_my_name(driver_name)
             play_mp3("welcome.mp3")
             time.sleep(2)
             TSR_STATUS[0]=TSR_ON_FLAG
            #  time.sleep(2)
            #  SOUND_STSYTEM_THREAD.start()                                          # start SOUND task (run at background)
            #  time.sleep(2)
             CAR_IS_ON[0]  =  True                                                 # car is now on

            #  START_SYSTEM[0] = 0
            #  RECEIVE_GLOBAL_FLAG_THREAD = threading.Thread(target=RECEIVE_GLOBAL_FLAG)                  # put RECEIVE_GLOBAL_FLAG algorithm in independent task 
            #  RECEIVE_GLOBAL_FLAG_THREAD.start()                                           # run 24 hours (run at background and won't stop at all)
            #  time.sleep(2)
            #  CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD = threading.Thread(target=CONFIGURE_RECEIVED_GLOBAL_FLAG)       # put CONFIGURE_RECEIVED_GLOBAL_FLAG algorithm in independent task 
            #  CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD.start()                                # run 24 hours (run at background and won't stop at all) 
            #  time.sleep(2)
            #  BLOCK_VOICE[0] = False
             

             while True:                                                           # wait untill off the car to back to initial status
                 time.sleep(1) 
                 CHECK_PORT()

                 if (CAR_STATUS[0] == CAR_OFF_FLAG)and (TSR_CAMERA_FAILED_SOUND[0] == False)and (DMS_CAMERA_FAILED_SOUND[0] == False):                               # all systems off

                     TSR_STATUS[0] = TSR_OFF_FLAG                                  # STOP TSR

                    #  time.sleep(2)                                                 # wait if there is sound on to stop

                     play_mp3("caroff.mp3")

                     START_SYSTEM[0] = 0

                     CAR_IS_ON[0] = False                                          # stop car
  
                     DMS_STATUS[0] =  DMS_TAKE_ACTION                              # reset DMS FLAG TO ITS INITIAL STATUS

                     ADD_USER_IS_ON[0] = False 

                     DELETE_USER_IS_ON[0] = False 

                    #  BLOCK_VOICE[0] = False

                     break                                                         # back to initial status


        elif (verified_person == False) and (driver_name == "camerafailed"):
                  CAR_STATUS[0] = CAR_OFF_FLAG
                  GLOBAL_FLAG[0]= 0
                  START_SYSTEM[0] = 0
                  ADD_USER_IS_ON[0] = False 
                  DELETE_USER_IS_ON[0] = False 
                  play_mp3("drivercamera.mp3")
                  CAMERA_ERROR[0] = True
                  time.sleep(1)

        elif (verified_person == False) or ( SERIAL_CONNECTION_IS_OK[0] == False):
            # time.sleep(10)
            CAR_STATUS[0] = CAR_OFF_FLAG
            GLOBAL_FLAG[0]= 0
            START_SYSTEM[0] = 0
            ADD_USER_IS_ON[0] = False 
            DELETE_USER_IS_ON[0] = False 
            # BLOCK_VOICE[0] = False
            # RECEIVE_GLOBAL_FLAG_THREAD = threading.Thread(target=RECEIVE_GLOBAL_FLAG)                  # put RECEIVE_GLOBAL_FLAG algorithm in independent task 
            # RECEIVE_GLOBAL_FLAG_THREAD.start()                                           # run 24 hours (run at background and won't stop at all)
            # time.sleep(2)
            # CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD = threading.Thread(target=CONFIGURE_RECEIVED_GLOBAL_FLAG)       # put CONFIGURE_RECEIVED_GLOBAL_FLAG algorithm in independent task 
            # CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD.start()                                # run 24 hours (run at background and won't stop at all) 
            # time.sleep(2)
