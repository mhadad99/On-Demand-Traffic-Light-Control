/*
 * REGISTERS.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

/*Status Register*/
#define SREG (*(volatile u8 *)0x5F)

/*DIO registers*/
/*Data Direction Register*/
#define DDRA  (*(volatile u8 *)0x3A)
#define DDRB  (*(volatile u8 *)0x37)
#define DDRC  (*(volatile u8 *)0x34)
#define DDRD  (*(volatile u8 *)0x31)

/*Port Data Register*/
#define PORTA (*(volatile u8 *)0x3B)
#define PORTB (*(volatile u8 *)0x38)
#define PORTC (*(volatile u8 *)0x35)
#define PORTD (*(volatile u8 *)0x32)

/*Input Pins Address*/
#define PINA  (*(volatile u8 *)0x39)
#define PINB  (*(volatile u8 *)0x36)
#define PINC  (*(volatile u8 *)0x33)
#define PIND  (*(volatile u8 *)0x30)

/*TIMERS registers*/

/*Timer/Counter Interrupt Mask Register*/
#define TIMSK (*(volatile u8 *)0x59)
/*Timer/Counter Interrupt Flag Register*/
#define TIFR  (*(volatile u8 *)0x58)

/*TIMER0*/
/*Timer/Counter Control Register*/
#define TCCR0 (*(volatile u8 *)0x53)
/*Timer/Counter Register*/
#define TCNT0 (*(volatile u8 *)0x52)
/*Output Compare Register*/
#define OCR0  (*(volatile u8 *)0x5C)

/*EXTI registers*/
/*MCU Control Register*/
#define MCUCR  (*(volatile u8  *)0x55)
/*MCU Control and Status Register*/
#define MCUCSR (*(volatile u8  *)0x54)
/*General Interrupt Control Register*/
#define GICR   (*(volatile u8  *)0x5B)

#define GIFR   (*(volatile u8  *)0x5A)

#endif /* REGISTERS_H_ */
