//-----------------------------------------------
#ifndef  CAN_STM32F767_H
#define  CAN_STM32F767_H
//-----------------------------------------------
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_can.h"
#include "main.h"
//-----------------------------------------------
void Can1_intNfil(void);
void Can2_intNfil(void);
void Can3_intNfil(void);
void Send_Mess_CAN1(uint32_t GET_StdID, uint32_t GET_DLC, uint8_t* TxData1);
void Send_Mess_CAN2(uint32_t GET_StdID, uint32_t GET_DLC, uint8_t* TxData2);
void Send_Mess_CAN3(uint32_t GET_StdID, uint32_t GET_DLC, uint8_t* TxData3);
int Get_Mess_CAN1(uint32_t* GET_StdID, uint32_t* GET_DLC, uint8_t* RxData1);
int Get_Mess_CAN2(uint32_t* GET_StdID, uint32_t* GET_DLC, uint8_t* RxData2);
int Get_Mess_CAN3(uint32_t* GET_StdID, uint32_t* GET_DLC, uint8_t* RxData3);
void timeoutfunc(int time);
//-----------------------------------------------
#endif /* CAN_STM32F767_H */
