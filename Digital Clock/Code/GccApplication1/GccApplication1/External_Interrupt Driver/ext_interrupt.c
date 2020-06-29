//****************************************************************************
#include "ext_interrupt.h"


void Init_Ext_INT0(void)
{
	asm volatile ("CLI");	//cli();

	#if (Interrupt_0_SenseControl == 0)
		CLR_BIT(MCUCR,ISC00);
		CLR_BIT(MCUCR,ISC01);
			
	#elif (Interrupt_0_SenseControl == 1)
		SET_BIT(MCUCR,ISC00);
		CLR_BIT(MCUCR,ISC01);
		
	#elif (Interrupt_0_SenseControl == 2)
		CLR_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);

	#elif (Interrupt_0_SenseControl == 3)
		SET_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
	
	#endif
	
	SET_BIT(GICR,INT0);		//	Enable External Interrupt Request 1 
	asm volatile ("SEI");	//sei();
}


void Init_Ext_INT1(void)
{
	asm volatile ("CLI");	//cli();

	#if (Interrupt_1_SenseControl == 0)
		CLR_BIT(MCUCR,ISC10);
		CLR_BIT(MCUCR,ISC11);
	
	#elif (Interrupt_1_SenseControl == 1)
		SET_BIT(MCUCR,ISC10);
		CLR_BIT(MCUCR,ISC11);
		
	#elif (Interrupt_1_SenseControl == 2)
		CLR_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);

	#elif (Interrupt_1_SenseControl == 3)
		SET_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
		
	#endif
	
	SET_BIT(GICR,INT1);
	asm volatile ("SEI");	//sei();
}


void Init_Ext_INT2(void)
{
	asm volatile ("CLI");	//cli();

	#if (Interrupt_2_SenseControl == 0)
		CLR_BIT(MCUCSR,ISC2);
	
	#elif (Interrupt_2_SenseControl == 1)
		SET_BIT(MCUCSR,ISC2);
	
	#endif
	
	SET_BIT(GICR,INT2);
	asm volatile ("SEI");	//sei();
}


void Clear_INT_Flag(u8 INTFX)
{
	SET_BIT(GIFR,INTFX);
}


u8 Get_INT_Flag(u8 INTFX)
{
	return (GET_BIT(GIFR,INTFX));
}
//****************************************************************************

