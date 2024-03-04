/*
 * MDIO.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef MDIO_MDIO_H_
#define MDIO_MDIO_H_
#include "../../UTALITIES/LBIT_MATH.h"
#include "../../UTALITIES/LSTD_TYPES.h"
#include "../../UTALITIES/REGISTERS.h"
typedef enum
{
	PORTA_ID=0,
	PORTB_ID,
	PORTC_ID,
	PORTD_ID
}port_type;

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}pin_type;
typedef enum
{
	LOW=0,
	HIGH
}value_type;
typedef enum
{
	INPUT=0,
	OUTPUT
}direction_type;

void       MDIO_void_setPin_value(port_type port,pin_type pin,value_type value);
void       MDIO_void_setPin_direction(port_type port,pin_type  pin,direction_type direction);
value_type MDIO_value_type_getPin_value(port_type port,pin_type pin);
void DIO_toggle(port_type portNumber, pin_type pinNumber);
void MDIO_void_setPort_value(port_type port,u8 value);
void MDIO_void_setPort_direction(port_type port,u8 direction);

#endif /* MDIO_MDIO_H_ */
