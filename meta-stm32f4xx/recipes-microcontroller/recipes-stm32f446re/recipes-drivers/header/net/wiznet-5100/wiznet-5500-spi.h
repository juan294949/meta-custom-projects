#ifndef WIZNET_5500_SPI_H
    #define WIZNET_5500_SPI_H
#include "stm32f446xx.h"
#include "socket.h"

/* ABOUT PORTS: A port number identifies a specific application or service on a device. 
*  			IP: PORT
*	192.168.1.50:80   → Apartment 80 (web server)
*	192.168.1.50:22   → Apartment 22 (SSH)
*	192.168.1.50:1883 → Apartment 1883 (MQTT)
*
*/

/* The Most important 5 functions to handle TCP/UDP */
/**
* w5500_set_ip()  - Sets the source IP for the wiznet w5500 chip.
* @ip:             	Buffer that contains the 4 IP digits.
* 									For example: uint8_t MyIpBuffer[4] = {192,168,3,100};
* Return:	void
*/
void w5500_set_ip(uint8_t	*SrcIp,uint8_t	*DstIp);

/**
* w5500_set_mac()  -
*
* Return:	void
*/
void w5500_set_mac(uint8_t	*SrcMac,uint8_t	*DstMac);

/**
* w5500_set_gateway()  - Set the source gateway  for the wiznet w5500 chip.
* @ip:             	Buffer that contains the 4 IP digits.
* 									For example: uint8_t MyIpBuffer[4] = {0};
* Return:	void
*/
void w5500_set_gateway(uint8_t	*Gw);

/**
* w5500_set_subnet()  - Get the source IP for the wiznet w5500 chip.
* @ip:             			Buffer that contains the 4 IP digits.
* 											For example: uint8_t MyIpBuffer[4] = {0};
* Return:	void
*/
void w5500_set_subnet(uint8_t	*Subnet);

/**
* w5500_get_ip()  - Get the source IP for the wiznet w5500 chip.
* @ip:             	Buffer that contains the 4 IP digits.
* 									For example: uint8_t MyIpBuffer[4] = {0};
* Return:	void
*/
void w5500_get_ip(uint8_t *StoreSrcIp,uint8_t *StoreDstIp);

/**
* w5500_get_id()  - Get ID from the wiznet w5500 chip.
* @ip:             	Buffer that contains the 4 IP digits.
* 
* Return:	returns the ID version of the device.
*
*	Note: You should be getting 0x04 which is the ID from the register VERSIONR
*/
uint8_t w5500_get_id(void);

/**
* W5500_Init()  - Initializes the w5500 device before beign able to be used.
* 
* Return:	TODO:
*
* Note: Initialization goes as following:
*		1).TODO:	
*/
int w5500_Init(void);

void w5500_reset(void);

/**
* W5500_bind()  - Initializes the w5500 device before beign able to be used.
* 
*	@address: Points to a sockaddr structure containing the address to be bound to the socket. 
*						The length, and format of the address depend on the address family of the socket.
*
* Return:	TODO:
*
*/
int w5500_bind(const struct sockaddr *address,socklen_t address_len);

/**
* w5500_connect()  - 
* 
* Return:	void.
*
* Note:	
*/
int w5500_connect(void);

/*
* w5500_listen()  -
* 
* Return:	void.
*
* Note:	
*/
int w5500_listen(void);

#endif
