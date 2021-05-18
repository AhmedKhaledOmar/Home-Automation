/* Login System !  */
/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define	 F_CPU 10000000UL
#include <util/delay.h>
/*MCAL*/

#include "DIO_interface.h"
#include "TIMERS_private.h"
/*HAL*/
#include "LCD_interface.h"
#include "ADC_interface.h"
#include "KPD_interface.h"
#include "Functions.h"
u8 Local_Au8PassArr[]={'1','2','3','4'};
u8 Local_Au8EnteredNums[4];
u8 Local_u8Flag= 1,i,Local_u8_GasFlag,Local_u8_FlameFlag;


void LightSensorCheck(void)
{
	u16 Local_u16DigitalValue, Local_u16AnalogValue;
	ADC_u8GetDigitalValue(ADC_u8_CHANNEL_1,&Local_u16DigitalValue);
		Local_u16AnalogValue = (u16) ((Local_u16DigitalValue * 5000UL) / 1024);
		if(Local_u16AnalogValue< 1000 )
		{
			DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN5, DIO_u8_HIGH);

		}
		else
		{
			DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN5, DIO_u8_LOW);

		}
}
void ShowTemp(void)
{
	u16 Local_u16DigitalValue,Local_u16AnalogValue,Local_u16TempValue;
	LCD_voidClearScreen();
	LCD_u8GoToXY(LCD_u8_LINE1, 0);
	LCD_voidSendString("TEMP:");
	ADC_u8GetDigitalValue(ADC_u8_CHANNEL_0, &Local_u16DigitalValue);
	Local_u16AnalogValue = (u16)((Local_u16DigitalValue * 5000UL) / 1024);
	Local_u16TempValue = Local_u16AnalogValue / 10;
	LCD_voidSendNum(Local_u16TempValue);
	_delay_ms(2000);
	DashBoard();
}
void DashBoard (void)
{
	u8 Local_PressFlag=0,Local_u8Key;
	LCD_voidClearScreen();
	Reset();
	LCD_u8GoToXY(LCD_u8_LINE1, 0);
	LCD_voidSendString("1.Show Temp");
	LCD_u8GoToXY(LCD_u8_LINE2, 0);
	LCD_voidSendString("2.Exit");
	while(Local_PressFlag==0)
	{
		 DIO_u8GetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,&Local_u8_GasFlag);
		DIO_u8GetPinValue(DIO_u8_PORTD,DIO_u8_PIN3,&Local_u8_FlameFlag);
		if(!Local_u8_FlameFlag)
		{
			LCD_voidClearScreen();
			LCD_voidSendString("Fire!!!!");
			Alert(1);
			OpenDoor();
			while(1);
		}
		if(!Local_u8_GasFlag)
		{
			LCD_voidClearScreen();
			LCD_voidSendString("Gas Leaking!!!!");
			Alert(1);
			OpenDoor();
			while(1);
		}
		LightSensorCheck();
		KPD_u8GetKeyState(&Local_u8Key);//Key Pressed Function
		if(Local_u8Key != KPD_u8_KEY_NOT_PRESSED)//If A Key Pressed
		{
			//LightSensorCheck();
			//LCD_voidClearScreen();
			switch(Local_u8Key)
			{
			case '1': ShowTemp();
				break;
			case '2':
				break;
			default :
			LCD_voidClearScreen();
			LCD_u8GoToXY(LCD_u8_LINE1, 0);
			LCD_voidSendString("Wrong Choice !");
			_delay_ms(1500);
			DashBoard();
			}
			Local_PressFlag =1;
		}
	}
}
void OpenDoor(void)
{
	TIMERS_u16_OCR1A_REG=2500;
}
void CloseDoor(void)
{
	TIMERS_u16_OCR1A_REG=1550;
}
void Alert(int check)
{
	if(check==1)
		 DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN6, DIO_u8_HIGH);
	else
		 DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN6, DIO_u8_LOW);
}
void GreenLed(int check)
{
	if(check==1)
		 DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN4, DIO_u8_HIGH);
	else
		 DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN4, DIO_u8_LOW);
}
void YellowLed(int check)
{
	if(check==1)
		 DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN5, DIO_u8_HIGH);
	else
		 DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN5, DIO_u8_LOW);
}

void AcssesAllowed(void)
{
	 LCD_voidClearScreen();
	 LCD_u8GoToXY(LCD_u8_LINE1, 0);
	 LCD_voidSendString("Access Allowed");
	 OpenDoor();
	 GreenLed(1);
	 _delay_ms(3000);
	 CloseDoor();
	 GreenLed(0);
	 _delay_ms(3000);
}
void AccessDenied(void)
{
	 LCD_voidClearScreen();
	 LCD_u8GoToXY(LCD_u8_LINE1, 0);
	 LCD_voidSendString("Access Denied");
	 Alert(1);
	 _delay_ms(4000);
	 Alert(0);

}
void NewTry(void)
{
	// Local_u8Flag = 1;
	 LCD_u8GoToXY(LCD_u8_LINE1, 0);
	 LCD_voidSendString("Enter Password:");
	 LCD_u8GoToXY(LCD_u8_LINE2, 0);
}
void WrongPass(void)
{
	 LCD_voidClearScreen();
	 LCD_u8GoToXY(LCD_u8_LINE1, 0);
	 LCD_voidSendString("Wrong Pass !");
	 YellowLed(1);
	 _delay_ms(1500);
	 LCD_voidClearScreen();
	 YellowLed(0);
	 LCD_u8GoToXY(LCD_u8_LINE1, 0);
	 LCD_voidSendString("Tries Left:");
}
void Reset(void)
{
	 YellowLed(0);
	 GreenLed(0);
	 Alert(0);
	 LCD_voidClearScreen();
}
void Login(void)
{
	u8 Local_u8Key;
	_delay_ms(2000);
	Reset();
	for(int j=2;j>=0;j--)//The Three Tries Four Loop
	{
		Local_u8Flag = 1;
		NewTry();

	 i=0;
	 while(i<4)//While Loop To Enter The 4 Number Password
	 {
		 DIO_u8GetPinValue(DIO_u8_PORTD,DIO_u8_PIN2,&Local_u8_GasFlag);
		DIO_u8GetPinValue(DIO_u8_PORTD,DIO_u8_PIN3,&Local_u8_FlameFlag);
		if(!Local_u8_FlameFlag)
		{
			LCD_voidClearScreen();
			LCD_voidSendString("Fire!!!!");
			Alert(1);
			OpenDoor();
			while(1);
		}
		if(!Local_u8_GasFlag)
		{
			LCD_voidClearScreen();
			LCD_voidSendString("Gas Leaking!!!!");
			Alert(1);
			OpenDoor();
			while(1);
		}
		 LightSensorCheck();
		 KPD_u8GetKeyState(&Local_u8Key);//Key Pressed Function
		 if(Local_u8Key != KPD_u8_KEY_NOT_PRESSED)//If A Key Pressed
		 {
			 LCD_voidSendChar('*');	// Write On The LCD *
			 Local_Au8EnteredNums[i] = Local_u8Key;// Store Every Char In Array To Compare It Later
			 i++;// The Counter Will Increase Only When He Press A Key.
		}
	 }
	 for(i=0;i<4;i++)// For Loop To Check Every Number In Password Array
	 {
		 if(Local_Au8PassArr[i] != Local_Au8EnteredNums[i])//If Any Number Wasn't Match the password
		 {
				 Local_u8Flag = 0;//Change The Flag
		 }
	 }
		 if(Local_u8Flag == 1) // If The Password Was Correct
		 {

			 AcssesAllowed();
			 DashBoard();
			 break;
		 }
		 else
		 {
			 WrongPass();
			 if(j==0)
			 {
				 LCD_voidSendChar('0');
			 }
			 LCD_voidSendNum(j);//To Display The Left Tries on the screen
			 _delay_ms(2000);
		 }
		 if(j==0)
		 {
			 AccessDenied();
		 }
	}
}

