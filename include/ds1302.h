#ifndef __DS1302_H_
#define __DS1302_H_

//---����ͷ�ļ�---//
#include<reg52.h>
#include<intrins.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//---����ds1302ʹ�õ�IO��---//
sbit DSIO = P3^4;
sbit RST  = P3^5;
sbit SCLK = P1^5;

//---����ȫ�ֺ���---//
void DS1302_Write(unsigned char addr, unsigned char dat);
unsigned char DS1302_Read(unsigned char addr);
void DS1302_Init();
void DS1302_ReadTime();

//---����ȫ�ֱ���--//
extern uchar TIME[7];	//����ȫ�ֱ���

#endif