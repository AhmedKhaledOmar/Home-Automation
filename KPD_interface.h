/*******************************************************************************/
/**********************    Name	: Abdalrahman Magdy ****************************/
/**********************    Date	: 07/09/2020         ****************************/
/**********************    SWC	: KPD      			****************************/
/********************    Version: 1.0   			****************************/
/*******************************************************************************/
#ifndef KPD_INTERFACE_H
#define KPD_INTERFACE_H

#define KPD_u8_KEY_NOT_PRESSED  0xFF

u8 KPD_u8GetKeyState(u8 *Copy_pu8ReturnedKey);

#endif