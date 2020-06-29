//****************************************************************************
 #ifndef	TIMER_1_CONFIG_H_
 #define	TIMER_1_CONFIG_H_
 

/* Select Timer_1 Mode */
#define			TIMER_1_MODE								1					  // Choose from (0) to (4)

/* Select the Clock for Timer_1 */
#define			Clock_Select								4					  // From (0) to (7) 

//	For Non PWM Mode only
#define			Compare_OutputMode							0					  // From (0) to (7)

//	For CTC Mode only
#define			CTC_TopValue								0					  // (0) for OCR1A, (1) for ICR1 

/* Select Timer_1 Interrupt Enable */						
#define			Timer_1_Interrupt_select					2					  // Form (0) to (3)


#endif
//****************************************************************************