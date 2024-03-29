#ifndef __DS1302_H_
#define __DS1302_H_

//---包含头文件---//
#include<reg52.h>
#include<intrins.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//---定义ds1302使用的IO口---//
sbit DSIO = P3^7;
sbit RST  = P2^0;	//RST(CE)
sbit SCLK = P3^6;

//---定义全局函数---//
void DS1302_Write(unsigned char addr, unsigned char dat);
unsigned char DS1302_Read(unsigned char addr);
void DS1302_Init();
void DS1302_ReadTime();

//---加入全局变量--//
extern uchar TIME[7];	//加入全局变量
extern unsigned char code WRITE_RTC_ADDR[7];

#endif