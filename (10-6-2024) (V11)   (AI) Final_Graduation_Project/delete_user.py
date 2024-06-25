import cv2
import time
import datetime
from PIL import Image
import numpy as np
import os
import re
import sys
import msvcrt
import requests
from pytimedinput import timedInput
from deepface import DeepFace
from validate_email_address import validate_email
from random import randint , choice
import string
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
from shared_resources import *
from sound_system import *

#################################################################################################################

def time_out_input(prompt, timeout):
    print(prompt, end='', flush=True)

    start_time = time.time()
    input_text = ""
    cursor_position = 0  # Initialize cursor position
    while True:
        if msvcrt.kbhit():  # Check if a key is pressed
            char = msvcrt.getwch()  # Get the character
            if char == '\r':  # Enter key
                break
            elif char == '\x08':  # Backspace
                if cursor_position > 0:
                    input_text = input_text[:cursor_position - 1] + input_text[cursor_position:]
                    cursor_position -= 1
                    sys.stdout.write('\b \b' + input_text[cursor_position:] + ' ' * (len(input_text) - cursor_position + 1) + '\b' * (len(input_text) - cursor_position + 1))  # Backspace and clear the character
                    sys.stdout.flush()
            elif char == '\x00':  # Arrow key (extended key)
                arrow_key = msvcrt.getwch()  # Get the next character
                if arrow_key == 'K':  # Left arrow
                    pass
                    # if cursor_position > 0:
                    #     sys.stdout.write('\b')  # Move cursor left
                    #     sys.stdout.flush()
                    #     cursor_position -= 1
                elif arrow_key == 'M':  # Right arrow
                    pass
                    # if cursor_position < len(input_text):
                    #     sys.stdout.write(input_text[cursor_position])  # Move cursor right
                    #     sys.stdout.flush()
                    #     cursor_position += 1
                elif arrow_key == 'H':  # UP arrow
                    pass
         
                elif arrow_key == 'P':  # DOWN arrow
                    pass
              
            else:
                input_text = input_text[:cursor_position] + char + input_text[cursor_position:]
                cursor_position += 1
                sys.stdout.write(char + input_text[cursor_position - 1:] + '\b ')  # Echo back the character and remaining text
                sys.stdout.flush()
                sys.stdout.write('\b' * (len(input_text) - cursor_position + 1))  # Move cursor left
                sys.stdout.flush()
        elif time.time() - start_time > timeout:
            # print("\nTimeout reached. No input received.")
            return None, True
    print()  # New line after input
    return input_text, False


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

def save_names(names, filename):
    with open(filename, "w") as file:
        for name in names:
            file.write(name + "\n")

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

def load_names(filename):
    try:
        with open(filename, "r") as file:
            names = file.read().splitlines()
        return names
    except FileNotFoundError:
        return []

#################################################################################################################

def check_internet():
    try:
        requests.get('http://www.google.com', timeout=2)
        return True
    #except requests.ConnectionError:
    except:
        return False

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

def DELETE_USER():

    capture_index = delete_user_camera[0]

    USERS_FOUND[0] = False

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    sender_email = "ecotronicscrafters@gmail.com"
    sender_password = "bdvb cidy cqdv isht"
    mail_subject = "DELETE USER !!!"
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
    mail_body = "Attempt to delete user\nThe verification code for completion deleting proecss is (" + str(verification_code) + ")"
    code_trials = 3
    id_trials = 3
    positions_counter = 0
    num_of_positions  = 30
    time_out = False
    time_out_sec = 60
    internet_connection = True


    driver_names = load_names("database.txt")
    recipient_emails = load_names("mails.txt")

    for user in driver_names:
       if (user != "NONE"):
          USERS_FOUND[0] = True
          break
       
    if(USERS_FOUND[0] == True):
     cap = cv2.VideoCapture(capture_index)

     try:
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
      cv2.putText(frame, "DELETE USER", (10, 130), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2, cv2.LINE_AA)
      photo_name = 'delete_user.jpg'
      unknown_photo_path = os.path.join(theft_folder, f'deleteuser_{current_datetime.strftime("%Y%m%d%H%M%S")}.jpg')
      attached_image_path = unknown_photo_path
      cv2.imwrite(unknown_photo_path, frame)
      cv2.destroyAllWindows()
      cap.release()

     except:
        play_mp3("drivercamera.mp3")
        CAMERA_ERROR[0] = True
        time.sleep(1)
        GLOBAL_FLAG[0] = CAR_OFF_FLAG

        return 0    #terminate now
     
    

     if(check_internet() == True):

         try:
            location , map_zoom = GET_LIVE_LOCATION()
            if(map_zoom > 14):
                mail_body = f"Attempt to delete user from this location\n\n{location}\n\nThe verification code for completion deleting proecss is (" + str(verification_code) + ")"
            
            send_mails(sender_email , sender_password , recipient_emails , mail_subject , mail_body , attached_image_path)
            
            internet_connection = True

         except:
            internet_connection = False
     else:
            internet_connection = False

     no_thing = timedInput("Please enter the verification code : " , timeout=0.001)
     os.system("cls")
     if (internet_connection == True):
         os.system("cls")
         print("A verification code has already been sent to verified user mails\n")
         
     elif(internet_connection == False):
        os.system("cls")
        print("(OFFLINE MODE) A verification code has already been sent to your local database\n")
        with open("offline_mode.txt", "w") as file:
                file.write(verification_code)
    
    
    while(code_trials>0) and (time_out == False):

        if(USERS_FOUND[0] == True):
         user_code , time_out = time_out_input("Please enter the verification code : " , timeout= time_out_sec)

        else:
         os.system('cls')
         print("NO USERS FOUND")
         cv2.waitKey(3000)
         os.system('cls')
         break

        

        if(user_code == verification_code) and (time_out == False):
            code_trials=0

            while(id_trials>0) and (time_out ==False):

                try:

                 deleted_id , time_out = time_out_input("Enter the id you want to delete  >>  " , timeout= time_out_sec)

                 if (time_out == False):

                    deleted_id = int(deleted_id)
                    driver_names[deleted_id-1] = "NONE"
                    recipient_emails[deleted_id-1] = "NONE"


                    while (positions_counter < num_of_positions):

                        os.remove(f"{database_path}/{deleted_id}-{positions_counter+1}.jpg")

                        positions_counter = positions_counter + 1

                    save_names(driver_names,"database.txt")
                    save_names(recipient_emails,"mails.txt")

                    USERS_FOUND[0] = False
                    for user in driver_names:
                      if (user != "NONE"):
                         USERS_FOUND[0] = True
                         break
                    
                    if(USERS_FOUND[0] == True):
                      os.system('cls')
                      #frame = temp_saved_positions[0]
                      #DeepFace.find(img_path = frame, db_path = database_path , model_name="DeepFace" , enforce_detection=False)
                      DeepFace.find(img_path = frame, db_path = database_path , model_name="Facenet512", enforce_detection=False)
                      DeepFace.find(img_path = frame, db_path = database_path , model_name="Dlib", enforce_detection=False)
                      DeepFace.find(img_path = frame, db_path = database_path , model_name="SFace", enforce_detection=False)
                    
                    else:
                        
                        files = os.listdir(database_path)
                        for file_name in files:
                            file_path = os.path.join(database_path, file_name)
                            if os.path.isfile(file_path):
                               os.remove(file_path)

                    os.system('cls')
                    print("DELETED SUCCESSFULLY")
                    id_trials=0
                    cv2.waitKey(3000)
                    os.system('cls')


                except ValueError:
                    id_trials-=1
                    if(id_trials==0):
                       os.system('cls')
                       print("ID MUST BE ONLY NUMBERS , you don't have any trials")
                    else:
                        os.system('cls')
                        print(f"ID MUST BE ONLY NUMBERS , try again , you still have {id_trials} trials")
                    cv2.waitKey(3000)
                    os.system('cls')

                except IndexError:
                    id_trials-=1
                    if(id_trials==0):
                        os.system('cls')
                        print("WRONG ID , you don't have any trials")
                    else:
                        os.system('cls')
                        print(f'WRONG ID , TRY AGAIN , YOU HAVE {id_trials} trials')
                    cv2.waitKey(3000)
                    os.system('cls')

                except FileNotFoundError:
                    id_trials-=1
                    if(id_trials==0):
                        os.system('cls')
                        print("WRONG ID , you don't have any trials")
                    else:
                        os.system('cls')
                        print(f'WRONG ID , TRY AGAIN , YOU HAVE {id_trials} trials')
                    cv2.waitKey(3000)
                    os.system('cls')

        elif (time_out == False):
            code_trials-=1
            if(code_trials==0):
                os.system('cls')
                print(f"WRONG CODE , you don't have any trials")
            else:
                os.system('cls')
                print(f"WRONG CODE , try again , you still have {code_trials} trials")
            cv2.waitKey(3000)
            os.system('cls')

    if (internet_connection == False):  #no internet connection
        with open("offline_mode.txt", "w") as file:
            file.write("")
        internet_connection = True  #reset

    if (time_out == True):  
        os.system('cls')
        print("\n TIME OUT !\n")
        time.sleep(3)
        os.system('cls')
        time_out = False  #reset



#################################################################################################################
