#ifndef __eosBoard_Custom_PIC32_USB_STARTER_KIT_I__
#define __eosBoard_Custom_PIC32_USB_STARTER_KIT_I__


#include "Board/eosBoard_PIC32_USB_STARTER_KIT_I.h"



// Conexions a la placa d'expanssio.
//
// Senyal     Senyal PIC32          Pin
// ---------  --------------------  -------
// X-STEP     OC4/RD3               J11-18
// X-DIR      PMPWR/OC5/C13/RD4     J10-14
// X-HOME
// X-LIMIT
//
// Y-STEP     PMPRD/RD5             J11-13
// Y-DIR      IC1/RTCC/RD8          J11-25
// Y-HOME
// Y-LIMIT
//
// Z-STEP     SS1/IC2/RD9           J11-26
// Z-DIR      SCK1/IC3/PMPCS2/RD10  J10-16
// Z-HOME
// Z-LIMIT
//
// 5V0        +5.0                  J10-28
// 3V3        +3.3                  J10-27
// GND        GND                   J10-45
//


// -----------------------------------------------------------------------
// MOTORS
//
#define EXIST_MOTORS_MOTOR1

#define MOTORS_MOTOR1_STEP_PORT
#define MOTORS_MOTOR1_STEP_PIN

#define MOTORS_MOTOR1_DIRECTION_PORT
#define MOTORS_MOTOR1_DIRECTION_PIN

#define MOTORS_MOTOR1_ENABLE_PORT           HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR1_ENABLE_PIN            HAL_GPIO_PIN_NONE

#define MOTORS_MOTOR1_HOME_PORT             HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR1_HOME_PIN              HAL_GPIO_PIN_NONE

#define MOTORS_MOTOR1_LIMIT_PORT            HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR1_LIMIT_PIN             HAL_GPIO_PIN_NONE

#define EXIST_MOTORS_MOTOR2

#define MOTORS_MOTOR2_STEP_PORT             HAL_GPIO_PORT_D
#define MOTORS_MOTOR2_STEP_PIN              HAL_GPIO_PIN_5

#define MOTORS_MOTOR2_DIRECTION_PORT        HAL_GPIO_PORT_D
#define MOTORS_MOTOR2_DIRECTION_PIN         HAL_GPIO_PIN_8

#define MOTORS_MOTOR2_ENABLE_PORT           HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR2_ENABLE_PIN            HAL_GPIO_PIN_NONE

#define MOTORS_MOTOR2_HOME_PORT             HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR2_HOME_PIN              HAL_GPIO_PIN_NONE

#define MOTORS_MOTOR2_LIMIT_PORT            HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR2_LIMIT_PIN             HAL_GPIO_PIN_NONE

#define EXIST_MOTORS_MOTOR3

#define MOTORS_MOTOR3_STEP_PORT             HAL_GPIO_PORT_D
#define MOTORS_MOTOR3_STEP_PIN              HAL_GPIO_PIN_9

#define MOTORS_MOTOR3_DIRECTION_PORT        HAL_GPIO_PORT_D
#define MOTORS_MOTOR3_DIRECTION_PIN         HAL_GPIO_PIN_10

#define MOTORS_MOTOR3_ENABLE_PORT           HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR3_ENABLE_PIN            HAL_GPIO_PIN_NONE

#define MOTORS_MOTOR3_HOME_PORT             HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR3_HOME_PIN             HAL_GPIO_PIN_NONE

#define MOTORS_MOTOR3_LIMIT_PORT            HAL_GPIO_PORT_NONE
#define MOTORS_MOTOR3_LIMIT_PIN             HAL_GPIO_PIN_NONE


#endif // __eosBoard_Custom_PIC32_USB_STARTER_KIT_I__
