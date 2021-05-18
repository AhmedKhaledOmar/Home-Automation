/* Login System !  */
/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define	 F_CPU 8000000UL
#include <util/delay.h>
/*MCAL*/
#include "DIO_interface.h"
/*HAL*/
#include "TIMERS_private.h"
#include "LCD_interface.h"
#include "GI_interface.h"
#include "TIMERS_interface.h"
#include "KPD_interface.h"
#include "ADC_interface.h"
#include "Functions.h"

//static u16 App_voidU16DigitalValue;
int main(void)
{
	//u16 Local_u16DigitalValue, Local_u16AnalogValue;
	u8 Local_u8Key;
	DIO_voidInit();
	GI_voidEnable();
	TIMERS_voidTimer0Init();
	ADC_voidInit();
	LCD_voidInit();
	LCD_voidClearScreen();


	while(1)
	{
		Login();
		LCD_voidClearScreen();
		Reset();
		LCD_u8GoToXY(LCD_u8_LINE1, 0);
		LCD_voidSendString("Good Bye !");


	}
	 return 0;
}

