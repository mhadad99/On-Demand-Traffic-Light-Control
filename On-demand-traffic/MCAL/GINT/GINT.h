/*
 * GINT.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef GINT_GINT_H_
#define GINT_GINT_H_

/*
 * Includes the headers files
 */
#include "../../UTALITIES/LBIT_MATH.h"
#include "../../UTALITIES/LSTD_TYPES.h"
#include "../../UTALITIES/REGISTERS.h"

/*
 * bits definition
*/
#define I 7

/*
 * this function to enable the global interrupt
 * returns void
 * takes void
 *
 */
void GIE_enable(void);

/*
 *  this function  disables the global interrupt
 * returns void
 * takes void
 *
 */
void GIE_disable(void);

#endif /* GINT_GINT_H_ */
