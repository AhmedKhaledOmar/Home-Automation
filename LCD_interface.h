/*******************************************************************************/
/**********************    Name	: Abdalrahman Magdy ****************************/
/**********************    Date	: 01/09/2020         ****************************/
/**********************    SWC	: LCD      			****************************/
/********************    Version: 1.0   			****************************/
/*******************************************************************************/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

/* Macros To Choose Which line to write on the lcd  */
#define LCD_u8_LINE1	1
#define LCD_u8_LINE2	2

/* Macros To Choose The Place To Store The Special Chars on the CGROM */
#define LCD_u8_1_PLACE		0
#define LCD_u8_2_PLACE		1
#define LCD_u8_3_PLACE		2
#define LCD_u8_4_PLACE		3
#define LCD_u8_5_PLACE		4
#define LCD_u8_6_PLACE		5
#define LCD_u8_7_PLACE		6
#define LCD_u8_8_PLACE		7

void LCD_voidInit(void);

void LCD_voidSendCmnd(u8 Copy_u8Cmnd);

void LCD_voidSendChar(u8 Copy_u8Char);

void LCD_voidSendString(u8 *Copy_pu8String);

void LCD_voidSendNum(u32 Copy_u32Num);

u8 LCD_u8GoToXY(u8 Copy_u8LineNum ,u8 Copy_u8Location);

void LCD_voidClearScreen(void);

u8 LCD_u8WriteSpecialChar(u8 Copy_u8CharNum ,u8 *Copy_pu8ArrOfChar ,u8 Copy_u8LineNum ,u8 Copy_u8Location);
#endif
