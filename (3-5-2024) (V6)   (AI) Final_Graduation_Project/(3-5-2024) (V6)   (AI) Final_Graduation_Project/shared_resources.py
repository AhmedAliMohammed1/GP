import serial

################################## GLOBAL VARIABLES WILL (NOT) BE CHANGED IN ANOTHER FILES (CONSTANT) ##################################

baud_rate                      = 115200
laptop_port                    = 'COM8'

shared_ser = serial.Serial(laptop_port , baud_rate)


web_cam_id                      = 0
external_cam_id_1               = 1
external_cam_id_2               = 2


check_user_camera              = web_cam_id
add_user_camera                = web_cam_id
delete_user_camera             = web_cam_id
tsr_camera                     = external_cam_id_1
dms_camera                     = web_cam_id

FACE_ID_START_OF_FRAME         = '/'
FACE_ID_END_OF_FRAME           = '+'


CAR_ON_FLAG                    = '\x22'   #""
CAR_OFF_FLAG                   = '\x33'   # 3


ADD_USER_OPTION_FLAG           = 'a'
DELETE_USER_OPTION_FLAG        = 'd'


TSR_START_OF_FRAME             = '#'
TSR_END_OF_FRAME               = '*'
TSR_ON_FLAG                    = '\x88'
TSR_OFF_FLAG                   = '\x77'
SIGN_NO_WAITING_FLAG           = 8
SIGN_100_KM_FLAG               = 9
SIGN_120_KM_FLAG               = 10
SIGN_40_KM_FLAG                = 13


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

########################################## GLOBAL VARIABLES WILL BE CHANGED IN ANOTHER FILES ###########################################

START_SYSTEM      =        [0]
GLOBAL_FLAG       =        [0]
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