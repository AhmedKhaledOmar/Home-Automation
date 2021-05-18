/*******************************************************************************/
/**********************    Name	: Abdalrahman Magdy ****************************/
/**********************    Date	: 01/09/2020         ****************************/
/**********************    SWC	: LCD      			****************************/
/********************    Version: 1.0   			****************************/
/*******************************************************************************/
/*LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 10000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_interface.h"

/*HAL*/
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

void LCD_voidInit(void)
{
	_delay_ms(35);
	/* Function Set CMND */
	LCD_voidSendCmnd(0b00111000);
	/* Display ON\OFF */
	_delay_us(40);
	LCD_voidSendCmnd(0b00001100);
	/* Display Clear */
	_delay_us(40);
	LCD_voidSendCmnd(0x01);
	/* Entry Mode Set */
	_delay_us(2);
	LCD_voidSendCmnd(0b00000110);
}

void LCD_voidSendCmnd(u8 Copy_u8Cmnd)
{
	/* Step 1 RS=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_RS_PIN ,DIO_u8_LOW);
	/* RW = 0*/
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_RW_PIN ,DIO_u8_LOW);
	/*  Write Command */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT ,Copy_u8Cmnd);
	/* E = 1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_E_PIN ,DIO_u8_HIGH);
	_delay_ms(1);
	/* E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_E_PIN ,DIO_u8_LOW);
}
void LCD_voidSendChar(u8 Copy_u8Char)
{
		/* Step 1 RS=0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_RS_PIN ,DIO_u8_HIGH);
	/* RW = 0*/
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_RW_PIN ,DIO_u8_LOW);
	/*  Write Command */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT ,Copy_u8Char);
	/* E = 1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_E_PIN ,DIO_u8_HIGH);
	_delay_ms(1);
	/* E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT ,LCD_u8_E_PIN ,DIO_u8_LOW);
}
void LCD_voidSendString(u8 *Copy_pu8String)
{
	while(*Copy_pu8String!='\0')
	{
		LCD_voidSendChar(*Copy_pu8String);
		Copy_pu8String++;
	}
}
void LCD_voidSendNum(u32 Copy_u32Num)
{
	u32 Local_u32Reainder=0 , Local_u32Reversee=0;
	while(Copy_u32Num>0)
    {
		Local_u32Reainder = Copy_u32Num % 10;
		Local_u32Reversee = Local_u32Reversee*10 + Local_u32Reainder;
	    Copy_u32Num = Copy_u32Num / 10;
    }
	while(Local_u32Reversee !=0)
	{
		LCD_voidSendChar((Local_u32Reversee % 10) + 48);
		Local_u32Reversee =Local_u32Reversee /10;
	}
}
u8 LCD_u8GoToXY(u8 Copy_u8LineNum ,u8 Copy_u8Location)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8Location<=39)
	{
		switch (Copy_u8LineNum)
		{
		case LCD_u8_LINE1:LCD_voidSendCmnd(0x80 + Copy_u8Location);break;
		case LCD_u8_LINE2:LCD_voidSendCmnd(0xc0 + Copy_u8Location);break;
		default:Local_u8ErrorState = STD_TYPES_NOK;
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
u8 LCD_u8WriteSpecialChar(u8 Copy_u8CharNum ,u8 *Copy_pu8ArrOfChar ,u8 Copy_u8LineNum ,u8 Copy_u8Location)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_u8Location<=39 && ((Copy_u8LineNum == LCD_u8_LINE1) || (Copy_u8LineNum ==LCD_u8_LINE2) ))
	{
		switch(Copy_u8CharNum)
		{
		case LCD_u8_1_PLACE: LCD_voidSendCmnd(0b01000000);break;
		case LCD_u8_2_PLACE: LCD_voidSendCmnd(0b01001000);break;
		case LCD_u8_3_PLACE: LCD_voidSendCmnd(0b01010000);break;
		case LCD_u8_4_PLACE: LCD_voidSendCmnd(0b01011000);break;
		case LCD_u8_5_PLACE: LCD_voidSendCmnd(0b01100000);break;
		case LCD_u8_6_PLACE: LCD_voidSendCmnd(0b01101000);break;
		case LCD_u8_7_PLACE: LCD_voidSendCmnd(0b01110000);break;
		case LCD_u8_8_PLACE: LCD_voidSendCmnd(0b01111000);break;
		default: Local_u8ErrorState = STD_TYPES_NOK;
		}
		if(Local_u8ErrorState == STD_TYPES_OK)
		{
			for(u8 i=0;i<8;i++)
			{
				LCD_voidSendChar(Copy_pu8ArrOfChar[i]);
			}
			LCD_u8GoToXY(Copy_u8LineNum ,Copy_u8Location);
			LCD_voidSendChar(Copy_u8CharNum);
			//LCD_u8GoToXY(LCD_u8_LINE1 ,0);
		}
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}

	return Local_u8ErrorState;
}
void LCD_voidClearScreen(void)
{
	LCD_voidSendCmnd(0x01);
	_delay_ms(2);
}

