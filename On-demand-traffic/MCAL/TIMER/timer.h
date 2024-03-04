/*
 * timer.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef TIMER__H_
#define TIMER__H_

/*
 * Includes the headers files
 */
#include "../../UTALITIES/LSTD_TYPES.h"
#include "../../UTALITIES/LBIT_MATH.h"
#include "../../UTALITIES/REGISTERS.h"

/*bits definition*/
#define CS00 0  /*Clock Select 0 of timer0*/
#define CS01 1  /*Clock Select 1 of timer0*/
#define CS02 2  /*Clock Select 2 of timer0*/
#define WGM01 3 /*Waveform Generation Mode 1 of timer0*/
#define COM00 4 /*Compare Output Mode 0 of timer0*/
#define COM01 5 /*Compare Output Mode 1 of timer0*/
#define WGM00 6 /*Waveform Generation Mode 0 of timer0*/
#define FOC0 7  /*Force Output Compare of timer0*/
#define TOIE0 0 /*Timer/Counter0 Overflow Interrupt Enable*/
#define OCIE0 1 /*Timer/Counter0 Output Compare Match Interrupt Enable*/

typedef enum {
	TIMER0_STOP,
	TIMER0_1_PS,
	TIMER0_8_PS,
	TIMER0_64_PS,
	TIMER0_256_PS,
	TIMER0_1024_PS,
	EXTERNAL0_FALLING, /*external trigger at falling edge*/
	EXTERNAL0_RISING /*external trigger at rising edge*/
} EN_timer0Prescaler_t;

typedef enum {
	TIMER0_NORMAL, TIMER0_PHASECORRECT, TIMER0_CTC, /*Clear Timer at Compare match*/
	TIMER0_FAST_PWM
} EN_timer0Mode_t;

typedef enum {
	OC0_DISCONNECTED, OC0_TOGGLE, OC0_NON_INVERTING, OC0_INVERTING
} EN_oc0Mode_t;

typedef enum {
	TIMER0_OK, TIMER0_WRONG_MODE, TIMER0_WRONG_OC_MODE
} EN_timer0Error_t;

typedef struct {
	EN_timer0Mode_t mode;
	EN_timer0Prescaler_t prescaler;
	EN_oc0Mode_t ocMode;
} ST_timer0_t;

/*TIMER0 functions*/

/* this function is to initialise the mode of timer0 and the output compare mode
 * takes pointer to ST_timer0_t
 * returns EN_timer0Error_t (TIMER0_OK, TIMER0_WRONG_MODE, TIMER0_WRONG_OC_MODE)
 */
EN_timer0Error_t TIMER0_init(ST_timer0_t *);

/* this function is to set the prescaler of the timer0 (start it)
 * takes pointer to ST_timer0_t
 * returns void
 */
void TIMER0_start(ST_timer0_t *);

/* this function is to set the prescaler of the timer0 to zero (stop it)
 * takes void
 * returns void
 */
void TIMER0_stop(void);

/* this function is to set initial value of counting
 * takes u8 as the value
 * returns void
 */
void TIMER0_setTimerValue(u8);

/* this function is to get the counter register value
 * takes pointer to u8 as a buffer to the vlaue
 * returns void
 */
void TIMER0_getTimerValue(u8 *);

/* this function is to set the output compare match register
 * takes u8 as the value
 * returns void
 */
void Timer0_setOutputCompareValue(u8);

/* this function is to enable the overflow interrupt (the GIE must be enabled to)
 * takes void
 * returns void
 */
void TIMER0_OVF_interruptEnable(void);

/* this function is to disable the overflow interrupt
 * takes void
 * returns void
 */
void TIMER0_OVF_interruptDisable(void);

/* this function is to enable the output compare match interrupt (the GIE must be enabled to)
 * takes void
 * returns void
 */
void TIMER0_OC_interruptEnable(void);

/* this function is to disable the output compare match interrupt
 * takes void
 * returns void
 */
void TIMER0_OC_interruptDisable(void);

/* this function is to set the overflow interrupt callback function (ISR)
 * takes pointer to the function
 * returns void
 */
void TIMER0_OVF_setCallBackFunction(void (*ptr_callBackFunction)(void));

/* this function is to set the output compare match interrupt callback function (ISR)
 * takes pointer to the function
 * returns void
 */
void TIMER0_OC_setCallBackFunction(void (*ptr_callBackFunction)(void));

#endif /*TIMER__H_*/

