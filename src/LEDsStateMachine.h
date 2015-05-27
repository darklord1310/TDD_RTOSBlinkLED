#ifndef LEDsStateMachine_H
#define LEDsStateMachine_H

#include "getCurrrentTime.h"
#include "turnOffLED.h"
#include "turnOnLED.h"
#include "ReadButton.h"

#define LED5blinkRate	200

typedef enum { initial, ON, OFF, CheckButton, CheckCount, isButtonHold} State;

typedef enum { LED5 } LEDSelection;


void SD_LED5(State *state,int BlinkRate , int *count, int *previousTime);



#endif // LEDsStateMachine_H
