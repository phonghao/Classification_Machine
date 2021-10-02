#include <Arduino.h>
#include <define.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,4);
Servo Servo_Left;
Servo Servo_Right;

void setup() 
{
  Serial.begin(9600);

  /*--------------- Attach mode for Pins ---------------*/
  for (int i = 0; i < O_PIN; i++) 
    pinMode(pinOut[i],OUTPUT);
  for (int i = 0; i < I_PIN; i++) 
    pinMode(pinIn[i],INPUT);

  /*--------------- Attach interuption for Pins ---------------*/
  attachInterrupt(digitalPinToInterrupt(I_SENSOR1_PIN),Sensor1,RISING);
  attachInterrupt(digitalPinToInterrupt(I_SENSOR2_PIN),Sensor2,RISING);
  attachInterrupt(digitalPinToInterrupt(I_SENSOR3_PIN),Sensor3,RISING);

  /*--------------- Attach servo controler Pins ---------------*/
  Servo_Left.attach(O_SERVO_L_PIN);
  Servo_Right.attach(O_SERVO_R_PIN);

  /*--------------- Initialization for LCD ---------------*/
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("CANTALOUP");
  lcd.setCursor(0,1);
  lcd.print("WEIGHT: "+String(Val_LoadcellRaw));
  lcd.setCursor(14,1);
  lcd.print("KG");
}

/*
************************************************************************
* Function decription : Run Motor and LCD
* Run condition       : Continuously
* Input               : Val_LoadcellRaw
* Ouput               : None
************************************************************************
*/
void loop() 
{
  MOTOR(RUN);

  lcd.setCursor(8,1);
  lcd.print(String(Val_LoadcellRaw));
}

/*
********************************************************************************
* Function decription : Send request to Raspberry Pi to conduct image processing
* Run condition       : Interuption of Sensor 1
* Input               : None
* Output              : Val_Raspi is 1 if vein is lager than 50%
                        Otherwise, it is 0
********************************************************************************
*/
void Sensor1()
{
  MOTOR(STOP);
  _delay_ms(500);
  do
  {
    RASPI_OUT(HIGH);
    Val_Raspi = STATE(I_VEIN_PIN);
  } while (!STATE(I_RASPI_PIN));
  RASPI_OUT(LOW);
  _delay_ms(500);
}

/*
*******************************************************************************************************
* Function decription : Scale cantaloup weight
* Run condition       : Interuption of Sensor 2
* Input               : None
* Ouput               : Val_Loadcell is 1 if Val_LoadcellRaw is lager than 1.2Kg and smaller than 2.2Kg
                        Otherwise, it is 0
*******************************************************************************************************
*/
void Sensor2()
{
  MOTOR(STOP);
  _delay_ms(2000);
  Val_LoadcellRaw = 2.2;
  Val_Loadcell = ((Val_LoadcellRaw <= 2.2) && (Val_LoadcellRaw >= 1.2)) ? 1 : 0;
}

/*
*******************************************************************************************************
* Function decription : Classification and controlling servo to sort
* Run condition       : Interuption of Sensor 3
* Input               : Val_Loadcell
                        Val_Raspi
* Ouput               : Servo position
*******************************************************************************************************
*/
void Sensor3()
{
  MOTOR(STOP);

  Servo_Left.write(DIRECT_ANGLE);
  Servo_Right.write(DIRECT_ANGLE);
  _delay_ms(500);

  if (!Val_Loadcell)
    Type = CANTALOUP_TYPE_III;
  else if (Val_Loadcell && !Val_Raspi)
    Type = CANTALOUP_TYPE_II;
  else Type = CANTALOUP_TYPE_I;

  switch (Type)
  {
  case CANTALOUP_TYPE_I:
    Servo_Left.write(TOLEFT_ANGLE);
    Servo_Right.write(TOLEFT_ANGLE);
    _delay_ms(500);
    break;
  case CANTALOUP_TYPE_II:
    Servo_Left.write(DIRECT_ANGLE);
    Servo_Right.write(DIRECT_ANGLE);
    _delay_ms(500);
    break;
  case CANTALOUP_TYPE_III:
    Servo_Left.write(TORIGHT_ANGLE);
    Servo_Right.write(TORIGHT_ANGLE);
    _delay_ms(500);
    break;
  default:
    break;
  }
  MOTOR(RUN);
}