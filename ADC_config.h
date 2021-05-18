/*******************************************************************************/
/**********************    Name	: Abdalrahman Magdy ****************************/
/**********************    Date	: 17/09/2020         ****************************/
/**********************    SWC	: ADC     			****************************/
/********************    Version: 1.0   			****************************/
/*******************************************************************************/
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#define ADC_u32_TIME_OUT_MAX_VALUE			50000


/**********************************************************************/
/* Options For Voltage Refrance
 * 1- ADC_u8_VOLTAGE_REFRANCE_AREF
 * 2- ADC_u8_VOLTAGE_REFRANCE_AVCC
 * 3- ADC_u8_VOLTAGE_REFRANCE_2_56V
 * */
#define ADC_u8_VOLTAGE_REFRANCE		ADC_u8_VOLTAGE_REFRANCE_AVCC
/*****************************************************************/



/* Options For Conversion Mode
 * 1- ADC_u8_FREE_RUNNING_CONVERSION_MODE
 * 2- ADC_u8_SINGLE_CONVERSION_MODE
 * 3- ADC_u8_ANALOG_COMPARTOR_CONVERSION_MODE
 * 4- ADC_u8_EXTI0_CONVERSION_MODE
 * */
#define ADC_u8_CONVERSION_MODE		ADC_u8_SINGLE_CONVERSION_MODE
/**************************************************************************/



#endif
