/*************************************************/
/**************  Name : Abdalrahman Magdy **********/
/**************  Date : 17/9/2020      *********/
/**************  SWC  : ADC            ********/
/**************  Version : 1.0         *******/
/********************************************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_u8_CHANNEL_0               0
#define ADC_u8_CHANNEL_1               1
#define ADC_u8_CHANNEL_2               2
#define ADC_u8_CHANNEL_3               3
#define ADC_u8_CHANNEL_4               4
#define ADC_u8_CHANNEL_5               5
#define ADC_u8_CHANNEL_6               6
#define ADC_u8_CHANNEL_7               7
#define ADC_u8_CHANNEL_8               8
#define ADC_u8_CHANNEL_9               9
#define ADC_u8_CHANNEL_10              10
#define ADC_u8_CHANNEL_11              11
#define ADC_u8_CHANNEL_12              12
#define ADC_u8_CHANNEL_13              13
#define ADC_u8_CHANNEL_14              14
#define ADC_u8_CHANNEL_15              15
#define ADC_u8_CHANNEL_16              16
#define ADC_u8_CHANNEL_17              17
#define ADC_u8_CHANNEL_18              18
#define ADC_u8_CHANNEL_19              19
#define ADC_u8_CHANNEL_20              20
#define ADC_u8_CHANNEL_21              21
#define ADC_u8_CHANNEL_22              22
#define ADC_u8_CHANNEL_23              23
#define ADC_u8_CHANNEL_24              24
#define ADC_u8_CHANNEL_25              25
#define ADC_u8_CHANNEL_26              26
#define ADC_u8_CHANNEL_27              27
#define ADC_u8_CHANNEL_28              28
#define ADC_u8_CHANNEL_29              29
#define ADC_u8_CHANNEL_30              30
#define ADC_u8_CHANNEL_31              31


/*  */
#define	ADC_u8_VOLTAGE_REFRANCE_AREF	0
#define	ADC_u8_VOLTAGE_REFRANCE_AVCC	1
#define	ADC_u8_VOLTAGE_REFRANCE_2_56V	2

#define ADC_u8_FREE_RUNNING_CONVERSION_MODE		0
#define ADC_u8_SINGLE_CONVERSION_MODE			1
#define ADC_u8_ANALOG_COMPARTOR_CONVERSION_MODE	2
#define ADC_u8_EXTI0_CONVERSION_MODE			3

void ADC_voidInit(void);
u8	ADC_u8VoltageRefrance(u8 Copy_VoltageRefrance);
u8	ADC_u8ConversionMode(u8 Copy_u8ConversionMode);



u8	ADC_u8GetDigitalValueSynchNonBlocking(u8 Copy_u8ChannelNp ,u16 *Copy_pu16DigitalValue);
u8  ADC_u8GetDigitalValue(u8 Copy_u8ChannelNb, u16 *Copy_pu16DigitalValue);
u8  ADC_u8GetDigitalValueAsynch(u8 Copy_u8ChannelNb, void(*Copy_pfNotification)(u16));
u8  ADC_u8GetADCRegValue(u16 *Copy_pu16ADCValue);
#endif
