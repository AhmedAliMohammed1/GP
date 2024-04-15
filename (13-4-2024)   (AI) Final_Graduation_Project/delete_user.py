import cv2
import time
import datetime
import os
import re
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
from shared_resources import *

capture_index = delete_user_camera

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

    USERS_FOUND[0] = False

    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    sender_email = "ecotronicscrafters@gmail.com"
    sender_password = "bdvb cidy cqdv isht"
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
    code_trials = 3
    id_trials = 3
    positions_counter = 0
    num_of_positions  = 30


    driver_names = load_names("database.txt")
    recipient_emails = load_names("mails.txt")

    for user in driver_names:
       if (user != "NONE"):
          USERS_FOUND[0] = True
          break
       
    if(USERS_FOUND[0] == True):
     cap = cv2.VideoCapture(capture_index)
     ret, frame = cap.read()
     frame = adjust_brightness_dynamic(frame)
     current_datetime = datetime.datetime.now()
     date_text = f"Date: {current_datetime.date().strftime('%d-%m-%Y')}"
     time_text = f"Time: {current_datetime.time().strftime('%I:%M:%S %p')}"
     cv2.putText(frame, date_text, (10, 50), font, font_size, font_color, font_thickness, cv2.LINE_AA)
     cv2.putText(frame, time_text, (10, 80), font, font_size, font_color, font_thickness, cv2.LINE_AA)
     cv2.putText(frame, "DELETE USER", (int(frame.shape[1]/2) - 50, int(frame.shape[0]/2)), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2, cv2.LINE_AA)
     photo_name = 'delete_user.jpg'
     unknown_photo_path = os.path.join(theft_folder, f'deleteuser_{current_datetime.strftime("%Y%m%d%H%M%S")}.jpg')
     cv2.imwrite(unknown_photo_path, frame)
     cv2.destroyAllWindows()
     cap.release()

     #Create the email message
     message = MIMEMultipart()
     message["From"] = sender_email
     message["To"] = ", ".join(recipient_emails)
     message["Subject"] = "DELETE USER !!!"
     # Attach text to the email
     body = "Attempt to delete user\nThe verification code for completion deleting proecss is (" + str(verification_code) + ")"
     message.attach(MIMEText(body, "plain"))
     #Attach image to the email
     image_path = unknown_photo_path
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


     print("A verification code has already been sent to verified user mails\n")
    
    
    while(code_trials>0):

        if(USERS_FOUND[0] == True):
         user_code = input("Please enter the verification code : ")

        else:
         print("NO USERS FOUND")
         cv2.waitKey(3000)
         os.system('cls')
         break

        

        if(user_code == verification_code):
            code_trials=0

            while(id_trials>0):

                try:
                    deleted_id = int(input("Enter the id you want to delete  >>  "))
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
                      #DeepFace.find(img_path = frame, db_path = database_path , model_name="Facenet512", enforce_detection=False)
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
                       print("ID MUST BE ONLY NUMBERS , you don't have any trials")
                    else:
                        print(f"ID MUST BE ONLY NUMBERS , try again , you still have {id_trials} trials")
                    cv2.waitKey(3000)
                    os.system('cls')

                except IndexError:
                    id_trials-=1
                    if(id_trials==0):
                        print("WRONG ID , you don't have any trials")
                    else:
                        print(f'WRONG ID , TRY AGAIN , YOU HAVE {id_trials} trials')
                    cv2.waitKey(3000)
                    os.system('cls')

                except FileNotFoundError:
                    id_trials-=1
                    if(id_trials==0):
                        print("WRONG ID , you don't have any trials")
                    else:
                        print(f'WRONG ID , TRY AGAIN , YOU HAVE {id_trials} trials')
                    cv2.waitKey(3000)
                    os.system('cls')

        else:
            code_trials-=1
            if(code_trials==0):
                print(f"WRONG CODE , you don't have any trials")
            else:
                print(f"WRONG CODE , try again , you still have {code_trials} trials")
            cv2.waitKey(3000)
            os.system('cls')

#################################################################################################################
