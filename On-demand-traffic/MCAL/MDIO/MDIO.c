/*
 * MDIO.c
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */


#include "MDIO.h"


void   MDIO_void_setPin_value(port_type port,pin_type pin,value_type value)
{
     if(value == HIGH)
     {
    	switch(port)
    	{
    	case PORTA_ID: SET_BIT(PORTA,pin); break;
    	case PORTB_ID: SET_BIT(PORTB,pin); break;
    	case PORTC_ID: SET_BIT(PORTC,pin); break;
    	case PORTD_ID: SET_BIT(PORTD,pin); break;
    	}
     }
     else if(value == LOW)
     {
    	switch(port)
		{
		case PORTA_ID: CLR_BIT(PORTA,pin); break;
		case PORTB_ID: CLR_BIT(PORTB,pin); break;
		case PORTC_ID: CLR_BIT(PORTC,pin); break;
		case PORTD_ID: CLR_BIT(PORTD,pin); break;
		}
     }
}
void   MDIO_void_setPin_direction(port_type port,pin_type  pin,direction_type direction)
{
    if(direction == INPUT)
    {
          switch(port)
          {
          case PORTA_ID : CLR_BIT(DDRA,pin);break;
          case PORTB_ID : CLR_BIT(DDRB,pin);break;
          case PORTC_ID : CLR_BIT(DDRC,pin);break;
          case PORTD_ID : CLR_BIT(DDRD,pin);break;
          }
    }
    else if (direction == OUTPUT)
    {
    	switch(port)
		  {
		  case PORTA_ID : SET_BIT(DDRA,pin);break;
		  case PORTB_ID : SET_BIT(DDRB,pin);break;
		  case PORTC_ID : SET_BIT(DDRC,pin);break;
		  case PORTD_ID : SET_BIT(DDRD,pin);break;
		  }

    }
}
value_type MDIO_value_type_getPin_value(port_type port,pin_type pin)
{
	value_type ret_val;
    switch(port)
    {
      case PORTA_ID : ret_val = GET_BIT(PINA,pin);break;
	  case PORTB_ID : ret_val = GET_BIT(PINB,pin);break;
	  case PORTC_ID : ret_val = GET_BIT(PINC,pin);break;
	  case PORTD_ID : ret_val = GET_BIT(PIND,pin);break;
    }
    return ret_val;
}

void DIO_toggle(port_type portNumber, pin_type pinNumber)
{
	/*

		This function toggle the state of the pin (if it 0 it makes it 1, if it 1 it makes it 0)
	*/
	switch (portNumber)
	{
	case PORTA_ID:
		TOG_BIT(PORTA, pinNumber);
		break;
	case PORTB_ID:
		TOG_BIT(PORTB, pinNumber);
		break;
	case PORTC_ID:
		TOG_BIT(PORTC, pinNumber);
		break;
	case PORTD_ID:
		TOG_BIT(PORTD, pinNumber);
		break;
	default:
		// Error handling
		break;
	}
}

 void MDIO_void_setPort_value(port_type port,u8 value)
 {
	 switch(port)
	 {
		  case PORTA_ID : PORTA =  value ;break;
		  case PORTB_ID : PORTB =  value ;break;
		  case PORTC_ID : PORTC =  value ;break;
		  case PORTD_ID : PORTD =  value ;break;
	 }

 }
 void MDIO_void_setPort_direction(port_type port,u8 direction)
 {
		switch(port)
		 {
			  case PORTA_ID : DDRA = direction;break;
			  case PORTB_ID : DDRB = direction;break;
			  case PORTC_ID : DDRC = direction;break;
			  case PORTD_ID : DDRD = direction;break;
		 }


 }
