
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal.h"
#include "utility.h"
#include "w5500.h"
#include "wizchip_conf.h"
#include "dns.h"
//#include "wizchip_port.h"

// Definitions & Macros
#define W5500_SPI_TIMEOUT (100u)
#define DNS_SOCKET	  6  // 2nd last socket

//Global variables section.
uint8_t DNS_buffer[512];
wiz_NetInfo netInfo = {
    .mac = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},
    .ip = {192, 168, 3, 99},
    .sn = {255, 255, 255, 0},
    .gw = {192, 168, 1, 1},
    .dns = {8, 8, 8, 8},
#if USE_DHCP
	.dhcp = NETINFO_DHCP
#else
    .dhcp = NETINFO_STATIC
#endif
};

// Global extern Objects Defined in another file.
extern SPI_HandleTypeDef SpiCOnfig;

// Functions defined in another file @wizchip_conf.c
extern void wizchip_spi_writebyte(uint8_t wb);
extern uint8_t wizchip_spi_readbyte(void);
extern void wizchip_cs_deselect(void);
extern void wizchip_cs_select(void);

void w5500_set_ip(uint8_t* ip)
{
	uint8_t* pIP = ip;
	uint32_t srcIP_start = 0x0F;

	if(pIP) //true If there is an address and not a Null pointer.
	{
		for(unsigned short i = 0; i < 4;i++)
		{
			WIZCHIP_WRITE(((srcIP_start + i) << 8) ,*pIP);
			pIP++;
		}
	}
}

void w5500_get_ip(uint8_t *StoreIP)
{
	uint8_t* pIP = StoreIP;
	uint32_t srcIP_start = 0x0F;

	if(pIP) // If there is an address and not a Null pointer.
	{
		for(unsigned short i = 0; i < 4;i++)
		{
			*pIP = WIZCHIP_READ(((srcIP_start + i) << 8));
			pIP++;
		}
	}
}

void w5500_set_mac(uint8_t* Mac)
{
	// Source Hardware Address Register) [R/W] [0x0009 – 0x000E] [0x00]
	uint8_t* pMac = Mac;
	uint32_t Mac_start = 0x09;

	if(pMac) // If there is an address and not a Null pointer.
	{
		for(unsigned short i = 0; i < 4;i++)
		{
			WIZCHIP_WRITE(((Mac_start + i) << 8) ,*pMac);
			pMac++;
		}
	}
}

void w5500_set_gateway(uint8_t* Gateway)
{
	// (Gateway IP Address Register) [R/W] [0x0001 – 0x0004] [0x00]
	uint8_t* pGateway = Gateway;
	uint32_t Gateway_start = 0x01;

	if(pGateway) // If there is an address and not a Null pointer.
	{
		for(unsigned short i = 0; i < 4;i++)
		{
			WIZCHIP_WRITE(((Gateway_start + i) << 8) ,*pGateway);
			pGateway++;
		}
	}
}

void w5500_set_dns(uint8_t* Dns)
{
	uint8_t* pDns = Dns;

	if(pDns) // If there is an address and not a Null pointer.
	{
		for(unsigned short i = 0; i < 4;i++)
		{
			netInfo.dns[i] = *pDns; // Not in any register.
			pDns++;
		}
	}
}


void w5500_set_netmask(uint8_t* Netmask)
{
	// (Gateway IP Address Register) [R/W] [0x0001 – 0x0004] [0x00]
	uint8_t* pNetmask = Netmask;
	uint32_t Netmask_start = 0x01;

	if(pGateway) // If there is an address and not a Null pointer.
	{
		for(unsigned short i = 0; i < 4;i++)
		{
			WIZCHIP_WRITE(((Gateway_start + i) << 8) ,*pGateway);
			pGateway++;
		}
	}
}

uint8_t w5500_get_id(void)
{
	uint32_t AddrID = 0x39;
  return WIZCHIP_READ(AddrID << 8);
}

void w5500_reset(void)
{
  GPIOB->BSRR = (1U << (6 + 16)); // set it low to reset the chip.
	HAL_Delay(50);
  GPIOB->BSRR = (1U << 6); // set it high to reset the chip.
	HAL_Delay(200);
}

int w5500_Init(void)
{
    uint8_t memsize[2][8] = {{2,2,2,2,2,2,2,2},{2,2,2,2,2,2,2,2}};

    /***** Reset Sequence  *****/
   	w5500_reset();
    /***** Register callbacks  *****/
    reg_wizchip_cs_cbfunc(wizchip_cs_select, wizchip_cs_deselect);
    reg_wizchip_spi_cbfunc(wizchip_spi_readbyte,wizchip_spi_writebyte);

    /***** Initialize the chip  *****/
    if (ctlwizchip(CW_INIT_WIZCHIP, (void*)memsize) == -1){
    	print("Error while initializing WIZCHIP\r\n");
    	return -1;
    }
    print("WIZCHIP Initialized\r\n");

    /***** check communication by reading Version  *****/
    uint8_t ver = getVERSIONR();
    if (ver != 0x04){
    	print("Error Communicating with W5500\t Version: 0x%02X\r\n", ver);
    	return -2;
    }
    print("Checking Link Status..\r\n");

 	/*****  CHeck Link Status  *****/
    uint8_t link = PHY_LINK_OFF;
    uint8_t retries = 10;
    while ((link != PHY_LINK_ON) && (retries > 0)){
      ctlwizchip(CW_GET_PHYLINK, &link);
      if (link == PHY_LINK_ON) print("Link: UP\r\n");
      else print("Link: DOWN Retrying : %d\r\n", 10-retries);
      retries--;
      HAL_Delay(500);
    }
    if (link != PHY_LINK_ON){
    	print ("Link is Down,please reconnect and retry\nExiting Setup..\r\n");
    	return 3;
    }

    /***** Use DHCP or Static IP  *****/
#if USE_DHCP
    print ("Using DHCP.. Please Wait..\r\n");
    setSHAR(netInfo.mac);
    DHCP_init(DHCP_SOCKET, DHCP_buffer);

    reg_dhcp_cbfunc(Callback_IPAssigned, Callback_IPAssigned, Callback_IPConflict);

    retries = 20;
    while((!ip_assigned) && (retries > 0)) {
        DHCP_run();
        HAL_Delay(500);
        retries--;
    }
    if(!ip_assigned) {
    	// DHCP Failed, switch to static IP
    	print ("DHCP Failed, switching to static IP\r\n");
    	ctlnetwork(CN_SET_NETINFO, (void*)&netInfo);
    }
    else {
    	// if IP is allocated, read it
        getIPfromDHCP(netInfo.ip);
        getGWfromDHCP(netInfo.gw);
        getSNfromDHCP(netInfo.sn);
        getDNSfromDHCP(netInfo.dns);

        // Now apply them to the chip
        ctlnetwork(CN_SET_NETINFO, (void*)&netInfo);
        print("DHCP IP assigned successfully\r\n");
    }

#else
    // use static IP (Not DHCP)
    print("Using Static IP..\r\n");
    ctlnetwork(CN_SET_NETINFO, (void*)&netInfo);
#endif

  /***** Configure DNS  *****/
  HAL_Delay(500);
  print("Configuring DNS..\r\n");
  DNS_init(DNS_SOCKET, DNS_buffer);
  /***** Print assigned IP on the console  *****/
  wiz_NetInfo tmpInfo;
  ctlnetwork(CN_GET_NETINFO, &tmpInfo);
  return 0;
}

void w5500_show_info(wiz_NetInfo* tmpInfo)
{
	w5500_get_ip(&(tmpInfo->ip));
	print("inet: %d.%d.%d.%d ", tmpInfo->ip[0], tmpInfo->ip[0], tmpInfo->ip[0], tmpInfo->ip[0]);
	w5500_get_sn(&(tmpInfo->sn));
  print("netmask: %d.%d.%d.%d\r\n", tmpInfo->sn[0], tmpInfo->sn[1], tmpInfo->sn[2], tmpInfo->sn[3]);
	w5500_get_gw(&(tmpInfo->gw));
	print("ether: %x.%x.%x.%x\r\n", tmpInfo->mac[0], tmpInfo->mac[1], tmpInfo->mac[2], tmpInfo->mac[3], tmpInfo->mac[4], tmpInfo->mac[5]);
	w5500_get_gw(&(tmpInfo->gw));
  print("gateway: %d.%d.%d.%d\r\n", tmpInfo->gw[0], tmpInfo->gw[1], tmpInfo->gw[2], tmpInfo->gw[3]);
	w5500_get_dns(&(tmpInfo->dns));
  print("domain name system: %d.%d.%d.%d\r\n", tmpInfo->dns[0], tmpInfo->dns[1], tmpInfo->dns[2], tmpInfo->dns[3]);
}

// socket()
// bind()
// listen()
// accept()
// send()
// recv()

/* Used inside wiznet_conf.c */
void spi_tx_byte(uint8_t byte)
{
	HAL_SPI_Transmit(&SpiCOnfig,&byte,1,W5500_SPI_TIMEOUT);
}

uint8_t spi_rx_byte(void)
{
	uint8_t DataRcv = 0;
	HAL_SPI_Receive(&SpiCOnfig,&DataRcv,1,W5500_SPI_TIMEOUT);
	return DataRcv;
}
