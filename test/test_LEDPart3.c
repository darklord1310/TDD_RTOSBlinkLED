#include "unity.h"
#include <cmock.h>
#include "LEDsStateMachine.h"
#include "mock_getCurrrentTime.h"
#include "mock_turnOffLED.h"
#include "mock_turnOnLED.h"
#include "mock_ReadButton.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_module_generator_needs_to_be_implemented(void)
{
	State *state = initial;
	
	SD_LED5(initial , LED5blinkRate);
}
