//-----------------------------------------------
#ifndef  CAN_STM32F767_H
#define  CAN_STM32F767_H
//-----------------------------------------------
#include "main.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"
#include "stdio.h"
#include "string.h"
//-----------------------------------------------
void UDPinit(u32_t a, u32_t b, u32_t c, u32_t d, u16_t port);
void UDPsend(u32_t a, u32_t b, u32_t c, u32_t d, u16_t port, char *mess, char arr);
int UDPmessToMem(char *mass_cop, char *arr );
//-----------------------------------------------
#endif /* CAN_STM32F767_H */
