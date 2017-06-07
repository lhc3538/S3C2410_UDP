#include "changeformat.h"
#include "skbuff.h"
#include "eth.h"
#include "arp.h"
#include "ip.h"
#include "udp.h"
#include "time.h"
#include "utils.h"
#include "2410lib.h"

INT32T g_nYear,g_nMonth,g_nDate,g_nWeekday,g_nHour,g_nMin,g_nSec;
INT8T *day[8] = {" ","SUN","MON","TUE","WED","THR","FRI","SAT"};

char TftpLoadEnd;
char TftpPutBegin;
char TftpPutMark;

int net_handle(void)
{
	struct sk_buff *skb;
	struct ethhdr *eth_hdr;												
	skb = alloc_skb(ETH_FRAME_LEN);

	if (eth_rcv(skb) != -1) 
	{

		eth_hdr = (struct ethhdr *)(skb->data);					
		skb_pull(skb, ETH_HLEN);
		if (ntohs(eth_hdr->h_proto) == ETH_P_ARP)
		{
			arp_rcv_packet(skb);

		}

		else if(ntohs(eth_hdr->h_proto) == ETH_P_IP)						
		{

		 	ip_rcv_packet(skb);

		}
	 	
	}

	free_skb(skb);

	return 0;
}



#define	LOCAL_IP_ADDR	((192UL<<24)|(168<<16)|(2<<8)|111)

extern unsigned long download_len;
extern unsigned long download_addr;

unsigned char data[4] = {0};

int NetLoadFile(UINT32T addr, UINT32T give_ip, UINT32T a3, UINT32T a4)
{
	struct sk_buff *skb = alloc_skb(ETH_FRAME_LEN);
	unsigned char eth_addr[ETH_ALEN];	
	unsigned char *s;
	int i;
	unsigned char *p;
	give_ip = LOCAL_IP_ADDR;
	s = (unsigned char *)&give_ip;
	
	uart_printf("Mini TFTP Server 1.0 (IP : %d.%d.%d.%d PORT: %d)\n", s[3], s[2], s[1], s[0], TFTP);		
	uart_printf("Type tftp -i %d.%d.%d.%d put filename at the host PC\n", s[3], s[2], s[1], s[0]);

	eth_init();		
	eth_get_addr(eth_addr);		
	ip_init(give_ip);
	udp_init();
		
	
	arp_add_entry(eth_addr, give_ip);	
	
	

		net_handle();
		//change data p
		udp_skb_reserve(skb);
		(*skb->data) = 'l';
		
		uart_printf("udp send pad: %s\n",skb->pad);
		uart_printf("udp send buf: %s\n",skb->buf);
		uart_printf("udp send truesize: %d\n",skb->truesize);
		uart_printf("udp send data: %s\n",skb->data);
		uart_printf("udp send len: %d\n\n",skb->len);
		udp_send(skb, 3232236098, UDP, 3538);	//192.168.2.66:3538
		
           
	uart_printf("\n Display current Date and time: \n");

	rRTCCON = 0x01;					// No reset, Merge BCD counters, 1/32768, RTC Control enable
	uart_printf(" Press any key to exit.\n");

            g_nYear =rBCDYEAR;

            g_nMonth   = rBCDMON;
            g_nWeekday = rBCDDAY;
            g_nDate    = rBCDDATE;
            g_nHour    = rBCDHOUR;
            g_nMin     = rBCDMIN;
            g_nSec     = rBCDSEC;
       
        uart_printf(" %02x:%02x:%02x  %10s,  %02x/%02x/%04x\r",g_nHour,g_nMin,g_nSec,day[g_nWeekday],g_nMonth,g_nDate,g_nYear);

	rRTCCON = 0x0;					// No reset, Merge BCD counters, 1/32768, RTC Control disable(for power consumption)
    
    uart_printf("\n\n Exit display.\n");
	 
		net_handle();
		time_skb_reserve(skb);
		time_send(skb, g_nYear,g_nMonth,g_nDate,g_nWeekday,g_nHour,g_nMin,g_nSec);	//192.168.2.66:3538
	
/*	TftpLoadEnd  = 0;
	TftpPutMark  = 0;
	TftpPutBegin = 0;
	
	download_addr = 0x30008000;
	download_len = 0;
	
	while (!TftpLoadEnd) {		
		net_handle();
		if(TftpPutBegin) {
			uart_printf("Starting the TFTP download...\n");
			TftpPutBegin = 0;
		}
		if(TftpPutMark) {
			uart_sendbyte('.');
			TftpPutMark = 0;
		}
	}

	if(TftpLoadEnd) {
		uart_printf("\ndownload 0x%x bytes to 0x%08x\n\n", download_len, download_addr);
	p=(char *)download_addr;
	for(i=0;i<download_len;i++)
		uart_printf("%c",p[i]);
    uart_printf("\nPress any key to continue...\n");
    while(!uart_getkey());
	return download_len;
	}*/

	return 0;
}



