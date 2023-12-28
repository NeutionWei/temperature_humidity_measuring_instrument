#ifndef	_THD11_H
#define _THD11_H

#include "reg52.h"

extern unsigned char RH,RL,TH,TL;

//int dht11_init(void);
void DHT11_receive();      //接收40位的数据


#endif /* _THD11_H */


