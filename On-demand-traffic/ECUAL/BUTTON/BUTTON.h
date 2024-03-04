/*
 * BUTTON.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include "../../MCAL/MDIO/MDIO.h"

// define button1 port and pin
#define EXT_INT_BUTTON_PORT PORT_D
#define EXT_INT_BUTTON_PIN PIN2

//functions prototypes

//initialization
void Button_init(port_type buttonPort, pin_type buttonPin);

// get button status
u8 Button_get_state(port_type buttonPort, pin_type buttonPin, u8 value);

#endif /* BUTTON_BUTTON_H_ */
