/*
 * EXTI.c
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#include "EXTI.h"

/*call back function of EXTI 0*/
void (*EXTI0_func)(void) = NULL;
/*call back function of EXTI 1*/
void (*EXTI1_func)(void) = NULL;
/*call back function of EXTI 2*/
void (*EXTI2_func)(void) = NULL;

/*from interrupt vectors table in the datasheet*/
/*external interrupt 0*/
void __vector_1(void) __attribute__((signal));
/*external interrupt 0*/
void __vector_2(void) __attribute__((signal));
/*external interrupt 0*/
void __vector_3(void) __attribute__((signal));

extiError_type EXTI0_init(senseControl_type senseControl) {
	extiError_type ret = EXTI_OK;

	/*switch over sense control*/
	switch (senseControl) {
	/*ISC00 and ISC01 should be 0*/
	case EXTI_LOW_LEVEL:
		CLR_BIT(MCUCR, ISC00);
		CLR_BIT(MCUCR, ISC01);
		break;
	/*ISC00 should be 1 and ISC01 should be 0*/
	case EXTI_CHANGING:
		SET_BIT(MCUCR, ISC00);
		CLR_BIT(MCUCR, ISC01);
		break;
	/*ISC00 should be 0 and ISC01 should be 1*/
	case EXTI_FALLING_EDGE:
		CLR_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
		break;
	/*ISC00 and ISC01 should be 1*/
	case EXTI_RISING_EDGE:
		SET_BIT(MCUCR, ISC00);
		SET_BIT(MCUCR, ISC01);
		break;

	default:
		/*passed sense control is wrong*/
		ret = EXTI_WRONG_SENSE_CTRL;
		break;
	}

	/*enable the external interrupt 0 by setting 1 to bit INT0*/
	SET_BIT(GICR, INT0);

	return ret;
}

extiError_type EXTI1_init(senseControl_type senseControl) {
	extiError_type ret = EXTI_OK;
	switch (senseControl) {
	case EXTI_LOW_LEVEL: /*ISC10 and ISC11 should be 0*/
		CLR_BIT(MCUCR, ISC10);
		CLR_BIT(MCUCR, ISC11);
		break;
	case EXTI_CHANGING: /*ISC10 should be 1 and ISC11 should be 0*/
		SET_BIT(MCUCR, ISC10);
		CLR_BIT(MCUCR, ISC11);
		break;
	case EXTI_FALLING_EDGE: /*ISC10 should be 0 and ISC11 should be 1*/
		CLR_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
		break;
	case EXTI_RISING_EDGE: /*ISC10 and ISC11 should be 1*/
		SET_BIT(MCUCR, ISC10);
		SET_BIT(MCUCR, ISC11);
		break;

	default:
		/*passed sense control is wrong*/
		ret = EXTI_WRONG_SENSE_CTRL;
		break;
	}

	/*enable the external interrupt 1 by setting 1 to bit INT1*/
	SET_BIT(GICR, INT1);

	return ret;
}

extiError_type EXTI2_init(senseControl_type senseControl) {
	extiError_type ret = EXTI_OK;

	/*switch over sense control*/
	switch (senseControl) {
	case EXTI_FALLING_EDGE: /*ISC2 should be 0*/
		CLR_BIT(MCUCSR, ISC2);
		break;
	case EXTI_RISING_EDGE: /*ISC2 should be 1*/
		SET_BIT(MCUCSR, ISC2);
		break;

	default:
		/*passed sense control is wrong (this interrupt has only falling and rising sense control not else*/
		ret = EXTI_WRONG_SENSE_CTRL;
		break;
	}

	/*enable the external interrupt 2 by setting 1 to bit INT2*/
	SET_BIT(GICR, INT2);

	return ret;
}

void EXTI0_setCallBack(void (*ptr_callBackFunction)(void)) {
	/*setting the call back function with the user function*/
	EXTI0_func = ptr_callBackFunction;
}

void __vector_1(void) {
	/*called when INTF0 is set to one*/
	if (EXTI0_func != NULL)
		EXTI0_func();
}

void EXTI1_setCallBack(void (*ptr_callBackFunction)(void)) {
	/*setting the call back function with the user function*/
	EXTI1_func = ptr_callBackFunction;
}

void __vector_2(void) {
	/*called when INTF1 is set to one*/
	if (EXTI1_func != NULL)
		EXTI1_func();
}

void EXTI2_setCallBack(void (*ptr_callBackFunction)(void)) {
	/*setting the call back function with the user function*/
	EXTI2_func = ptr_callBackFunction;
}

void __vector_3(void) {
	/*called when INTF2 is set to one*/
	if (EXTI2_func != NULL)
		EXTI2_func();
}
