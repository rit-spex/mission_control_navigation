#include <Arduino.h>
#include "interface.h"
#define POT_READPIN_1 PIN_A9
#define POT_READPIN_2 PIN_A8
#define POT_READPIN_3 PIN_A7
#define BUTTON_READPIN_POT 0
const int MAX_ANALOG = 1023;
int potVal1 = 0;
int potVal2 = 0;
int potVal3 = 0;

void setup() {
    pinMode(POT_READPIN_1, INPUT);
    pinMode(POT_READPIN_2, INPUT);
    pinMode(POT_READPIN_3, INPUT);
    pinMode(BUTTON_READPIN_POT, INPUT);
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println(parseValue(245, 0));
    Serial.println(parseValue(245, 1));
    Serial.println(parseValue(245, 2));
}

void loop() {  
    int setPotentiometers = digitalRead(BUTTON_READPIN_POT);
    Serial.println(setPotentiometers);
    if (setPotentiometers > 0) {
        potVal1 = analogRead(POT_READPIN_1);
        potVal2 = analogRead(POT_READPIN_2);
        potVal3 = analogRead(POT_READPIN_3);
        int roll = getDegrees(potVal1),
            pitch = getDegrees(potVal2),
            yaw = getDegrees(potVal3);
        setDisplay(roll, pitch, yaw);
    }
}