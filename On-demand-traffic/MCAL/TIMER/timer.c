/*
 * timer.c
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */


#include "timer.h"

static void (*TIMER0_OVF_func)(void) = NULL; /*call back function of timer 0 overflow interrupt*/
static void (*TIMER0_OC_func)(void) = NULL;	 /*call back function of timer 0 output compare match interrupt*/

/*from interrupt vectors table in the datasheet*/
void __vector_10(void) __attribute__((signal)); /*Timer/Counter0 Compare Match*/
void __vector_11(void) __attribute__((signal)); /*Timer/Counter0 Overflow*/

EN_timer0Error_t TIMER0_init(ST_timer0_t *ptr_timer0)
{
	EN_timer0Error_t ret = TIMER0_OK;

	/*switch over the timer mode*/
	switch (ptr_timer0->mode)
	{
	case TIMER0_NORMAL: /*WGM00 and WGM01 should be 0*/
		CLR_BIT(TCCR0, WGM00);
		CLR_BIT(TCCR0, WGM01);
		break;
	case TIMER0_PHASECORRECT: /*WGM00 should be 1, WGM01 should be 0, and FOC0 should be 0*/
		CLR_BIT(TCCR0, FOC0);
		SET_BIT(TCCR0, WGM00);
		CLR_BIT(TCCR0, WGM01);
		break;
	case TIMER0_CTC: /*WGM00 should be 0 and WGM01 should be 1*/
		CLR_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
		break;
	case TIMER0_FAST_PWM: /*WGM00 should be 1, WGM01 should be 1, and FOC0 should be 0*/
		CLR_BIT(TCCR0, FOC0);
		SET_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
		break;

	default:
		/*passed mode is wrong*/
		ret = TIMER0_WRONG_MODE;
		break;
	}

	/*switch over output compare mode*/
	switch (ptr_timer0->ocMode)
	{
	case OC0_DISCONNECTED: /*COM00 and COM01 should be 0*/
		CLR_BIT(TCCR0, COM00);
		CLR_BIT(TCCR0, COM01);
		break;
	case OC0_TOGGLE: /*COM00 should be 1 and COM01 should be 0*/
		if ((ptr_timer0->mode == TIMER0_NORMAL) || (ptr_timer0->mode == TIMER0_CTC))
		{
			SET_BIT(TCCR0, COM00);
			CLR_BIT(TCCR0, COM01);
		}
		else /*if PWM mode these tow bits are reserved (this mode is not allowed for PWM modes)*/
		{
			ret = TIMER0_WRONG_OC_MODE;
		}
		break;
	case OC0_NON_INVERTING: /*COM00 should be 0 and COM01 should be 1*/
		CLR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		break;
	case OC0_INVERTING: /*COM00 and COM01 should be 1*/
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		break;

	default:
		/*passed mode is wrong*/
		ret = TIMER0_WRONG_OC_MODE;
		break;
	}

	return ret;
}

void TIMER0_start(ST_timer0_t *ptr_timer0)
{
	/*depending on
	 *TIMER0_STOP 		= 0b0000 0000 = 0,
	 *TIMER0_1_PS 		= 0b0000 0001 = 1,
	 *TIMER0_8_PS 		= 0b0000 0010 = 2,
	 *TIMER0_64_PS 		= 0b0000 0011 = 3,
	 *TIMER0_256_PS 	= 0b0000 0100 = 4,
	 *TIMER0_1024_PS 	= 0b0000 0101 = 5,
	 *EXTERNAL0_FALLING = 0b0000 0110 = 6,
	 *EXTERNAL0_RISING 	= 0b0000 0111 = 7
	 */
	TCCR0 &= 0xF8; /*0b1111 1000*/
	TCCR0 |= ptr_timer0->prescaler;

	/*timer starts when setting the prescaler with a value not 0 (setting a value to clock select bits)*/
}

void TIMER0_stop(void)
{

	/*timer0 stop when clearing the clock select bits*/
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
}

void TIMER0_setTimerValue(u8 value)
{
	/*setting the value of TCNT0 (timer counter register of timer 0) to the value of the user*/
	TCNT0 = value;
}

void TIMER0_getTimerValue(u8 *pValue)
{
	/*fill the buffer of the user with the value of TCNT0 (timer counter register of timer 0)*/
	*pValue = TCNT0;
}

void Timer0_setOutputCompareValue(u8 value)
{
	/*setting the value of OCR0 (output compare register of timer 0) to the value of the user*/
	OCR0 = value;
}

void TIMER0_OVF_interruptEnable(void)
{
	/*enable the timer0 overflow interrupt by setting bit TOIE0 to 1*/
	SET_BIT(TIMSK, TOIE0);
}

void TIMER0_OVF_interruptDisable(void)
{
	/*disable the timer0 overflow interrupt by clearing bit TOIE0*/
	CLR_BIT(TIMSK, TOIE0);
}

void TIMER0_OC_interruptEnable(void)
{
	/*enable the timer0 output compare match interrupt by setting bit OCIE0 to 1*/
	SET_BIT(TIMSK, OCIE0);
}

void TIMER0_OC_interruptDisable(void)
{
	/*disable the timer0 output compare match interrupt by clearing bit OCIE0*/
	CLR_BIT(TIMSK, OCIE0);
}

void __vector_10(void)
{
	/*called when OCF0 is set to one*/
	if (TIMER0_OC_func != NULL)
		TIMER0_OC_func();
}

void __vector_11(void)
{
	/*called when TOV0 is set to one*/
	if (TIMER0_OVF_func != NULL)
		TIMER0_OVF_func();
}

void TIMER0_OVF_setCallBackFunction(void (*ptr_callBackFunction)(void))
{
	/*setting the call back function with the user function*/
	TIMER0_OVF_func = ptr_callBackFunction;
}

void TIMER0_OC_setCallBackFunction(void (*ptr_callBackFunction)(void))
{
	/*setting the call back function with the user function*/
	TIMER0_OC_func = ptr_callBackFunction;
}


