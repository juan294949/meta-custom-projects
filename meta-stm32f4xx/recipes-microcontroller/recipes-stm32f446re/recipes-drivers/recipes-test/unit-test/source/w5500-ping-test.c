#include "stm32f446xx.h"

/*
*	@TODO: investigate what does ping do.
*
*		About ping command:
*
*   - When you ping a device, your computer expects to receive an: ICMP Echo Reply
*     in response to the ICMP Echo Request it sent. If, it gets that reply back → the device is considered reachable.
* 
*   -	Ping is not networking. Ping is a diagnostic.
*/


/* TCP server ECHO test. 
*		-TCP Echo Server (the “Hello World” of networking)
*	
*	What it does:
*
*	A PC connects to your device
*
*	Sends bytes
*
*	Your device sends the same bytes back
*/
int w5500_TCP_test(uint8_t DstIp)
{
	
	while(!listen());

	return 0;
}
