#ifndef __DEFINE_H__
#define __DEFINE_H_

#include <Arduino.h>

#define O_PIN                   4
#define I_PIN                   5

#define RUN                     1
#define STOP                    0

#define DEBUGGER                13
#define I_SENSOR1_PIN           2
#define I_SENSOR2_PIN           3
#define I_SENSOR3_PIN           18

#define O_RASPI_PIN             28
#define I_RASPI_PIN             30
#define I_VEIN_PIN              32

#define O_LOADCELL_PIN          34

#define O_SERVO_L_PIN           24
#define O_SERVO_R_PIN           26

#define RASPI_OUT(X)            (digitalWrite(O_RASPI_PIN,X))

#define STATE(X)                (digitalRead(X))

#define O_MOTOR_PIN             36
#define MOTOR(X)                (digitalWrite(O_MOTOR_PIN,X))

#define DIRECT_ANGLE            93
#define TOLEFT_ANGLE            68
#define TORIGHT_ANGLE           117

void Sensor1();
void Sensor2();
void Sensor3();

typedef enum
{
    CANTALOUP_TYPE_I = 1,
    CANTALOUP_TYPE_II,
    CANTALOUP_TYPE_III
}CANTALOUP_TYPE;

CANTALOUP_TYPE Type;
uint8_t pinOut[O_PIN]   = {\
                            O_MOTOR_PIN,\
                            DEBUGGER,\
                            O_RASPI_PIN,\
                            O_LOADCELL_PIN\
                            };
uint8_t pinIn[I_PIN]    = {\
                            I_SENSOR1_PIN,\
                            I_SENSOR2_PIN,\
                            I_SENSOR3_PIN,\
                            I_RASPI_PIN,\
                            I_VEIN_PIN\
                            };

uint8_t Val_Raspi       = 0;

float   Val_LoadcellRaw = 0;
uint8_t Val_Loadcell    = 0;

#endif