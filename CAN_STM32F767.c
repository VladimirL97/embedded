//----------------------------------------//
/******FAIL*S*FUNKTZIYAMI*DLYA*CANOV*******/
//----------------------------------------//
/******PODKLU4AEMYE*BIBLIOTEKI*************/
//----------------------------------------//
#include "CAN_STM32F767.h"
//----------------------------------------//
//----------------------------------------//
/******PEREMENNYE*&*STRUKTURY**************/
//----------------------------------------//
//-----EXTERN-STRUCT-FROM-MAIN------------//
//----------------------------------------//
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern CAN_HandleTypeDef hcan3;
//----------------------------------------//
/**********FUNKZII*************************/
//----------------------------------------//
/******FIRST*BLOK*INITIALIZATION***********/
/**********CAN*AND*FILTERS*****************/
//----------------------------------------//
//-----INIZIALIZAZIYA-&-FILTER-CAN-1------//
void Can1_intNfil(void)
{
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 13;

	if(HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_CAN_Start(&hcan1);
}
//-----INIZIALIZAZIYA-&-FILTER-CAN-2------//
void Can2_intNfil(void)
{
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = 15;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;

	if(HAL_CAN_ConfigFilter(&hcan2, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_CAN_Start(&hcan2);
}
//-----INIZIALIZAZIYA-&-FILTER-CAN-3------//
void Can3_intNfil(void)
{
	CAN_FilterTypeDef  sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;

	if(HAL_CAN_ConfigFilter(&hcan3, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_CAN_Start(&hcan3);
}
//----------------------------------------//
/******SECOND*BLOK*SEND*MESSEGE************/
//----------------------------------------//
//-----SEND-MESSAGE-CAN-1-----------------//

void Send_Mess_CAN1(uint32_t Send_StdID, uint32_t Send_DLC, uint8_t* TxData1)
{
	CAN_TxHeaderTypeDef TxHeader1;

	TxHeader1.StdId = Send_StdID;
	TxHeader1.DLC = Send_DLC;
	TxHeader1.IDE = CAN_ID_STD;
	TxHeader1.RTR = CAN_RTR_DATA;
	TxHeader1.TransmitGlobalTime = 0;

	uint32_t TxMailbox1 = 0;

	if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0)
	{
	//---function-for-add-arr-in----
	//-------send-messege-----------
		if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader1, TxData1, &TxMailbox1)!= HAL_OK)
		{
			Error_Handler ();
		}
	}
}
//-----SEND-MESSAGE-CAN-2-----------------//
void Send_Mess_CAN2(uint32_t Send_StdID, uint32_t Send_DLC, uint8_t* TxData2)
{
	CAN_TxHeaderTypeDef TxHeader2;

	TxHeader2.StdId = Send_StdID;
	TxHeader2.DLC = Send_DLC;
	TxHeader2.IDE = CAN_ID_STD;
	TxHeader2.RTR = CAN_RTR_DATA;
	TxHeader2.TransmitGlobalTime = 0;

	uint32_t TxMailbox2 = 0;

	if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
	{
		//---function-for-add-arr-in----
		//-------send-messege-----------
		if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader2, TxData2, &TxMailbox2)!= HAL_OK)
		{
			Error_Handler ();
		}
	}
}
//-----SEND-MESSAGE-CAN-3-----------------//
void Send_Mess_CAN3(uint32_t Send_StdID, uint32_t Send_DLC, uint8_t* TxData3)
{
	CAN_TxHeaderTypeDef TxHeader3;

	TxHeader3.StdId = Send_StdID;
	TxHeader3.DLC = Send_DLC;
	TxHeader3.IDE = CAN_ID_STD;
	TxHeader3.RTR = CAN_RTR_DATA;
	TxHeader3.TransmitGlobalTime = 0;

	uint32_t TxMailbox3 = 0;

	if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan3) > 0)
	{
		//---function-for-add-arr-in----
		//-------send-messege-----------
		if (HAL_CAN_AddTxMessage(&hcan3, &TxHeader3, TxData3, &TxMailbox3)!= HAL_OK)
		{
			Error_Handler ();
		}
	}
}
//----------------------------------------//
/******THIRD*BLOK*SEND*MESSEGE*************/
//----------------------------------------//
//-----GET-MESSAGE-CAN-1------------------//
int Get_Mess_CAN1(uint32_t* GET_StdID, uint32_t* GET_DLC, uint8_t* RxData1)
{
	CAN_RxHeaderTypeDef RxHeader1;

	//---function-for-add-arr-in----
	//-------get-messege-----------
	if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader1, RxData1) == HAL_OK)
	{
		*GET_StdID = RxHeader1.StdId;
		*GET_DLC = RxHeader1.DLC;

		//---function-for-add-0-when-DLC-<-0--
		//---MOST-IMPORTENT-FUNCTION----------
		if(RxHeader1.DLC < 8)
		{
			for(int i = RxHeader1.DLC; i < 8; i++ )
			{
				RxData1[i]=0;
			}
		}
		return 0;
	}
	else
	{
		return 1;
	}
}
//-----GET-MESSAGE-CAN-2------------------//
int Get_Mess_CAN2(uint32_t* GET_StdID, uint32_t* GET_DLC, uint8_t* RxData2)
{
	CAN_RxHeaderTypeDef RxHeader2;

	//---function-for-add-arr-in----
	//-------get-messege-----------
	if (HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxHeader2, RxData2) == HAL_OK)
	{
		*GET_StdID = RxHeader2.StdId;
		*GET_DLC = RxHeader2.DLC;

		//---function-for-add-0-when-DLC-<-0--
		//---MOST-IMPORTENT-FUNCTION----------
		if(RxHeader2.DLC < 8)
		{
			for(int i = RxHeader2.DLC; i < 8; i++ )
			{
				RxData2[i]=0;
			}
		}
		return 0;
	}
	else
	{
		return 1;
	}
}
//-----GET-MESSAGE-CAN-3------------------//
int Get_Mess_CAN3(uint32_t* GET_StdID, uint32_t* GET_DLC, uint8_t* RxData3)
{
	CAN_RxHeaderTypeDef RxHeader3;

	//---function-for-add-arr-in----
	//-------get-messege-----------
	if (HAL_CAN_GetRxMessage(&hcan3, CAN_RX_FIFO0, &RxHeader3, RxData3) == HAL_OK)
	{
		*GET_StdID = RxHeader3.StdId;
		*GET_DLC = RxHeader3.DLC;

		//---function-for-add-0-when-DLC-<-0--
		//---MOST-IMPORTENT-FUNCTION----------
		if(RxHeader3.DLC < 8)
		{
			for(int i = RxHeader3.DLC; i < 8; i++ )
			{
				RxData3[i]=0;
			}
		}
		return 0;
	}
	else
	{
		return 1;
	}
}
