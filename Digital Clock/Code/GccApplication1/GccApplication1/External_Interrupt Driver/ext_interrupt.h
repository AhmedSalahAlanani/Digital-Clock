//****************************************************************************
#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#include <avr/interrupt.h>
#include "ext_interrupt_CONFIG.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"


//	Functions Prototypes
void Init_Ext_INT0(void);
void Init_Ext_INT1(void);
void Init_Ext_INT2(void);
void Clear_INT_Flag(u8 INTFX);
u8 Get_INT_Flag(u8 INTFX);

#endif
//****************************************************************************

