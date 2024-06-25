import serial
import time
#from shared_resources import baud_rate , laptop_port , GLOBAL_FLAG , CAR_STATUS , DMS_STATUS , ADD_USER_IS_ON , DELETE_USER_IS_ON , CAR_ON_FLAG , CAR_OFF_FLAG , DMS_TAKE_ACTION , DMS_RELEASE_ACTION ,FACE_ID_START_OF_FRAME , FACE_ID_END_OF_FRAME
from shared_resources import *
import serial.tools.list_ports

#################################################################################################################

def SEND_FACE_ID(face_id):

    #send = serial.Serial(laptop_port, baud_rate)
    data_to_send = str(face_id)
    shared_ser[0].write(FACE_ID_START_OF_FRAME.encode('utf-8'))                    # START OF face id FRAME
    shared_ser[0].write(data_to_send.encode('utf-8'))                              # send face id 
    shared_ser[0].write(FACE_ID_END_OF_FRAME.encode('utf-8'))                      # END OF face id FRAME
    # shared_ser[0].close()
    # print("SEND done")

#################################################################################################################

def RECEIVE_GLOBAL_FLAG():

    #receive = serial.Serial(laptop_port, baud_rate)
    time.sleep(1)
    # print("RECIVE START")
    # time.sleep(2)
    while True:
      try:
        GLOBAL_FLAG[0] = shared_ser[0].read().decode('utf-8')
        SERIAL_CONNECTION_IS_OK[0] = True
      except:
        SERIAL_CONNECTION_IS_OK[0] = False
        CHECK_PORT()
        # GLOBAL_FLAG[0] = CAR_OFF_FLAG

      # print("RECIVE DONE")
      # time.sleep(2)
      # if (START_SYSTEM[0] == 2):
      #       break
     # Close the serial connection when done
    # shared_ser[0].close()  #till now , this line will not be executed

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

def CHECK_PORT():
    ports = serial.tools.list_ports.comports()
    if ports:
        # print("Available COM Ports:")
        for port, desc, hwid in sorted(ports):
          if (str(port) != laptop_port[0]):
            laptop_port[0] = str(port)
            try:
              shared_ser[0].close()
              # print("try")
            except:
              # print("exc")
              pass
            # print(f"  {port}: {desc} [{hwid}]")
            shared_ser[0] = serial.Serial(laptop_port[0] , baud_rate[0])
          # print(laptop_port[0])
          break

    else:
        # print("No COM ports found.")
        pass