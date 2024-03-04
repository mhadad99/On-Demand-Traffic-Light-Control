/*
 * EXTI.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef EXTI_EXTI_H_
#define EXTI_EXTI_H_

#include "../../UTALITIES/LBIT_MATH.h"
#include "../../UTALITIES/LSTD_TYPES.h"
#include "../../UTALITIES/REGISTERS.h"


/*bits definition*/
/*Interrupt Sense Control 0 bit 0*/
#define ISC00 0
/*Interrupt Sense Control 0 bit 1*/
#define ISC01 1
/*Interrupt Sense Control 1 bit 0*/
#define ISC10 2
/*Interrupt Sense Control 1 bit 1*/
#define ISC11 3
/*Interrupt Sense Control 2*/
#define ISC2 6
/*External Interrupt Request 0 Enable*/
#define INT0 6
/*External Interrupt Request 1 Enable*/
#define INT1 7
/*External Interrupt Request 2 Enable*/
#define INT2 5
/*External Interrupt Flag 0*/
#define INTF0 6
/*External Interrupt Flag 1*/
#define INTF1 7
/*External Interrupt Flag 2*/
#define INTF2 5

typedef enum
{
	/*interrupt fired if the logic is 0*/
    EXTI_LOW_LEVEL,
	/*interrupt fired if the logic is 1 and become 0*/
    EXTI_FALLING_EDGE,
	/*interrupt fired if the logic is 0 and become 1*/
    EXTI_RISING_EDGE,
	/*interrupt fired if the logic is changed*/
    EXTI_CHANGING
} senseControl_type;

typedef enum
{
    EXTI_OK,
    EXTI_WRONG_SENSE_CTRL
} extiError_type;

/* this function is to initialize the external interrupt 0
 * takes senseControl_type as sensControl
 * returns extiError_type (EXTI_OK, EXTI_WRONG_SENSE_CTRL)
 */
extiError_type EXTI0_init(senseControl_type);

/* this function is to initialize the external interrupt 1
 * takes senseControl_type as sensControl
 * returns extiError_type (EXTI_OK, EXTI_WRONG_SENSE_CTRL)
 */
extiError_type EXTI1_init(senseControl_type);

/* this function is to initialize the external interrupt 2
 * takes senseControl_type as sensControl this interrupt is only rising or falling nothing else
 * returns extiError_type (EXTI_OK, EXTI_WRONG_SENSE_CTRL)
 */
extiError_type EXTI2_init(senseControl_type);

/* this function is to set the call back function of external interrupt 0
 * takes a pointer to function takes void and returns void
 * returns void
 */
void EXTI0_setCallBack(void (*ptr_callBackFunction)(void));

/* this function is to set the call back function of external interrupt 1
 * takes a pointer to function takes void and returns void
 * returns void
 */
void EXTI1_setCallBack(void (*ptr_callBackFunction)(void));

/* this function is to set the call back function of external interrupt 2
 * takes a pointer to function takes void and returns void
 * returns void
 */
void EXTI2_setCallBack(void (*ptr_callBackFunction)(void));

#endif /* EXTI_EXTI_H_ */
