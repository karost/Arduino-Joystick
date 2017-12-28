///////////////////////////////////////////////////////////////////////////////////////////////////
//Program this use
//1. Keyes Thumb Joystick Module for Arduino
//2. Sparkfun Pro Micro ATmega32U4 5V/16MHZ
//3. Arduino 1.8.3 with Sparkfun Pro Micro driver
//
//Thanit Kebsiri
//2017-07-27
//Credit:
//Thank you to
//1) Matthew Heironimus from https://github.com/MHeironimus/ArduinoJoystickLibrary
//2) metanurb from https://www.instructables.com/id/Add-a-little-two-analog-axis-thumb-joystick-to-you/
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Joystick.h"
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK,
0, 0, // Button Count, Hat Switch Count
true, true, false, // X and Y, but no Z Axis
false, false, false, // No Rx, Ry, or Rz
false, false, // No rudder or throttle
false, true, false); // No accelerator, brake, or steering

const bool DEBUG = false; // set to true to debug the raw values

//--- make sure you point to the right pin :)
int xPin = A1;
int yPin = A2;
int zPin = A3;
int xZero, yZero;
int xValue, yValue, zValue;
int xTrans, yTrans;
int xCur, yCur , zCur ;
int xMaxRange , xMinRange;
int yMaxRange, yMinRange;
int zMaxBrake, zMinBrake;
int deadzone = 5; // smaller values will be set to 0
void setup(){
pinMode(xPin, INPUT);
pinMode(yPin, INPUT);
pinMode(zPin, INPUT);
if(DEBUG) {
Serial.begin(9600);
}
// seting max min range for send to joystick
// because my joystick not point to center
// you will data from debug
// from my joystick
//xRage 610/2 -> 305
//yRange 680/2 -> 340
xMaxRange = 497;
xMinRange = -497;
yMaxRange = 497;
yMinRange = -497;

zMaxBrake = 300; 
zMinBrake = 50;

// calculate neutral position
xZero = analogRead(xPin);
yZero = analogRead(yPin);
//-- need logial joystick point to center ( 0 - 1024)
xTrans = 497 - xZero;
yTrans = 497 - yZero;
// Initialize Joystick Library
Joystick.setXAxisRange(xMaxRange, xMinRange);
Joystick.setYAxisRange(yMinRange, yMaxRange);
Joystick.setBrakeRange(zMinBrake, zMaxBrake);
Joystick.begin();
}
void loop(){

// read instance joystick positon
xCur = analogRead(xPin);
yCur = analogRead(yPin);
zCur = analogRead(zPin);
// trick it
xValue = xCur + xTrans - 497;
yValue = yCur + yTrans - 497;
zValue = zCur;

// dead zone blocking
if(abs(xValue) < deadzone) {
xValue = 0;
}
if(abs(yValue) < deadzone) {
yValue = 0;
}
if(DEBUG) {
/*
this is for checking my joystick
*/
//-- joystick positon : Center , Max , Min : Range ->Range Use
//-- xCur 514 , 1023 , 0 : 612 ->610
//-- yCur 497 , 1023 , 0 : 689 ->680
//-- so my range x -257 0 +355 --> set range 257
// x -371 0 +317 --> set range 371
Serial.print("xCurrent: ");
Serial.print(xCur);
Serial.print(" yCurrent: ");
Serial.print(yCur);
Serial.print(" <> xZero: ");
Serial.print(xZero);
Serial.print(" yZero: ");
Serial.print(yZero);
Serial.print(" <> X: ");
Serial.print(xValue);
Serial.print(" Y: ");
Serial.println(yValue);
}
//-- if value jump out of maxrange setting
if ( xValue > xMaxRange )
    xValue = xMaxRange;
if ( xValue < xMinRange )
    xValue = xMinRange;
if ( yValue > yMaxRange )
    yValue = yMaxRange;
if ( yValue < yMinRange )
    yValue = yMinRange;

if ( zValue > zMaxBrake )
    zValue = zMaxBrake;
 
if ( zValue < zMinBrake )
    zValue = zMinBrake;




//-- Send to USB
Joystick.setXAxis(xValue);
Joystick.setYAxis(yValue);
Joystick.setBrake(zValue);
delay(10);
}

