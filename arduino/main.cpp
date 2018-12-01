#include <Arduino.h>
#include <stdlib.h>
#include "interface.h"
const int MAX_ANALOG = 1023;
const int SLEEP_TIME = 400; // 400ms

void setup() {
    pinMode(POT_READPIN_1, INPUT);
    pinMode(POT_READPIN_2, INPUT);
    pinMode(POT_READPIN_3, INPUT);
    pinMode(BUTTON_READPIN_POT, INPUT);
    pinMode(BUTTON_ROLL_UP, INPUT);
    pinMode(BUTTON_ROLL_DOWN, INPUT);
    pinMode(BUTTON_PITCH_UP, INPUT);
    pinMode(BUTTON_PITCH_DOWN, INPUT);
    pinMode(BUTTON_YAW_UP, INPUT);
    pinMode(BUTTON_YAW_DOWN, INPUT);
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
}

void loop() {  
    int setPotentiometers = digitalRead(BUTTON_READPIN_POT);
    int potVal1 = 0, potVal2 = 0, potVal3 = 0;
    int roll, pitch, yaw;
    if (setPotentiometers > 0) {  // if button to set displays is pressed
        potVal1 = analogRead(POT_READPIN_1);
        potVal2 = analogRead(POT_READPIN_2);
        potVal3 = analogRead(POT_READPIN_3);
        roll = getDegrees(potVal1);
        pitch = getDegrees(potVal2);
        yaw = getDegrees(potVal3);
        setDisplay(roll, pitch, yaw);
    }
    if (digitalRead(BUTTON_ROLL_UP) > 0) {  // button to increment roll 
        roll = (roll+1)%360;
        setDisplay(roll, pitch, yaw);
    } else if (digitalRead(BUTTON_ROLL_DOWN) >  0) {  // button to decrement roll 
        roll = (roll+1)%360;
        setDisplay(roll, pitch, yaw);
    }
    if (digitalRead(BUTTON_PITCH_UP) > 0) {  // button to increment pitch 
        pitch = (pitch+1)%360;
        setDisplay(roll, pitch, yaw);
    } else if (digitalRead(BUTTON_PITCH_DOWN) >  0) { // button to decrement pitch 
        pitch = (pitch-1)%360;
        setDisplay(roll, pitch, yaw);
    }
    if (digitalRead(BUTTON_YAW_UP) > 0) {  // button to increment yaw 
        yaw = (yaw+1)%360;
        setDisplay(roll, pitch, yaw);
    } else if (digitalRead(BUTTON_YAW_DOWN) >  0) {  // button to decrement yaw 
        yaw = (yaw-1)%360;
        setDisplay(roll, pitch, yaw);
    } 
    sleep(SLEEP_TIME);
}