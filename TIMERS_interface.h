/*************************************************/
/**************  Name : Abdalrahman Magdy **********/
/**************  Date : 22/9/2020      *********/
/**************  SWC  : TIMERS         ********/
/**************  Version : 1.0         *******/
/********************************************/
#ifndef TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H

void TIMERS_voidTimer0Init(void);
u8 TIMERS_u8Timer0SetCallBack(void(*Copy_pf)(void));
u8 TIMERS_u8Timer0CTCSetCallBack(void(*Copy_pf)(void));
void TIMERS_voidTimer0SetCompareMatchValue(u8 Copy_u8OCR0Value);
void TIMERS_voidTimer1SetCompareMatchValueA(u16 Copy_u16OCR1A);
#endif
