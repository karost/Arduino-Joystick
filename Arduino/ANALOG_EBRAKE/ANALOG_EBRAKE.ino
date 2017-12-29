// Analog eBrake-Handbrake
// PIN A0 to 10k pot output - Throttle Axis
// Use with Arduino ProMicro or Sparkfun Pro Micro ATmega32U4 5V/16MHZ
// Arduino 1.8.3 with Sparkfun Pro Micro driver
// by THANIT KEBSIRI
// 28.12.2017

#include "Joystick.h"

//--------------------------------------------------------------------
//--- CREATE JOYSTICK OBJECT AND USE ONLY BRAKE CONTROL
//--------------------------------------------------------------------
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
0, 0, // Button Count, Hat Switch Count
false, false, false,  // No X ,Y, Z Axis (Joystick)
false, false, false,  // No Rx, Ry, or Rz
false, false,         // No rudder or throttle
false, true, false);  // No accelerator, add new  brake,  No steering

const bool DEBUG = true; // set to true to debug the raw values
const int zPin = A0;   // use pin A0

int zCur,zMap ;
int zMinBrake, zMaxBrake;

void setup(){
  zMinBrake = 0; 
  zMaxBrake = 1021; 

  pinMode(zPin, INPUT);
  Joystick.setBrakeRange(zMinBrake, zMaxBrake);
  Joystick.begin();
  
  if(DEBUG) {
    Serial.begin(9600);
  }
}
void loop(){
  
  zCur = analogRead(zPin);

  if(DEBUG){
    Serial.print("zCur = ");
    Serial.println( zCur );
  }
  
  Joystick.setBrake(zCur);
  //zMap = map(zCur,0,1023,0,255);
  delay(10);
}
