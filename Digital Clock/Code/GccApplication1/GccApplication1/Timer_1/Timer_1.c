//****************************************************************************
#include "Timer_1.h"



/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static void (*volatile G_TIMER1_COMPA)(void) ='\0' ;



/*******************************************************************************
 *									ISRs	    	                           *
 *******************************************************************************/
ISR(TIMER1_COMPA_vect)
{
	if (G_TIMER1_COMPA!='\0')
	{
		(*G_TIMER1_COMPA)();
	}
}



/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
 void Timer1_CTC_Init(void)
 {
	#if (TIMER_1_MODE==1)
		//CTC Mode
				
		//Select the Compare Output Mode
		#if (Compare_OutputMode==0)
			//Normal Port Operation
			CLR_BIT(TCCR1A,COM1A0);
			CLR_BIT(TCCR1A,COM1A1);
			CLR_BIT(TCCR1A,COM1B0);
			CLR_BIT(TCCR1A,COM1B1);
			
		#elif (Compare_OutputMode==1)
		#elif (Compare_OutputMode==2)
		#elif (Compare_OutputMode==3)
		#elif (Compare_OutputMode==4)
		#elif (Compare_OutputMode==5)
		#elif (Compare_OutputMode==6)
		#elif (Compare_OutputMode==7)
		
		#endif


		//Select the CTC Top Value
		#if (CTC_TopValue==0)
			//OCR1A
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);

		#elif (CTC_TopValue==1)
			//ICR1

		#endif

		//Select the Clock for Timer_1
		#if (Clock_Select==0)
		#elif (Clock_Select==1)
		#elif (Clock_Select==2)
		#elif (Clock_Select==3)
		
		#elif (Clock_Select==4)
			//Prescaler = 256
			CLR_BIT(TCCR1B,CS10);
			CLR_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS12);
			//	Reset Prescaler
			SET_BIT(SFIOR,PSR10);
			
		#elif (Clock_Select==5)
		#elif (Clock_Select==6)
		#elif (Clock_Select==7)

		#endif

	#endif
 }
 
 
 
 
 void Timer_1_Interrupt_Enable(void)
 {
	 #if (Timer_1_Interrupt_select==0)
	 
	 #elif (Timer_1_Interrupt_select==1)
	 #elif (Timer_1_Interrupt_select==2)
		//Timer/Counter1, Output Compare A Match Interrupt Enable
		SET_BIT(TIMSK,OCIE1A);
		asm volatile ("SEI");	//sei();
		
	 #elif (Timer_1_Interrupt_select==3)

	#endif
 }
 
 

 void OCR1A_Write(u16 value)
 {
	 //The HIGH Byte must be written before the LOW Byte
	 OCR1AH = (value >> 8);
	 OCR1AL = (value & 0xFF);
 }

 
 
 
/*
 * calling back function enable you to use Timer0_ISR
 * Any function passed to callback function will be
 * called in ISR
 */
void TIMER1_COMPA_Callback(void(*function_ptr) (void))
{
	G_TIMER1_COMPA = function_ptr ;
}
 
 //****************************************************************************