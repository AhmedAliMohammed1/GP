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
os.chdir(os.path.dirname(os.path.abspath(__file__)))


#####################################################################################################################################

def FINAL_GRADUATION_PROJECT():

 TSR_THREAD                            = threading.Thread(target=TSR_ON)                               # put TSR algorithm in independent task 
 RECEIVE_GLOBAL_FLAG_THREAD            = threading.Thread(target=RECEIVE_GLOBAL_FLAG)                  # put RECEIVE_GLOBAL_FLAG algorithm in independent task 
 CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD = threading.Thread(target=CONFIGURE_RECEIVED_GLOBAL_FLAG)       # put CONFIGURE_RECEIVED_GLOBAL_FLAG algorithm in independent task 
 SOUND_STSYTEM_THREAD                  = threading.Thread(target=SOUND_ON)                             # put SOUND_STSYTEM algorithm in independent task 
 DMS_EYE_DETECTION_THREAD              = threading.Thread(target=DMS_EYE_DETECTION)                    # put DMS_EYE_DETECTION algorithm in independent task 
#  VOICE_CONTROL_THREAD                  = threading.Thread(target=OFFLINE_VOICE_CONTROL)                # put VOICE_CONTROL algorithm in independent task 


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


 while True :                                                                      # super loop for all system
     
     if(START_SYSTEM[0] == 0):            # TO SHOW THE OPTIONS ONLY AT INITIALIZATION OF SYSTEM
                                                         

    #   TSR_THREAD                            = threading.Thread(target=TSR_ON)                               # put TSR algorithm in independent task 
    #   RECEIVE_GLOBAL_FLAG_THREAD            = threading.Thread(target=RECEIVE_GLOBAL_FLAG)                  # put RECEIVE_GLOBAL_FLAG algorithm in independent task 
    #   CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD = threading.Thread(target=CONFIGURE_RECEIVED_GLOBAL_FLAG)       # put CONFIGURE_RECEIVED_GLOBAL_FLAG algorithm in independent task 
    #   SOUND_STSYTEM_THREAD                  = threading.Thread(target=SOUND_ON)                             # put SOUND_STSYTEM algorithm in independent task 


    #   RECEIVE_GLOBAL_FLAG_THREAD.start()                                                # run 24 hours (run at background and won't stop at all)
    #   time.sleep(2)
    #   CONFIGURE_RECEIVED_GLOBAL_FLAG_THREAD.start()                                     # run 24 hours (run at background and won't stop at all)
    #   time.sleep(2)
      os.system('cls')
      print(" CHOOSE OPTION\n (KEYBOARD)  a              >> ADD USER\n (KEYBOARD)  d              >> DELETE USER\n (DASHBOARD) POWER SWITCH   >> CAR ON\n")
      START_SYSTEM[0] = 1                                                          # PREVENT OPTIONS TO BE PRINTED MORE THAN ONCE                                                  

     if keyboard.is_pressed('a'):  
            ADD_USER_IS_ON[0] = True
    
     elif keyboard.is_pressed('d'):  
            DELETE_USER_IS_ON[0] = True 

     if (ADD_USER_IS_ON[0] == True) :                                                  # Check if the 'a' key is pressed
         START_SYSTEM[0] = 0                                                       # RESET THIS VARIABLE TO SHOW OPTIONS AGAIN
         os.system('cls')
         print("\n PLEASE WAIT FOR ADDING PROCESS ......\n\n")                                                  # to stop check user to be on (recieve car on flag) while add user is on
         ADD_USER()
         ADD_USER_IS_ON[0] = False
        #  BLOCK_VOICE[0] = False  


     elif (DELETE_USER_IS_ON[0] == True):                                                # Check if the 'd' key is pressed
         START_SYSTEM[0] = 0                                                       # RESET THIS VARIABLE TO SHOW OPTIONS AGAIN
         DELETE_USER_IS_ON[0] = True
         os.system('cls')
         print("\n PLEASE WAIT FOR DELETING PROCESS ......\n\n")                                                 # to stop check user to be on (recieve car on flag) while add user is on
         DELETE_USER()
         DELETE_USER_IS_ON[0] = False                                              # reset after finish deleting
        #  BLOCK_VOICE[0] = False 


     elif (CAR_STATUS[0] == CAR_ON_FLAG):                                          # someone try to open the car
        #  START_SYSTEM[0] =  2                                                      # RESET THIS VARIABLE TO SHOW OPTIONS AGAIN
         os.system('cls')
         print("\n PLEASE WAIT FOR CHECKING LOG IN PROCESS ......\n\n")
         face_id , verified_person , driver_name = CHECK_USER()                                  # return if person is verified or not after (3 times) check
         time.sleep(1)

        #  print("check out")
         SEND_FACE_ID(face_id)                                                     # send face id

         if (verified_person == True):                                             # already verified person
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
                 time.sleep(1)                                                 # wait if there is sound on to stop

                 if (CAR_STATUS[0] == CAR_OFF_FLAG):                               # all systems off

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
         elif (verified_person == False):
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
