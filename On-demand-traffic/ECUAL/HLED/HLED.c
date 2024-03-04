/*
 * HLED.c
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */


#include "HLED.h"
void LED_init(port_type ledPort, pin_type ledPin)
{
	// let LED as output
	MDIO_void_setPin_direction(ledPort, ledPin, OUTPUT);
}
void LED_on(port_type ledPort, pin_type ledPin)
{
	// write high on the LED
	MDIO_void_setPin_value(ledPort, ledPin, HIGH);
}
void LED_off(port_type ledPort, pin_type ledPin)
{
	// write low on the LED
	MDIO_void_setPin_value(ledPort, ledPin, LOW);
}
void LED_toggle(port_type ledPort, pin_type ledPin)
{
	// toggle the LED
	DIO_toggle(ledPort, ledPin);
}
