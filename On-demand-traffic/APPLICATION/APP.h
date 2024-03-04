/*
 * APP.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef APP_H_
#define APP_H_

#include "../UTALITIES/LSTD_TYPES.h"
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/EXTI/EXTI.h"
#include "../MCAL/GINT/GINT.h"
#include "../ECUAL/BUTTON/BUTTON.h"
#include "../ECUAL/HLED/HLED.h"

typedef enum
{
    CAR,
    YELLOW_CAR,
    MAN,
    YELLOW_MAN
} EN_systemState_t;

/*
 * takes void
 * returns void
 * this function contains the flowchart of the system and start the system
 */
void APP_start(void);

/*
 * takes pointer to ST_timer0_t to operate with it
 * returns void
 * this function is a delay for 1/10 of the sec
 */
void delayOneTenthSec(ST_timer0_t *);

/*
 * takes void
 * returns void
 * this function is the Interrupt Serviece Routine for timer0
 */
void timerISR(void);

/*
 * takes void
 * returns void
 * this function is the Interrupt Serviece Routine for exti0
 */
void ISR(void);

#endif /* APP_H_ */
