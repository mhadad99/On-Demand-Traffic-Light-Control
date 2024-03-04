/*
 * LBIT_MATH.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef LBIT_MATH_H_
#define LBIT_MATH_H_

#define SET_BIT(Reg,Bit)  Reg |= (1<<(Bit))
#define CLR_BIT(Reg,Bit)  Reg &= ~(1<<(Bit))
#define TOG_BIT(Reg,Bit)  Reg ^= (1<<(Bit))
#define GET_BIT(Reg,Bit)  (Reg>>(Bit)) & 0x01

#endif /* LBIT_MATH_H_ */
