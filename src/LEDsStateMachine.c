#include "LEDsStateMachine.h"


/*
 *  LED5 will blinks 5 times when user button is press
 *  Even if user hold the button, it will still blinks 5 times only
 *  After release and press again, then will only blinks for another 5 times
 *
 */
void SD_LED5(State *state,int BlinkRate)
{
	static int previousTime = 0;
	static int count = 0;

	switch(*state)
	{
		case initial: *state = CheckButton;
					  break;

		case CheckButton : if( ReadButton() )
					            *state = ON;
						   break;

		case ON : turnOnLED();
				   if( getCurrentTime() - previousTime == BlinkRate )
				   {
					 previousTime = getCurrentTime();
					 *state = OFF;
				   }
				   break;

		case OFF : turnOffLED();
				  if( getCurrentTime() - previousTime == BlinkRate)
				  {
					previousTime = getCurrentTime();
					*state = CheckCount;
					count++;
				  }
				  break;
		case CheckCount : if(count < 5)
							 *state = ON;
						  else
							  *state = isButtonHold;
						  break;

		case isButtonHold : if( !ReadButton() )
							{
								  *state = CheckButton;
								  count = 0;
							}
							else
								 *state = isButtonHold;
							break;
	}
}
