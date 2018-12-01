#ifndef HEADER_H_
#define HEADER_H_

#define POT_READPIN_1 PIN_A9
#define POT_READPIN_2 PIN_A8
#define POT_READPIN_3 PIN_A7
#define BUTTON_ROLL_UP 1
#define BUTTON_ROLL_DOWN 2
#define BUTTON_PITCH_UP 3
#define BUTTON_PITCH_DOWN 4
#define BUTTON_YAW_UP 5
#define BUTTON_YAW_DOWN 6
#define BUTTON_READPIN_POT 0

#define DOUT 11
#define DIN 12
#define CS 10
#define SCK 13

int getDegrees(int);
void setDisplay(int, int, int);
int parseValue(int, int);

#endif /* HEADER_H_ */