#ifndef __TIME_H
#define __TIME_H

/*
 *	This structure defines an time header.
 */

__packed struct timehdr {
	int time_data[8];
};//__attribute__ ((packed));

int time_init(void);
int time_send(struct sk_buff *skb, int g_nYear,int g_nMonth,
	int g_nDate,int g_nWeekday,int g_nHour,int g_nMin,int g_nSec);
void time_skb_reserve(struct sk_buff *skb);

#endif /* __TIME_H */
