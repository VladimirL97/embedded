//----------------------------------------//
/******FAIL*S*FUNKTZIYAMI*DLYA*UDP*********/
//----------------------------------------//
/******PODKLU4AEMYE*BIBLIOTEKI*************/
//----------------------------------------//
#include "UDP_STM32F767.h"
#include "QueueMCU.h"
//----------------------------------------//

//----------------------------------------//
/******PEREMENNYE*&*STRUKTURY**************/
//----------------------------------------//
struct udp_pcb *upcb;
//----------------------------------------//
struct glob_var{
	uint8_t glob_mess[128];
	u16_t strlen;
};

void UDPrecv(void *arg, struct udp_pcb *pcb, struct pbuf *pb, const ip_addr_t *srcAddr, uint16_t port);

QueueMCU_t QueueUDP;
//----------------------------------------//
/**********FUNKZII*************************/
//----------------------------------------//
/******FIRST*BLOK*INITIALIZATION***********/
//----------------------------------------//
void UDPinit(u32_t a, u32_t b, u32_t c, u32_t d, u16_t port)
{
	upcb = udp_new();
	ip_addr_t myIPADDR;
	IP_ADDR4(&myIPADDR, a, b, c, d);
	udp_bind(upcb, &myIPADDR, port);
	udp_recv(upcb, UDPrecv, NULL);
	vl_CreateQueue(&QueueUDP, sizeof(struct glob_var), 5);
}
//----------------------------------------//
/******SECOND*BLOK*SEND*MESS***************/
//----------------------------------------//
void UDPsend(u32_t a, u32_t b, u32_t c, u32_t d, u16_t port, char *mess, char arr)
{
	struct pbuf *p;
	p = pbuf_alloc(PBUF_TRANSPORT, arr, PBUF_POOL);
	ip_addr_t pcIPADDR;
	IP_ADDR4(&pcIPADDR, a, b, c, d);

	if (p != NULL)
	{
		pbuf_take(p, (void *) mess, arr);
		udp_sendto(upcb, p, &pcIPADDR ,port);
		pbuf_free(p);
	}
}
//----------------------------------------//
/******FIRST*BLOK*GET*MESS*****************/
//----------------------------------------//
void UDPrecv(void *arg, struct udp_pcb *pcb, struct pbuf *pb, const ip_addr_t *srcAddr, uint16_t port)
{
	struct glob_var str;
	str.strlen = pb->len;
	memcpy(str.glob_mess,pb->payload ,pb->len);
	if(vl_QueueSize(&QueueUDP) > 4)
	{
		vl_GetFront(&QueueUDP);
		vl_SetBack(&QueueUDP, &str);
	}
	else
	{
		vl_SetBack(&QueueUDP, &str);
	}
	pbuf_free(pb);
}
//----------------------------------------//
/******FIFTH*BLOK*GET*MESS*****************/
//----------------------------------------//
int UDPmessToMem(char *mass_cop, char *arr )
{
	if(vl_QueueSize(&QueueUDP) > 0)
	{
		struct glob_var* str = (struct glob_var*)vl_GetFront(&QueueUDP);
		memcpy(mass_cop, str->glob_mess, str->strlen);
		*arr = str->strlen;
		return 0;
	}
	else
	{
		return 1;
	}
}
