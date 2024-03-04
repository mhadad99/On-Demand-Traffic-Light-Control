/*
 * GINT.c
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */


#include "GINT.h"

void GIE_enable()
{
	/* Set bit I in the Status Register to enable the global interrupt*/
    SET_BIT(SREG, I);
}

void GIE_disable()
{
    /* Clear bit I in the Status Register to disable the global interrupt*/
    CLR_BIT(SREG, I);
}
