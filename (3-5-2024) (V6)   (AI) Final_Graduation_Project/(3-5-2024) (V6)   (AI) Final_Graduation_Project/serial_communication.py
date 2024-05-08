import serial
import time
#from shared_resources import baud_rate , laptop_port , GLOBAL_FLAG , CAR_STATUS , DMS_STATUS , ADD_USER_IS_ON , DELETE_USER_IS_ON , CAR_ON_FLAG , CAR_OFF_FLAG , DMS_TAKE_ACTION , DMS_RELEASE_ACTION ,FACE_ID_START_OF_FRAME , FACE_ID_END_OF_FRAME
from shared_resources import *

#################################################################################################################

def SEND_FACE_ID(face_id):

    #send = serial.Serial(laptop_port, baud_rate)
    data_to_send = str(face_id)
    shared_ser.write(FACE_ID_START_OF_FRAME.encode('utf-8'))                    # START OF face id FRAME
    shared_ser.write(data_to_send.encode('utf-8'))                              # send face id 
    shared_ser.write(FACE_ID_END_OF_FRAME.encode('utf-8'))                      # END OF face id FRAME
    # shared_ser.close()
    # print("SEND done")

#################################################################################################################

def RECEIVE_GLOBAL_FLAG():

    #receive = serial.Serial(laptop_port, baud_rate)
    time.sleep(1)
    # print("RECIVE START")
    # time.sleep(2)
    while True:
      GLOBAL_FLAG[0] = shared_ser.read().decode('utf-8')
      # print("RECIVE DONE")
      # time.sleep(2)
      # if (START_SYSTEM[0] == 2):
      #       break
     # Close the serial connection when done
    # shared_ser.close()  #till now , this line will not be executed

#################################################################################################################    

def CONFIGURE_RECEIVED_GLOBAL_FLAG():
    time.sleep(1)
    # print("DMS START")
    # time.sleep(5)

    while True:
      time.sleep(1)
      # print(GLOBAL_FLAG[0])
      # time.sleep(2)
      if (GLOBAL_FLAG[0] == CAR_ON_FLAG) and (ADD_USER_IS_ON[0] == False) and (DELETE_USER_IS_ON[0] == False) and (CAR_IS_ON[0] == False) :     # make sure that car status will not change while add or delete is on
        
        CAR_STATUS[0] = CAR_ON_FLAG

      elif (GLOBAL_FLAG[0] == CAR_OFF_FLAG) and (ADD_USER_IS_ON[0] == False) and (DELETE_USER_IS_ON[0] == False) and (CAR_IS_ON[0] == True) :     # CAR OFF
        
        CAR_STATUS[0] = CAR_OFF_FLAG

      elif (GLOBAL_FLAG[0] == DMS_TAKE_ACTION ) or (GLOBAL_FLAG[0] == DMS_RELEASE_ACTION ) or (GLOBAL_FLAG[0] == DMS_WAIT ) :              # dms flags

        DMS_STATUS[0] = GLOBAL_FLAG[0]
      # if (START_SYSTEM[0] == 2):
      #       break

#################################################################################################################