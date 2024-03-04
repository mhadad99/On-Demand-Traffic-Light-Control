/*
 * HLED.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef HLED_HLED_H_
#define HLED_HLED_H_

#include "../../MCAL/MDIO/MDIO.h"

/**
 *functions prototypes
 */
void LED_init(port_type ledPort, pin_type ledPin);
void LED_on(port_type ledPort, pin_type ledPin);
void LED_off(port_type ledPort, pin_type ledPin);
void LED_toggle(port_type ledPort, pin_type ledPin);

#endif /* HLED_HLED_H_ */
