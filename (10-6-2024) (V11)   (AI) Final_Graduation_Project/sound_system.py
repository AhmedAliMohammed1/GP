import pygame
import time
import os
import pyttsx3
# from vosk import Model, KaldiRecognizer
# import pyaudio
from shared_resources import *
#from add_user import *
#from delete_user import *
import speech_recognition as sr
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

def ONLINE_VOICE_CONTROL():


  recognizer = sr.Recognizer()

  while True:

     try:

        with sr.Microphone() as mic:

            recognizer.adjust_for_ambient_noise(mic , duration=0.6 )
            #print("ready")
            audio = recognizer.listen(mic , None,5)
            #print("time out")

            text = recognizer.recognize_google(audio)
            text = text.lower()
            if (text == "please turn on the car"):
                CAR_STATUS[0] = CAR_ON_FLAG
            elif (text == "please turn off the car"):
                CAR_STATUS[0] = CAR_OFF_FLAG
            elif (text == "please add user"):
                ADD_USER_IS_ON[0]  = True                       
            elif (text == "please delete user"):
                DELETE_USER_IS_ON[0]  = True                                             # reset after finish deleting
            

     except :
        #print("error")
        recognizer = sr.Recognizer()
        continue

#####################################################################################################################################

def SOUND_ON():

    while True:
     time.sleep(1)
     while (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG) :

        no_sign_counter = 0
        
        if (DMS_STATUS[0] == DMS_TAKE_ACTION) and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):    # CAR IS OUT OF CONTROL
            
            play_mp3("danger.mp3")
            time.sleep(2)
            
            while  (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG) and (DMS_STATUS[0] == DMS_TAKE_ACTION) and (DMS_CAMERA_FAILED_SOUND[0] == False) and (TSR_CAMERA_FAILED_SOUND[0] == False):    # WHILE CAR IS OUT OF CONTROL
                
                play_mp3("warning alarm.mp3")
                time.sleep(2)


        elif (DMS_STATUS[0] == DMS_RELEASE_ACTION) and (TSR_CAMERA_FAILED_SOUND[0] == False)and (DMS_CAMERA_FAILED_SOUND[0] == False):           # CAR IS CONTROLLED
            
            play_mp3("safe.mp3")
            time.sleep(2)
            
            while (CAR_IS_ON[0] == True) and (CAR_STATUS[0] == CAR_ON_FLAG) and (DMS_STATUS[0] == DMS_RELEASE_ACTION) and (SLEEP_DRIVER[0] == False) and  (DMS_CAMERA_FAILED_SOUND[0] == False) and (TSR_CAMERA_FAILED_SOUND[0] == False):     # WHILE CAR IS CONTROLLED
                
                if (TSR_FLAG[0] == SIGN_NO_WAITING_FLAG) and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):
                    play_mp3("no stopping.mp3")
                    time.sleep(1)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_40_KM_FLAG)and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):
                    play_mp3("sign40.mp3")
                    time.sleep(3)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_100_KM_FLAG)and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):
                    play_mp3("sign100.mp3")
                    time.sleep(3)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_120_KM_FLAG)and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):
                    play_mp3("sign120.mp3")
                    time.sleep(3)
                    no_sign_counter = 0
                
                elif (TSR_FLAG[0] == SIGN_PARKING_AREA_FLAG)and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):
                    play_mp3("parking area.mp3")
                    time.sleep(1)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_NO_PARKING_FLAG)and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):
                    play_mp3("no parking.mp3")
                    time.sleep(2)
                    no_sign_counter = 0

                elif (TSR_FLAG[0] == SIGN_STOP_FLAG)and (TSR_CAMERA_FAILED_SOUND[0] == False) and (DMS_CAMERA_FAILED_SOUND[0] == False):
                    play_mp3("stop.mp3")
                    time.sleep(2)
                    no_sign_counter = 0

                elif (no_sign_counter == 0) and (DMS_CAMERA_FAILED_SOUND[0] == False) and (TSR_CAMERA_FAILED_SOUND[0] == False) :                           # no sign
                    play_mp3("nosign.mp3")
                    time.sleep(1)
                    no_sign_counter+=1                                 # to make no sign sound repeated only once untill new sign detected
                time.sleep(1)
        elif (DMS_STATUS[0] == DMS_WAIT)and (TSR_CAMERA_FAILED_SOUND[0] == False)and (DMS_CAMERA_FAILED_SOUND[0] == False):           # CAR IS ON BUT NOT MOVING
            time.sleep(0.1)

#####################################################################################################################################

def OFFLINE_VOICE_CONTROL():


  model = Model("vosk-model-en-us-0.42-gigaspeech")
  recognizer = KaldiRecognizer(model, 16000)
    
  mic = pyaudio.PyAudio()
  stream = mic.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=8192)
  stream.start_stream()

  while True:
   time.sleep(1)
   while (BLOCK_VOICE[0] == False):

    try:

        data = stream.read(4096)
        
        if recognizer.AcceptWaveform(data):
            text = recognizer.Result()
            text = text[14:-3]
            if (text == "please turn on the car") and (CAR_IS_ON[0] == False):
                CAR_STATUS[0] = CAR_ON_FLAG
                BLOCK_VOICE[0] = True
            elif (text == "please turn off the car") and (CAR_IS_ON[0] == True):
                CAR_STATUS[0] = CAR_OFF_FLAG
                BLOCK_VOICE[0] = True
            elif (text == "please add user") and (CAR_IS_ON[0] == False):
                ADD_USER_IS_ON[0]  = True
                BLOCK_VOICE[0] = True                       
            elif (text == "please delete user") and (CAR_IS_ON[0] == False):
                DELETE_USER_IS_ON[0]  = True                                             # reset after finish deleting
                BLOCK_VOICE[0] = True
            

    except :

        recognizer = KaldiRecognizer(model, 16000)
        mic = pyaudio.PyAudio()
        stream = mic.open(format=pyaudio.paInt16, channels=1, rate=16000, input=True, frames_per_buffer=8192)
        stream.start_stream()

        continue

#####################################################################################################################################
