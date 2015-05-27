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


void test_initial_will_goes_to_CheckButton_when_executed(void)
{
	State state = initial;
	int count = 0;
	int previousTime = 0;
	
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);
	
	TEST_ASSERT_EQUAL(CheckButton, state);
}



void test_CheckButton_will_stay_at_current_state_when_button_is_not_read(void)
{
	State state = CheckButton;
	int count = 0;
	int previousTime = 0;
	
	//mock
	ReadButton_ExpectAndReturn(0);
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);
	TEST_ASSERT_EQUAL(CheckButton, state);
}


void test_CheckButton_will_transition_to_ON_when_button_is_read(void)
{
	State state = CheckButton;
	int count = 0;
	int previousTime = 0;
	
	//mock
	ReadButton_ExpectAndReturn(1);
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);
	
	TEST_ASSERT_EQUAL(ON, state);
}



void test_On_will_turnOnLED_and_stay_when_timer_not_reach_yet(void)
{
	State state = ON;
	int count = 0;
	int previousTime = 0;
	
	//mock
	turnOnLED_Expect();
	getCurrentTime_ExpectAndReturn(100);
	turnOnLED_Expect();
	getCurrentTime_ExpectAndReturn(120);
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);			// previousTime is set to 0, then currentTime is 100
																	// 100 - 0 != 200
																	// so stay at ON state
	TEST_ASSERT_EQUAL(ON, state);
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);			// previousTime is set to 0, then currentTime is 120
																	// 120 - 0 != 200
																	// so stay at ON state
	TEST_ASSERT_EQUAL(ON, state);
}


void test_On_goes_to_turnOffLED_when_timer_reached(void)
{
	State state = ON;
	int previousTime = 0;
	int count = 0;
	
	//mock
	turnOnLED_Expect();											
	getCurrentTime_ExpectAndReturn(LED5blinkRate );				//  currentTime is BlinkRate which is 200ms which
																//	means timer already expires
																
	getCurrentTime_ExpectAndReturn(LED5blinkRate );				//  then load currentTime into previousTime
																//	and change state to CheckCount

	//run
	SD_LED5(&state , LED5blinkRate , &count , &previousTime);		
	TEST_ASSERT_EQUAL(OFF, state);
	TEST_ASSERT_EQUAL(LED5blinkRate, previousTime);
}


void test_Off_will_turnOffLED_and_stay_when_timer_not_reach_yet(void)
{
	State state = OFF;
	int previousTime = 200;
	int count = 0;
	
	//mock
	turnOffLED_Expect();
	getCurrentTime_ExpectAndReturn(301);
	turnOffLED_Expect();
	getCurrentTime_ExpectAndReturn(350);
	
	//run
	SD_LED5(&state , LED5blinkRate,&count, &previousTime);			// previousTime is set to 200, then currentTime is 301
																	// 301 - 200 != 200
																	// so stay at OFF state
	TEST_ASSERT_EQUAL(OFF, state);
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);			// previousTime is set to 200, then currentTime is 350
																	// 350 - 200 != 200
																	// so stay at OFF state
	TEST_ASSERT_EQUAL(OFF, state);
}



void test_Off_will_goes_to_CheckCount_when_timer_reached(void)
{
	State state = OFF;
	int previousTime = 200;										// set previousTime as 200
	int count = 0;
	
	//mock
	turnOffLED_Expect();											
	getCurrentTime_ExpectAndReturn(400);						//  currentTime is 400 means timer already expires
																//	because previous time is 200
																//	so 400 - 200 already 200ms
																
	getCurrentTime_ExpectAndReturn(400);						//  then load currentTime into previousTime
																//	and change state to CheckCount
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);					
	TEST_ASSERT_EQUAL(CheckCount, state);
	TEST_ASSERT_EQUAL(400, previousTime);
}



void test_CheckCount_will_go_to_ON_when_count_is_smaller_than_5(void)
{
	
	//initialize
	State state = CheckCount;						//initialize state to CheckCount
	int count = 2;									//initialize count smaller than 5
	int previousTime = 0;
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		
	TEST_ASSERT_EQUAL(ON, state);					// will go to ON state because
													// count < 5
													

}



void test_CheckCount_will_goes_to_isButtonHold_when_count_is_equal_to_5(void)
{
	
	//initialize
	State state = CheckCount;						//initialize state to CheckCount
	int count = 5;									//initialize count = 5
	int previousTime = 5;
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		
	TEST_ASSERT_EQUAL(isButtonHold, state);			// will goes to isButtonHold because count = 5

}



void test_isButtonHold_will_stay_at_currentState_when_button_is_still_press(void)
{
	
	//initialize
	State state = isButtonHold;						//initialize state to isButtonHold
	int count = 0;									//initialize count = 0
	int previousTime = 0;
	
	//mock
	ReadButton_ExpectAndReturn(1);
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		
	TEST_ASSERT_EQUAL(isButtonHold, state);			// will goes to isButtonHold because ReadButton is 1
	
}


void test_isButtonHold_will_goes_to_CheckButton_when_button_is_not_press(void)
{
	
	//initialize
	State state = isButtonHold;						//initialize state to isButtonHold
	int count = 0;									//initialize count = 0
	int previousTime = 0;
	
	//mock
	ReadButton_ExpectAndReturn(0);
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		
	TEST_ASSERT_EQUAL(CheckButton, state);			// will goes to CheckButton because ReadButton is 0
	
}


// fully testing the state machine
void test_allInOneTest()
{
	State state = initial;
	int previousTime = 0;
	int count = 0;
	
	//mock
	ReadButton_ExpectAndReturn(0);				//button not pressed
	ReadButton_ExpectAndReturn(0);				//button not pressed
	ReadButton_ExpectAndReturn(1);				//button pressed
	turnOnLED_Expect();							// LED on
	getCurrentTime_ExpectAndReturn(0);			// Timer not reach
	turnOnLED_Expect();							// LED on
	getCurrentTime_ExpectAndReturn(199);		// Timer not reach
	turnOnLED_Expect();							// LED on
	getCurrentTime_ExpectAndReturn(200);		// Timer reach, change state to Off
	getCurrentTime_ExpectAndReturn(200);		// load CurrentTime to previousTime
	turnOffLED_Expect();						// LED off
	getCurrentTime_ExpectAndReturn(201);		// Timer not reach
	turnOffLED_Expect();						// LED off
	getCurrentTime_ExpectAndReturn(400);		// Timer reach, change state to CheckCount
	getCurrentTime_ExpectAndReturn(400);		// load CurrentTime to previousTime
	ReadButton_ExpectAndReturn(1);				// button hold
	ReadButton_ExpectAndReturn(0);				// button release
	
	
	//run
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		
	TEST_ASSERT_EQUAL(CheckButton, state);						// will goes to CheckButton after initial without any condition
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);
	TEST_ASSERT_EQUAL(CheckButton, state);						// will stay at CheckButton if ReadButton = 0
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);
	TEST_ASSERT_EQUAL(CheckButton, state);						// continue to stay at CheckButton as long as ReadButton = 0
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);
	TEST_ASSERT_EQUAL(ON, state);								// change to ON state when ReadButton = 1
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);			
	TEST_ASSERT_EQUAL(ON, state);								// stay at ON state as long as timer not reach
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		// turn on LED, previousTime is 0, CurrentTime is 199
	TEST_ASSERT_EQUAL(ON, state);								// stay at ON state as long as timer not reach
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		// turn on LED, previousTime is 0, CurrentTime is 200
	TEST_ASSERT_EQUAL(OFF, state);								// goes to OFF state as timer expires
	TEST_ASSERT_EQUAL(200, previousTime);						// previousTime should updated to 200
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		// turn off LED, CurrentTime is 201
	TEST_ASSERT_EQUAL(OFF, state);								// stay at OFF state as timer not expires
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		// turn off LED, CurrentTime is 400
	TEST_ASSERT_EQUAL(400, previousTime);						// previousTime should updated to 400
	TEST_ASSERT_EQUAL(CheckCount, state);						// should go to CheckCount
	TEST_ASSERT_EQUAL(1, count);								// count should update to 1
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);
	TEST_ASSERT_EQUAL( ON , state);								// change to state ON since count < 5
	state = CheckCount;											// change state to CheckCount
	count = 5;													// change count = 5
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		
	TEST_ASSERT_EQUAL(isButtonHold, state);						// change state to isButtonHold since count >= 5
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);	
	TEST_ASSERT_EQUAL(isButtonHold, state);						// button hold, state stay at isButtonHold	
	SD_LED5(&state , LED5blinkRate, &count, &previousTime);		
	TEST_ASSERT_EQUAL(CheckButton, state);						// button release, wait for button again
}
