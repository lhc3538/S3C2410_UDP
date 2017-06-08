#include "skbuff.h"
#include "eth.h"
#include "ip.h"
#include "udp.h"
#include "time.h"
#include "tftp.h"
#include "utils.h"


int time_init(void)
{
	return 0;
}

int time_send(struct sk_buff *skb, int g_nYear,int g_nMonth,
	int g_nDate,int g_nWeekday,int g_nHour,int g_nMin,int g_nSec)
{
	struct timehdr *time_hdr;

	time_hdr = (struct timehdr *)skb_push(skb, sizeof(struct timehdr));
	time_hdr->time_data[0] = g_nHour;
	time_hdr->time_data[1] = g_nMin;
	time_hdr->time_data[2] = g_nSec;
	time_hdr->time_data[3] = g_nWeekday;
	time_hdr->time_data[4] = g_nMonth;
	time_hdr->time_data[5] = g_nDate;
	time_hdr->year = g_nYear;
	//uart_printf("year: %d\n",g_nYear);
	udp_send(skb, 3232236098, UDP,3538);

	return 0;
}

void time_skb_reserve(struct sk_buff *skb)
{
	udp_skb_reserve(skb);
	skb_reserve(skb, sizeof(struct timehdr));
}

