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

int net_handle(struct sk_buff *skbh)
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

	udp_skb_reserve(skbh);
	(*skbh->data) = 'l';
	udp_send(skbh, 3232236098, UDP, 3538);	//192.168.2.66:3538 
	
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

	rRTCCON = 0x01;					// No reset, Merge BCD counters, 1/32768, RTC Control enable
	g_nYear =rBCDYEAR;
	g_nMonth   = rBCDMON;
	g_nWeekday = rBCDDAY;
	g_nDate    = rBCDDATE;
	g_nHour    = rBCDHOUR;
	g_nMin     = rBCDMIN;
	g_nSec     = rBCDSEC;
  uart_printf(" %02x:%02x:%02x  %10s,  %02x/%02x/%04x\r\n",g_nHour,g_nMin,g_nSec,day[g_nWeekday],g_nMonth,g_nDate,g_nYear);
	rRTCCON = 0x0;					// No reset, Merge BCD counters, 1/32768, RTC Control disable(for power consumption)
	 
	net_handle(skb);
	time_skb_reserve(skb);
	time_send(skb, g_nYear,g_nMonth,g_nDate,g_nWeekday,g_nHour,g_nMin,g_nSec);	//192.168.2.66:3538
	
	return 0;
}



