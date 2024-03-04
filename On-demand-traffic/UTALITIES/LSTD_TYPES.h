/*
 * LSTD_TYPES.h
 *
 *  Created on: Oct 16, 2022
 *      Author: mhadd
 */

#ifndef LSTD_TYPES_H_
#define LSTD_TYPES_H_

typedef unsigned char         u8;
typedef signed char           s8;
typedef short unsigned int   u16;
typedef short signed int     s16;
typedef long unsigned int    u32;
typedef long signed int      s32;
typedef float                f32;
typedef double               f64;
typedef long double          f80;




#define NULL ((void *)0)

typedef enum
{
    FALSE,
    TRUE
} bool_type;

#endif /* LSTD_TYPES_H_ */
