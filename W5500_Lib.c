#include "W5500_Lib.h"

/*Variables and structurs*/
enum Status
{
  Failed = 0,
  Success = 1
};
/*Functions*/

/*
 * This feature creates a delay.
 * This function takes milliseconds as input.
 */
void Delay_func(uint32_t delay)
{
	for(uint32_t i = 0; i < delay; i++);
}

/* *
 * This function use for select CS or SCS pin on W5500.
 * This use in "reg_wizchip_cs_cbfunc"
 */
void CS_Select(void)
{
	CS_Select_Function;
}

/* *
 * This function use for reset and unselect for CS/SCS pin on W5500.
 * This use in "reg_wizchip_cs_cbfunc"
 */
void CS_Unselect(void)
{
	CS_UnSelect_Function;
}

/* *
 * This function use for restart W5500.
 * In this function use pin RST on W5500.
 */
void RST_Func(void)
{
	RST_Reset_PIN;
	Delay_func(1);
	RST_Set_PIN;
	Delay_func(2000);
}

/* *
 * This function use for connect W5500 on SPI protocol for read buffer from W5500 to board.
 * This use in "SPI_ReadByte".
 */
void SPI_ReadBuffer(uint8_t* buff, uint16_t len)
{
	SPI_Receive;
}

/* *
 * This function use for connect W5500 on SPI protocol for write buffer from W5500 to board.
 * This use in "SPI_ReadByte".
 */
void SPI_WriteBuffer(uint8_t* buff, uint16_t len)
{
	SPI_Transmit;
}

/* *
 * This function use for connect W5500 on SPI protocol for transfer pockets from W5500 to board.
 * This use in "reg_wizchip_spi_cbfunc".
 */
uint8_t SPI_ReadByte(void)
{
	uint8_t byte;
    SPI_ReadBuffer(&byte, sizeof(byte));
    return byte;
}

/* *
 * This function use for connect W5500 on SPI protocol for transfer pockets from W5500 to board.
 * This use in "reg_wizchip_spi_cbfunc".
 */
void SPI_WriteByte(uint8_t byte)
{
	SPI_WriteBuffer(&byte, sizeof(byte));
}
/* *
 * This initialization function for UDP protocot.
 * The first input value is IP address board.
 * The second input value is MASK address board.
 */
void init_UDP(uint8_t ip_adr[4], uint8_t mask_adr[4])
{
	//This part function includes data transfer from board to W5500
    reg_wizchip_cs_cbfunc(CS_Select, CS_Unselect);
    reg_wizchip_spi_cbfunc(SPI_ReadByte, SPI_WriteByte);

    //Restart W5500
    RST_Func();

    // W5500 has 8 channel, 32k buffer, 2 means 2KBytes
    uint8_t buffer_size_8channel_tx_rx[16] = {2, 2, 2, 2, 2, 2, 2, 2,  // 8 channel tx
                                              2, 2, 2, 2, 2, 2, 2, 2}; // 8 channel rx

    //Initialization work with memory board.
    wizchip_init(buffer_size_8channel_tx_rx, buffer_size_8channel_tx_rx);

    //Initialization all address for conection and hard part
    wiz_NetInfo gSetNetInfo = {
        .mac = {0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef}, // MAC address
        .ip = {ip_adr[0], ip_adr[1], ip_adr[2], ip_adr[3]}, // IP address
        .sn = {mask_adr[0], mask_adr[1], mask_adr[2], mask_adr[3]}, // mask address
    };
    wiz_NetInfo gGetNetInfo;

    //This part includes initialization connect to system network
    ctlnetwork(CN_SET_NETINFO, (void*)&gSetNetInfo);
    Delay_func(10);
    ctlnetwork(CN_GET_NETINFO, (void*)&gGetNetInfo);
}

/* *
 * This send message function for UDP protocol.
 *  uint8_t sn - sockets number (0-7)
 *  uint8_t *buff - package to send (fe: uint8_t hello[] = "hello";)
 *  uint8_t ipAddr[4] - witch IP address send to (fe: uint8_t ip1[4] = {192, 168, 87, 55};)
 *  uint16_t port - witch PORT send to (fe: uint8_t mask[4] = {255, 255, 255, 0};)
 */
void send_message_udp(uint8_t sn, uint8_t *buff, uint8_t ipAddr[4], uint16_t port)
{
	   switch(getSn_SR(sn))									//Get socket status
	   {
		  case SOCK_UDP :									//Open UDP socket
				sendto(0,buff,sizeof(buff),ipAddr,port);
			 break;
		  case SOCK_CLOSED:									//Closed opened socket
			  	socket(sn, Sn_MR_UDP, port, 0x00);
			 break;
		  default :
			 break;
	   }
}

/* *
 * This receive message function for UDP protocol.
 *  uint8_t sn - sockets number (0-7)
 *  uint8_t *buf - package to receive
 *  uint16_t destport - on which port messege will receive
 *  uint8_t destip[4] - on wich IP messege will recive (fe: uint8_t destip[4] = {192, 168, 87, 36};)
 *  uint16_t myport - from witch port on board message will recive
 */
void resive_message(uint8_t sn, uint8_t* buf, uint16_t destport, uint8_t destip[4], uint16_t myport)
{
	   uint16_t size = sizeof(buf);

	   switch(getSn_SR(sn))										//Get socket status
	   	   {
	   		  case SOCK_UDP :									//Open UDP socket
	   			  	recvfrom(sn, buf, size, destip, &destport);
	   			 break;
	   		  case SOCK_CLOSED:									//Closed opened socket
	   			  	socket(sn, Sn_MR_UDP, myport, 0x00);
	   			 break;
	   		  default :
	   			 break;
	   	   }
}
