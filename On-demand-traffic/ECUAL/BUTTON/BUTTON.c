/*
 * BUTTON.c
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */


#include "BUTTON.h"

/*
 * set pin connected to the button as input
 */
void Button_init(port_type buttonPort, pin_type buttonPin)
{
	MDIO_void_setPin_direction(buttonPort, buttonPin, INPUT);
}

/*
 *read the pin value
 */
value_type Button_get_state(port_type buttonPort, pin_type buttonPin, u8 value)
{

	return MDIO_value_type_getPin_value(buttonPort, buttonPin);
}
