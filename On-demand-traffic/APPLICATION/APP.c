/*
 * APP.c
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#include "app.h"

EN_systemState_t currentState = CAR;
u8 counter = 0, timerCounter = 0;
ST_timer0_t timer;

void APP_start(void) {

	/*
	 * Initialize the Project
	 */

	/*
	 *
	 *	   ____    _    ____      _     _____ ____
	 *	  / ___|  / \  |  _ \    | |   | ____|  _ \ ___
	 *	 | |     / _ \ | |_) |   | |   |  _| | | | / __|
	 *	 | |___ / ___ \|  _ <    | |___| |___| |_| \__ \
     *	  \____/_/   \_\_| \_\   |_____|_____|____/|___/
	 *
	 *
	 */
	/*Initialize the LEDs of the cars*/
	LED_init(PORTA_ID, PIN0); /*GreenCar*/
	LED_init(PORTA_ID, PIN1); /*YellowCar*/
	LED_init(PORTA_ID, PIN2); /*RedCar*/

	/*
	 *
	 *  __  __    _    _   _     _     _____ ____
	 * |  \/  |  / \  | \ | |   | |   | ____|  _ \ ___
	 * | |\/| | / _ \ |  \| |   | |   |  _| | | | / __|
	 * | |  | |/ ___ \| |\  |   | |___| |___| |_| \__ \
     * |_|  |_/_/   \_\_| \_|   |_____|_____|____/|___/
	 *
	 *
	 */
	/*Initialize the LEDs of the men*/
	LED_init(PORTB_ID, PIN0); /*GreenMan*/
	LED_init(PORTB_ID, PIN1); /*YellowMan*/
	LED_init(PORTB_ID, PIN2); /*RedMan*/

	/*
	 * Initialize the button on port D pin 2
	 */
	Button_init(PORTD_ID, PIN2);

	/*enable the global interrupt*/
	GIE_enable();

	/*Initialize the timer*/
	timer.mode = TIMER0_NORMAL;
	timer.ocMode = OC0_DISCONNECTED;
	timer.prescaler = TIMER0_1024_PS;
	TIMER0_init(&timer);

	/*enable the overflow interrupt*/
	TIMER0_OVF_interruptEnable();

	/*set the callback function of the timer0 interrupt*/
	TIMER0_OVF_setCallBackFunction(&timerISR);

	/*Initialize the exti0*/
	EXTI0_init(EXTI_FALLING_EDGE);

	/*set the callback function of the exti0*/
	EXTI0_setCallBack(&ISR);


	while (TRUE) {
		/*switch the state of the system*/
		switch (currentState) {
		case CAR:
			if (counter < 50) /*in the 5 sec of the state*/
			{
				/*
				 * CAR mode:
				 */
				/*the car green light is on*/
				LED_on(PORTA_ID, PIN0);
				/*the man red light is on*/
				LED_on(PORTB_ID, PIN2);

				/*the other light is off*/
				LED_off(PORTB_ID, PIN0);
				LED_off(PORTA_ID, PIN2);
				LED_off(PORTB_ID, PIN1);
				LED_off(PORTA_ID, PIN1);

				/*increment the counter*/
				counter++;
			} else {
				currentState = YELLOW_CAR;
				counter = 0;
			}
			break;
		case YELLOW_CAR:
			if (counter < 50) /*in the 5 sec of the state*/
			{
				/*
				 * YELLOW_CAR mode:
				 */
				/*the car yellow light is on and toggle*/
				/*the man red light is on*/
				LED_on(PORTB_ID, PIN2);

				/*the other light is off*/
				LED_off(PORTA_ID, PIN2);
				LED_off(PORTA_ID, PIN0);
				LED_off(PORTB_ID, PIN0);
				LED_off(PORTB_ID, PIN1);
				if ((counter % 5) == 0) /*toggling every 0.5 sec*/
				{
					/*toggle the yellow of the car*/
					LED_toggle(PORTA_ID, PIN1);
				}

				/*increment the counter*/
				counter++;
			} else {
				/*change the state to the next*/
				currentState = MAN;

				/*reset the counter*/
				counter = 0;
			}
			break;
		case MAN:
			if (counter < 50) /*in the 5 sec of the state*/
			{
				/*
				 *  MAN mode:
				 */


				/*the man green light is on*/
				LED_on(PORTB_ID, PIN0);
				/*the car red light is on*/
				LED_on(PORTA_ID, PIN2);

				/*the other light is off*/
				LED_off(PORTA_ID, PIN0);
				LED_off(PORTB_ID, PIN2);
				LED_off(PORTA_ID, PIN1);
				LED_off(PORTB_ID, PIN1);
				/*increment the counter*/
				counter++;
			} else {
				/*change the state to the next*/
				currentState = YELLOW_MAN;

				/*reset the counter*/
				counter = 0;
			}
			break;
		case YELLOW_MAN:
			if (counter < 50) /*in the 5 sec of the state*/
			{
				/*
				 * YELLOW_MAN mode:
				 */

				/*the man yellow light is on and toggle*/
				/*the car red light is on*/
				LED_on(PORTA_ID, PIN2);

				LED_off(PORTB_ID, PIN2);
				LED_off(PORTA_ID, PIN0);
				LED_off(PORTB_ID, PIN0);
				LED_off(PORTA_ID, PIN1);
				if ((counter % 5) == 0) /*toggling every 0.5 sec*/
				{
					/*toggle the yellow of the man*/
					LED_toggle(PORTB_ID, PIN1);
				}

				/*increment the counter*/
				counter++;
			} else {
				/*change the state to the next*/
				currentState = CAR;

				/*reset the counter*/
				counter = 0;
			}
			break;

		default:
			break;
		}

		/*wait to 1/10 of the sec*/
		delayOneTenthSec(&timer);
	}
}

void delayOneTenthSec(ST_timer0_t *ptr_timer0) {
	u8 flag = TRUE;
	u8 nothing = 0;

	/*start the timer*/
	TIMER0_start(ptr_timer0);
	/*wait until the number of overflows*/
	while (flag) {
		TIMER0_getTimerValue(&nothing);
		switch (timerCounter) {
		case 3:

			flag = FALSE;
			break;
		default:
			break;
		}
	}

	/*reset the overflow counter*/
	timerCounter = 0;

	/*stop the timer*/
	TIMER0_stop();
}

void ISR(void) {
	/*switch over the current state of the system*/
	switch (currentState) {
	case CAR: /*in CAR state change the state to YELLOW_CAR and make the counter 0*/
		currentState = YELLOW_CAR;
		counter = 0;
		break;
	case YELLOW_CAR: /*in YELLOW_CAR state*/
		/* code */
		break;
	case MAN: /*in MAN state*/
		/* code */
		break;
	case YELLOW_MAN: /*in YELLOW_MAN*/
		/* code */
		break;

	default:
		break;
	}
}

void timerISR(void) {
	/*increment the counter that indicates the overflows number*/
	timerCounter++;
}
