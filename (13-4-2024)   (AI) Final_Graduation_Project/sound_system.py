import pygame
import time
import os
import pyttsx3
from shared_resources import *

os.chdir(os.path.dirname(os.path.abspath(__file__)))

#####################################################################################################################################

def play_mp3(file_path):
    pygame.init()
    pygame.mixer.init()
    time.sleep(1)  # Add a small delay
    pygame.mixer.music.load(file_path)
    pygame.mixer.music.play()


#####################################################################################################################################


def say_my_name(name):
    engine = pyttsx3.init()
    engine.setProperty('voice' , 'HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\Tokens\TTS_MS_EN-US_DAVID_11.0')
    text = 'Welcome' + str(name)
    engine.say(text)
    engine.runAndWait()


#####################################################################################################################################


def SOUND_ON():

    while True:
     time.sleep(1)
     while (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG) :

        no_sign_counter = 0
        
        if (DMS_STATUS[0] == DMS_TAKE_ACTION):    # CAR IS OUT OF CONTROL
            
            play_mp3("danger.mp3")
            time.sleep(2)
            
            while  (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG) and (DMS_STATUS[0] == DMS_TAKE_ACTION) :    # WHILE CAR IS OUT OF CONTROL
                
                play_mp3("warning alarm.mp3")
                time.sleep(2)


        elif (DMS_STATUS[0] == DMS_RELEASE_ACTION):           # CAR IS CONTROLLED
            
            play_mp3("safe.mp3")
            time.sleep(2)
            
            while (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG) and (DMS_STATUS[0] == DMS_RELEASE_ACTION) :     # WHILE CAR IS CONTROLLED
                
                if (TSR_FLAG[0] == SIGN_NO_WAITING_FLAG):
                    play_mp3("no stopping.mp3")
                    time.sleep(1)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_40_KM_FLAG):
                    play_mp3("sign40.mp3")
                    time.sleep(3)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_100_KM_FLAG):
                    play_mp3("sign100.mp3")
                    time.sleep(3)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_120_KM_FLAG):
                    play_mp3("sign120.mp3")
                    time.sleep(3)
                    no_sign_counter = 0

                elif (no_sign_counter == 0) :                           # no sign
                    play_mp3("nosign.mp3")
                    time.sleep(1)
                    no_sign_counter+=1                                 # to make no sign sound repeated only once untill new sign detected
                time.sleep(1)
                    
