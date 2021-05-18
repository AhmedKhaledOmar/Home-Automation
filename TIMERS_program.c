/*************************************************/
/**************  Name : Abdalrahman Magdy  **********/
/**************  Date : 22/9/2020      *********/
/**************  SWC  : TIMERS         ********/
/**************  Version : 1.0         *******/
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h" 

#include "TIMERS_interface.h"
#include "TIMERS_private.h"
#include "TIMERS_config.h" 

/* Global Pointer To Func */
static void(*TIMERS_pfTimer0OVF)(void) = NULL;
static void(*TIMERS_pfTimer0CTC)(void) = NULL;
void TIMERS_voidTimer0Init(void)
{
	/* Select Timer1 Mode => 14 ICR1 = Top Value*/
		SET_BIT(TIMERS_u8_TCCR1A_REG,1);
		CLR_BIT(TIMERS_u8_TCCR1A_REG,0);
		SET_BIT(TIMERS_u8_TCCR1B_REG,4);
		SET_BIT(TIMERS_u8_TCCR1B_REG,3);

		/* Select HW Action on OC1A pin => Non Inverting */
		SET_BIT(TIMERS_u8_TCCR1A_REG,7);
		CLR_BIT(TIMERS_u8_TCCR1A_REG,6);

		/* Set Top Value in ICR1 */
		TIMERS_u16_ICR1_REG = 19999;

		/* Set Angle of Servo Motor */
		TIMERS_u16_OCR1A_REG = 1500;
//1249 599 0-> 2499  180 >> 3299
		/* Set Prescaler Value CLK/8 */
		CLR_BIT(TIMERS_u8_TCCR1B_REG,2);
		SET_BIT(TIMERS_u8_TCCR1B_REG,1);
		CLR_BIT(TIMERS_u8_TCCR1B_REG,0);


}
void TIMERS_voidTimer1SetCompareMatchValueA(u16 Copy_u16OCR1A)
{
	TIMERS_u16_OCR1A_REG = Copy_u16OCR1A;
}
void TIMERS_voidTimer0SetCompareMatchValue(u8 Copy_u8OCR0Value)
{
	TIMERS_u8_OCR0_REG = Copy_u8OCR0Value;
}
u8 TIMERS_u8Timer0SetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL)
	{
		TIMERS_pfTimer0OVF = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 TIMERS_u8Timer0CTCSetCallBack(void(*Copy_pf)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL)
	{
		TIMERS_pfTimer0CTC = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


/* ISR Of TIMER0 Overflow */
void __vector_11(void)    __attribute__((signal));
void __vector_11(void)
{
	static	u16 Local_u16CounterOVF = 0;
	Local_u16CounterOVF++;
	if(Local_u16CounterOVF == 39063)
	{
		/* Update preload Value */
		TIMERS_u8_TCNT0_REG = 244;
		/* Clear The OVF Counter */
		Local_u16CounterOVF = 0;
		/* Call App Function */
		if(TIMERS_pfTimer0OVF != NULL)
		{
			TIMERS_pfTimer0OVF();
		}
	}
}

/* ISR Of TIMER0 CTC*/
void __vector_10(void)    __attribute__((signal));
void __vector_10(void)
{
	static	u16 Local_u16CounterCTC = 0;
	Local_u16CounterCTC++;
	if(Local_u16CounterCTC == 1000)
	{
		/* Clear Counter */
		Local_u16CounterCTC =0;
		/* Call Back Function */

		if(TIMERS_pfTimer0CTC != NULL)
		{
			TIMERS_pfTimer0CTC();
		}
	}
}


