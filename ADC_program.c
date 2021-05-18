/*************************************************/
/************** Name : Abdalrahman Magdy  **********/
/**************  Date : 17/9/2020      *********/
/**************  SWC  : ADC            ********/
/**************  Version : 1.0         *******/
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

static void(*ADC_pfNotification)(u16)=NULL;
static u8 ADC_u8BusyFlag=0;
void ADC_voidInit(void)
{
	/* 1- Select V refrance = AVCC
     2- Right Adjust 
     3- Disable AutoTrigger 
     4- Select CLK/64  
	 5- Enable ADC
	 */
#if		ADC_u8_VOLTAGE_REFRANCE == ADC_u8_VOLTAGE_REFRANCE_AREF
	CLR_BIT(ADC_u8_ADMUX_REG,7);
	CLR_BIT(ADC_u8_ADMUX_REG,6);
#elif	ADC_u8_VOLTAGE_REFRANCE == ADC_u8_VOLTAGE_REFRANCE_AVCC
	CLR_BIT(ADC_u8_ADMUX_REG,7);
	SET_BIT(ADC_u8_ADMUX_REG,6);
#elif	ADC_u8_VOLTAGE_REFRANCE == ADC_u8_VOLTAGE_REFRANCE_2_56V
	SET_BIT(ADC_u8_ADMUX_REG,7);
	SET_BIT(ADC_u8_ADMUX_REG,6);
#else
#error	"Wrong Choice"
#endif
#if ADC_u8_CONVERSION_MODE == ADC_u8_SINGLE_CONVERSION_MODE
	CLR_BIT(ADC_u8_ADMUX_REG,5);
#elif	ADC_u8_CONVERSION_MODE == ADC_u8_FREE_RUNNING_CONVERSION_MODE
	SET_BIT(ADC_u8_ADMUX_REG,5);
	CLR_BIT(ADC_u8_SFIOR_REG,7);
	CLR_BIT(ADC_u8_SFIOR_REG,6);
	CLR_BIT(ADC_u8_SFIOR_REG,5);
	SET_BIT(ADC_u8_ADCSRA_REG,6);
#elif	ADC_u8_CONVERSION_MODE == ADC_u8_ANALOG_COMPARTOR_CONVERSION_MODE
	SET_BIT(ADC_u8_ADMUX_REG,5);
	CLR_BIT(ADC_u8_SFIOR_REG,7);
	CLR_BIT(ADC_u8_SFIOR_REG,6);
	SET_BIT(ADC_u8_SFIOR_REG,5);
#elif	ADC_u8_CONVERSION_MODE == ADC_u8_EXTI0_CONVERSION_MODE
	SET_BIT(ADC_u8_ADMUX_REG,5);
	CLR_BIT(ADC_u8_SFIOR_REG,7);
	SET_BIT(ADC_u8_SFIOR_REG,6);
	CLR_BIT(ADC_u8_SFIOR_REG,5);
#else
#error	"Wrong Choice"
#endif
	CLR_BIT(ADC_u8_ADMUX_REG,5);
	
	SET_BIT(ADC_u8_ADCSRA_REG,2);
	SET_BIT(ADC_u8_ADCSRA_REG,1);
	CLR_BIT(ADC_u8_ADCSRA_REG,0);
	
	SET_BIT(ADC_u8_ADCSRA_REG,7);
}
u8	ADC_u8VoltageRefrance(u8 Copy_VoltageRefrance)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_VoltageRefrance)
	{
	case ADC_u8_VOLTAGE_REFRANCE_AREF:
		CLR_BIT(ADC_u8_ADMUX_REG,7);
		CLR_BIT(ADC_u8_ADMUX_REG,6);
		break;
	case ADC_u8_VOLTAGE_REFRANCE_AVCC:
		CLR_BIT(ADC_u8_ADMUX_REG,7);
		SET_BIT(ADC_u8_ADMUX_REG,6);
		break;
	case ADC_u8_VOLTAGE_REFRANCE_2_56V:
		SET_BIT(ADC_u8_ADMUX_REG,7);
		SET_BIT(ADC_u8_ADMUX_REG,6);
		break;
	default: Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8	ADC_u8ConversionMode(u8 Copy_u8ConversionMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8ConversionMode)
	{
	case ADC_u8_SINGLE_CONVERSION_MODE:
		CLR_BIT(ADC_u8_ADMUX_REG,5);
	break;
	case ADC_u8_FREE_RUNNING_CONVERSION_MODE:
		SET_BIT(ADC_u8_ADMUX_REG,5);
		CLR_BIT(ADC_u8_SFIOR_REG,7);
		CLR_BIT(ADC_u8_SFIOR_REG,6);
		CLR_BIT(ADC_u8_SFIOR_REG,5);
		SET_BIT(ADC_u8_ADCSRA_REG,6);
	break;
	case ADC_u8_ANALOG_COMPARTOR_CONVERSION_MODE:
		SET_BIT(ADC_u8_ADMUX_REG,5);
		CLR_BIT(ADC_u8_SFIOR_REG,7);
		CLR_BIT(ADC_u8_SFIOR_REG,6);
		SET_BIT(ADC_u8_SFIOR_REG,5);
	break;
	case ADC_u8_EXTI0_CONVERSION_MODE:
		SET_BIT(ADC_u8_ADMUX_REG,5);
		CLR_BIT(ADC_u8_SFIOR_REG,7);
		SET_BIT(ADC_u8_SFIOR_REG,6);
		CLR_BIT(ADC_u8_SFIOR_REG,5);
	break;
	default:Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8   ADC_u8GetDigitalValue(u8 Copy_u8ChannelNb, u16 *Copy_pu16DigitalValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8ChannelNb < 32)  && (Copy_pu16DigitalValue != NULL))
    {
		/* Clear MUX 4..0 */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		/* Wait flag = 1 */
		while(GET_BIT(ADC_u8_ADCSRA_REG,4)== 0);
		/* Clear flag */
		SET_BIT(ADC_u8_ADCSRA_REG,4);
		/* Read The Digital Value */
		*Copy_pu16DigitalValue = ADC_u16_ADC_REG;
	}		
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	return Local_u8ErrorState;
}
u8 ADC_u8GetDigitalValueSynchNonBlocking(u8 Copy_u8ChannelNb ,u16 *Copy_pu16DigitalValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u32TimeOutCounter=0;
	if ((Copy_u8ChannelNb < 32)  && (Copy_pu16DigitalValue != NULL))
    {
		/* Clear MUX 4..0 */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		/* Wait flag = 1 */
		while((GET_BIT(ADC_u8_ADCSRA_REG,4)== 0) && (Local_u32TimeOutCounter < ADC_u32_TIME_OUT_MAX_VALUE))
		{
			Local_u32TimeOutCounter++;
		}
		if (GET_BIT(ADC_u8_ADCSRA_REG,4)!= 0)
		{
			/* Clear flag */
			SET_BIT(ADC_u8_ADCSRA_REG,4);
			/* Read The Digital Value */
			*Copy_pu16DigitalValue = ADC_u16_ADC_REG;
		}
		else
		{
			Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8  ADC_u8GetDigitalValueAsynch(u8 Copy_u8ChannelNb, void(*Copy_pfNotification)(u16))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8ChannelNb < 32)  && (Copy_pfNotification != NULL)&&(ADC_u8BusyFlag==0) )
	{
		/* Set Flag Busy */
		ADC_u8BusyFlag=1;
		/* Update Global Pointer To a Function  */
		ADC_pfNotification = Copy_pfNotification;
		/* Clear MUX 4..0 */
		ADC_u8_ADMUX_REG &= 0b11100000;
		/* Enable ADC Interrupt */
		SET_BIT(ADC_u8_ADCSRA_REG,3);
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNb;
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8  ADC_u8GetADCRegValue(u16 *Copy_pu16ADCValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pu16ADCValue != NULL)
	{
		/* Read ADC Register */
		*Copy_pu16ADCValue = ADC_u16_ADC_REG;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
void __vector_16(void)		__attribute__((signal));
void __vector_16(void)
{
	if(ADC_pfNotification != NULL)
	{
		/* Clear Flag */
		ADC_u8BusyFlag=0;
		/* Clear PIE of ADC */
		CLR_BIT(ADC_u8_ADCSRA_REG,3);
		/*Calling Notification Function*/
		ADC_pfNotification(ADC_u16_ADC_REG);
	}

}
