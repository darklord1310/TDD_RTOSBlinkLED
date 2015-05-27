#include "mock_ReadButton.h"
#include "mock_turnOnLED.h"
#include "mock_turnOffLED.h"
#include "mock_getCurrrentTime.h"
#include "LEDsStateMachine.h"
#include "cmock.h"
#include "unity.h"




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



 SD_LED5(&state , 200, &count, &previousTime);



 UnityAssertEqualNumber((_U_SINT)((CheckButton)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)27, UNITY_DISPLAY_STYLE_INT);

}







void test_CheckButton_will_stay_at_current_state_when_button_is_not_read(void)

{

 State state = CheckButton;

 int count = 0;

 int previousTime = 0;





 ReadButton_CMockExpectAndReturn(39, 0);





 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((CheckButton)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)43, UNITY_DISPLAY_STYLE_INT);

}





void test_CheckButton_will_transition_to_ON_when_button_is_read(void)

{

 State state = CheckButton;

 int count = 0;

 int previousTime = 0;





 ReadButton_CMockExpectAndReturn(54, 1);





 SD_LED5(&state , 200, &count, &previousTime);



 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)59, UNITY_DISPLAY_STYLE_INT);

}







void test_On_will_turnOnLED_and_stay_when_timer_not_reach_yet(void)

{

 State state = ON;

 int count = 0;

 int previousTime = 0;





 turnOnLED_CMockExpect(71);

 getCurrentTime_CMockExpectAndReturn(72, 100);

 turnOnLED_CMockExpect(73);

 getCurrentTime_CMockExpectAndReturn(74, 120);





 SD_LED5(&state , 200, &count, &previousTime);





 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)80, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);





 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)84, UNITY_DISPLAY_STYLE_INT);

}





void test_On_goes_to_turnOffLED_when_timer_reached(void)

{

 State state = ON;

 int previousTime = 0;

 int count = 0;





 turnOnLED_CMockExpect(95);

 getCurrentTime_CMockExpectAndReturn(96, 200);





 getCurrentTime_CMockExpectAndReturn(99, 200);







 SD_LED5(&state , 200 , &count , &previousTime);

 UnityAssertEqualNumber((_U_SINT)((OFF)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)104, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((200)), (_U_SINT)((previousTime)), (((void *)0)), (_U_UINT)105, UNITY_DISPLAY_STYLE_INT);

}





void test_Off_will_turnOffLED_and_stay_when_timer_not_reach_yet(void)

{

 State state = OFF;

 int previousTime = 200;

 int count = 0;





 turnOffLED_CMockExpect(116);

 getCurrentTime_CMockExpectAndReturn(117, 301);

 turnOffLED_CMockExpect(118);

 getCurrentTime_CMockExpectAndReturn(119, 350);





 SD_LED5(&state , 200,&count, &previousTime);





 UnityAssertEqualNumber((_U_SINT)((OFF)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)125, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);





 UnityAssertEqualNumber((_U_SINT)((OFF)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)129, UNITY_DISPLAY_STYLE_INT);

}







void test_Off_will_goes_to_CheckCount_when_timer_reached(void)

{

 State state = OFF;

 int previousTime = 200;

 int count = 0;





 turnOffLED_CMockExpect(141);

 getCurrentTime_CMockExpectAndReturn(142, 400);







 getCurrentTime_CMockExpectAndReturn(146, 400);







 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((CheckCount)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)151, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((400)), (_U_SINT)((previousTime)), (((void *)0)), (_U_UINT)152, UNITY_DISPLAY_STYLE_INT);

}







void test_CheckCount_will_go_to_ON_when_count_is_smaller_than_5(void)

{





 State state = CheckCount;

 int count = 2;

 int previousTime = 0;





 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)167, UNITY_DISPLAY_STYLE_INT);







}







void test_CheckCount_will_goes_to_isButtonHold_when_count_is_equal_to_5(void)

{





 State state = CheckCount;

 int count = 5;

 int previousTime = 5;





 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((isButtonHold)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)185, UNITY_DISPLAY_STYLE_INT);



}







void test_isButtonHold_will_stay_at_currentState_when_button_is_still_press(void)

{





 State state = isButtonHold;

 int count = 0;

 int previousTime = 0;





 ReadButton_CMockExpectAndReturn(200, 1);





 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((isButtonHold)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)204, UNITY_DISPLAY_STYLE_INT);



}





void test_isButtonHold_will_goes_to_CheckButton_when_button_is_not_press(void)

{





 State state = isButtonHold;

 int count = 0;

 int previousTime = 0;





 ReadButton_CMockExpectAndReturn(218, 0);





 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((CheckButton)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)222, UNITY_DISPLAY_STYLE_INT);



}







void test_allInOneTest()

{

 State state = initial;

 int previousTime = 0;

 int count = 0;





 ReadButton_CMockExpectAndReturn(235, 0);

 ReadButton_CMockExpectAndReturn(236, 0);

 ReadButton_CMockExpectAndReturn(237, 1);

 turnOnLED_CMockExpect(238);

 getCurrentTime_CMockExpectAndReturn(239, 0);

 turnOnLED_CMockExpect(240);

 getCurrentTime_CMockExpectAndReturn(241, 199);

 turnOnLED_CMockExpect(242);

 getCurrentTime_CMockExpectAndReturn(243, 200);

 getCurrentTime_CMockExpectAndReturn(244, 200);

 turnOffLED_CMockExpect(245);

 getCurrentTime_CMockExpectAndReturn(246, 201);

 turnOffLED_CMockExpect(247);

 getCurrentTime_CMockExpectAndReturn(248, 400);

 getCurrentTime_CMockExpectAndReturn(249, 400);

 ReadButton_CMockExpectAndReturn(250, 1);

 ReadButton_CMockExpectAndReturn(251, 0);







 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((CheckButton)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)256, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((CheckButton)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)258, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((CheckButton)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)260, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)262, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)264, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)266, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((OFF)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)268, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((200)), (_U_SINT)((previousTime)), (((void *)0)), (_U_UINT)269, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((OFF)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)271, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((400)), (_U_SINT)((previousTime)), (((void *)0)), (_U_UINT)273, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((CheckCount)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)274, UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((count)), (((void *)0)), (_U_UINT)275, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((ON)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)277, UNITY_DISPLAY_STYLE_INT);

 state = CheckCount;

 count = 5;

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((isButtonHold)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)281, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((isButtonHold)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)283, UNITY_DISPLAY_STYLE_INT);

 SD_LED5(&state , 200, &count, &previousTime);

 UnityAssertEqualNumber((_U_SINT)((CheckButton)), (_U_SINT)((state)), (((void *)0)), (_U_UINT)285, UNITY_DISPLAY_STYLE_INT);

}
