import serial

################################## GLOBAL VARIABLES WILL (NOT) BE CHANGED IN ANOTHER FILES (CONSTANT) ##################################

# baud_rate                      = 115200
# laptop_port                    = ['COM8']

# # shared_ser = [serial.Serial(laptop_port[0] , baud_rate)]
# shared_ser = [0]


# web_cam_id                      = 0
# external_cam_id_1               = 1
# external_cam_id_2               = 2




flip_frames                    = True
MAX_NUM_OF_CAMERAS             = 3

ADD_GESTURE                    = "thumbs up"
DELETE_GESTURE                 = "thumbs down"
CAR_ON_GESTURE                 = "peace"
CAR_OFF_GESTURE                = "fist"

FACE_ID_START_OF_FRAME         = '/'     #2f
FACE_ID_END_OF_FRAME           = '+'     #2b


CAR_ON_FLAG                    = '\x22'   #""
CAR_OFF_FLAG                   = '\x33'   # 3


ADD_USER_OPTION_FLAG           = 'a'
DELETE_USER_OPTION_FLAG        = 'd'


TSR_START_OF_FRAME             = '#'          #23
TSR_END_OF_FRAME               = '*'
TSR_ON_FLAG                    = '\x88'
TSR_OFF_FLAG                   = '\x77'
SIGN_NO_WAITING_FLAG           = 8
SIGN_100_KM_FLAG               = 9
SIGN_120_KM_FLAG               = 10
SIGN_40_KM_FLAG                = 13
SIGN_PARKING_AREA_FLAG         = 0
SIGN_NO_PARKING_FLAG           = 7
SIGN_STOP_FLAG                 = 19


DMS_START_OF_FRAME             = '@'
DMS_END_OF_FRAME               = '&'
DMS_OPEN_EYES                  = 'v'
DMS_CLOSED_EYES                = 'u'
DMS_FORCE_STOP                 = 'w'
DMS_NO_PERSON                  = 'x'
DMS_TAKE_ACTION                = '\x66'      #f
DMS_RELEASE_ACTION             =  '\x55'     #U
DMS_WAIT                       =  '\x21'     #!
EYE_THRESHOLD                  = 3.6

GESTURE_START_OF_FRAME         = '\x24'
GESTURE_END_OF_FRAME           = '\x25'
GESTURE_CAR_ON_FLAG            = 26
GESTURE_CAR_OFF_FLAG           = 27


########################################## GLOBAL VARIABLES WILL BE CHANGED IN ANOTHER FILES ###########################################

laptop_port = ['NULL']
baud_rate   = [115200]
shared_ser = [0]
CAMERA_ERROR = [False]
START_SYSTEM      =        [0]
GLOBAL_FLAG       =        [0]
TIMER_ENABLE      =        [False]
TSR_STATUS        =        [TSR_OFF_FLAG]
CAR_STATUS        =        [CAR_OFF_FLAG]
DMS_STATUS        =        [DMS_TAKE_ACTION]
ADD_USER_IS_ON    =        [False]
DELETE_USER_IS_ON =        [False]
TSR_FLAG          =        [99]
CAR_IS_ON         =        [False]
#BRIGHTNESS        =        [1]
USERS_FOUND        =       [False]
# BLOCK_VOICE        =       [False]
check_user_camera        = [0]
add_user_camera          = [0]
delete_user_camera       = [0]
tsr_camera               = [0]
dms_camera               = [0]
gesture_control_camera   = [0]
TSR_CAMERA_FAILED_SOUND  = [False]
DMS_CAMERA_FAILED_SOUND  = [False]
SERIAL_CONNECTION_IS_OK  = [False]
SLEEP_DRIVER             = [False]