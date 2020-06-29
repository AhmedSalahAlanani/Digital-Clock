/*
 * GccApplication1.c
 *
 * Created: 29-Jun-20 1:27:32 AM
 * Author : Ahmed Salah
 */ 

#include "External_Interrupt Driver/ext_interrupt.h"
#include "DIO Driver/DIO_INIT.h"
#include "Timer_1/Timer_1.h"


//	Application Defined Constants
#define		F_CPU				16000000UL
#define		Prescaler			256


//	Global Variables
static volatile u8 Flags = 0;
static volatile u8 SevenSegment_Array[6]  = {0};


//	Function Prototypes
void DIO_INIT(void);
void Timer_Handler(void);
void Reset_Handler(void);
void Update_Time(void);
void NumberSet0_Handler(u8 Pos);
void NumberSet1_Handler(u8 Pos);
void Display_Time(void);


int main(void)
{
    //	Initializations
	DIO_INIT();
	Init_Ext_INT0();							
	OCR1A_Write(0x24);
	OCR1A_Write(F_CPU/Prescaler);		
	TIMER1_COMPA_Callback(Timer_Handler);
	Timer_1_Interrupt_Enable();
	Timer1_CTC_Init();
	
    while (1) 
    {
		//Iterate and Display
		Display_Time();
		
		if (GET_BIT(Flags,0))
		{
			//Update
			Update_Time();			
				
			//Reset Bit0
			CLR_BIT(Flags,0);	
		}
		
		
		if (GET_BIT(Flags,1))
		{
			//Reset
			Reset_Handler();
			
			//Reset Bit1
			CLR_BIT(Flags,1);	
		}
	
    }
}


ISR(INT0_vect)
{
	SET_BIT(Flags,1);
}


void Reset_Handler(void)
{
	//Reset all values to Zero
	for (u8 i =0; i<6; i++)
	{
		SevenSegment_Array[i]  = 0;	
	}

}


void Update_Time(void)
{
	//Increase One Second
	NumberSet0_Handler(0);	 
}


void NumberSet0_Handler(u8 Pos)
{
	if (SevenSegment_Array[Pos] == 9)
	{
		SevenSegment_Array[Pos] = 0;
		NumberSet1_Handler(Pos+1);
	}
	else
	{
		//Handle 24-Hour Case
		if ((Pos==4)&&(SevenSegment_Array[Pos]==3)&&(SevenSegment_Array[Pos+1]==2))
		{
			//Reset
			Reset_Handler();
		} 
		else
		{
			(SevenSegment_Array[Pos])++ ;
		}
	}
}


void NumberSet1_Handler(u8 Pos)
{
	if (SevenSegment_Array[Pos] == 5)
	{
		SevenSegment_Array[Pos] = 0;
		NumberSet0_Handler(Pos+1);
	}
	else
	{
		(SevenSegment_Array[Pos])++ ;
	}
}



void Display_Time(void)
{
	for (u8 i =0; i<6; i++)
	{
		DIO_VidSetPortValue(portB,LOW);
		DIO_VidWritePortValue(PORTC_REG,SevenSegment_Array[i]);
		DIO_VidSetPinValue(i,portB,HIGH);		
	}
}


void Timer_Handler(void)
{
	SET_BIT(Flags,0);
}


void DIO_INIT(void)
{
	/*	Configure Port B  */
	for (u8 i = 0 ; i<6 ; i++)
	{
		DIO_VidSetPinDirection(i,portB,OUTPUT);
	}
	
	
	/*	Configure Port C  */
	for (u8 i = 0 ; i<4 ; i++)
	{
		DIO_VidSetPinDirection(i,portC,OUTPUT);
	}
	
	
	/*	Configure Port D  */
	DIO_VidSetPinDirection(2,portD,INPUT);
	
	//Enable Pull-Up Resistor
	DIO_VidSetPinValue(2,portD,HIGH);
	
}