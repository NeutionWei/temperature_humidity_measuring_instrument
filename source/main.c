/**************************************************************************************
*		              ���ڵ�Ƭ������ʪ����ʱ����ʾ											  *
ʵ������
ע�����																				  
***************************************************************************************/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "intrins.h"
#include "display.h"
#include "ds1302.h"
//#include "bmp.h"
#include "oled.h"
#include "key.h"
#include "detect.h"


volatile unsigned char Cnt_MainLoop;
volatile unsigned char Flag_MainLoop;

sbit GND_P00 = P0^0;
//unsigned char flag_300ms;

/*******************************************************************************
* �� �� ��       : Init_Time0
* ��������		   : ��ʱ��0��ʼ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/

void Timer0_Init()
{
	TMOD |= 0x01;						 // ��Ϊ������ʽ1
	TH0 = (65536 - 10000)/256;
	TL0 = (65536 - 10000)%256; // 10ms���
	TR0 = 1;								 // ����ʱ��0
	ET0 = 1;								 // ʹ�ܶ�ʱ��0�ж�
	EA  = 1;								 // ʹ��ȫ���ж�
}



/*******************************************************************************
* �� �� ��       : Init_Time1
* ��������		   : ��ʱ��1��ʼ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/

void Timer1_Init()
{
	TMOD |= 0x10;						 				// ��Ϊ������ʽ1
	TH1 = ((65536 - 10000) >> 8);		// ��ֵ��8λ
	TL1 = ((65536 - 10000) & 0xff); // ��ֵ��8λ��50000us���
	TR0 = 1;								 				// ����ʱ��1
	EA  = 1;
	/*TMOD |= 0x20;						 				// ��Ϊ������ʽ2
	TH0 = TL0 = 0; 									// 256us���
	TR0 = 1;								 				// ����ʱ��1*/
}




void Timer1_usDelay(int us)
{
/*#define		Timer1_CNTR		((TH0 << 8) | TL0)
	
	unsigned int cnt = us; 					// 1us��Ӧ1������ֵ
	unsigned int pre = Timer1_CNTR;	// ��õ�ǰ����ֵ
	unsigned int cur;
	unsigned int delta;
	
	while(cnt > 0)
	{
		cur = Timer1_CNTR;	// ������¼���ֵ
		if(cur >= pre)
			delta = cur - pre;
		else
			delta = cur + (50000 - pre);
		cnt = cnt - delta;
		pre = cur;
	}*/
	
	int cnt = us; 					// 1us��Ӧ1������ֵ
	int pre = TL0;					// ��õ�ǰ����ֵ
	int cur;
	int delta;
	
	while(cnt > 0)
	{
		cur = TL0;						// ������¼���ֵ
		if(cur >= pre)
			delta = cur - pre;
		else
			delta = cur + (256 - pre);
		cnt = cnt - delta;
		pre = cur;
		
	}	
}




/*void Timer1_msDelay(int ms)
{
	int cnt = ms;
	
	while(cnt >= 0)
	{
		Timer1_usDelay(1000);
		cnt--;
	}
}

void Timer1_sDelay(int s)
{
	int cnt = s;
	
	while(cnt >= 0)
	{
		Timer1_msDelay(1000);
		cnt--;
	}
}*/

void Delay(volatile unsigned char x)
{
	unsigned char i = 0;
	
	while(x--)
	{
		while(--i)
		{
			_nop_();
			_nop_();
			_nop_();
			_nop_();
			//asm("nop");
			//asm("nop");
			//asm("nop");
			//asm("nop");
		}
	}
}

//******************************�����ʱ����************************* 
void Delayms(unsigned int ms) 
{    
  unsigned int  i;      
  do    
   {        
     for(i=700;i;i--);                 //��1msΪ��ʱ��λ   
   } while(--ms);   
} 



/*******************************************************************************
* �� �� ��       : main
* ��������		   : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/

void main()
{	
//	p00 = 0;
//	p06 = 0;
//	p01 = 1;
	GND_P00 = 0;
	//Timer0_Init();	// ��ʱ��0��ʼ��
	//Timer1_Init();	// ��ʱ��1��ʼ��
	Disp_Init();		// ��ʾģ���ʼ��
	DS1302_Init();
	Delay(200);
	while(1)
	{
		//p08 = 0;
		//Timer1_sDelay(1);
		//p08 = 1;
		//Timer1_sDelay(1);
		//p08 = 0;
		//if(Flag_MainLoop == 1)
		{
			//Flag_MainLoop = 0;
			//OLED_Clear();
//			key_test();
			Disp_Data();	// ��ʾ��ʪ������
			//DHT11_receive();
			Keys_Scan();  // ����ɨ��
			DS1302_Get(); // ���ʱ������
			DHT11_Get();	// �����ʪ������
			Dete_Data();	// ���ݴ���
		}
	}
}



/*******************************************************************************
* �� �� ��       : Time1_Int
* ��������		   : ��ʱ��0�жϷ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/

void Timer1_Int() interrupt 3
{	
	//static unsigned char Cnt_Timer0;
	

	TH0 = (65536 - 10000)/256;
	TL0 = (65536 - 10000)%256; // 10ms���
	
	//if()
	//Flag_MainLoop = 1;
	/*if(++Cnt_Timer0 >= 8)	// 8*125us = 1ms
	{
		//Cnt_Timer0 = 0;
		if(++Cnt_MainLoop >= 10) // 10*10ms = 100ms
		{
			Cnt_MainLoop  = 0;
			Flag_MainLoop = 1;
		}
	}	*/ 
}



