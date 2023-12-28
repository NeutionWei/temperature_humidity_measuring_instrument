/**************************************************************************************
*		              基于单片机的温湿度与时钟显示											  *
实现现象：
注意事项：																				  
***************************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
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
* 函 数 名       : Init_Time0
* 函数功能		   : 定时器0初始化程序
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/

void Timer0_Init()
{
	TMOD |= 0x01;						 // 设为工作方式1
	TH0 = (65536 - 10000)/256;
	TL0 = (65536 - 10000)%256; // 10ms溢出
	TR0 = 1;								 // 开定时器0
	ET0 = 1;								 // 使能定时器0中断
	EA  = 1;								 // 使能全局中断
}



/*******************************************************************************
* 函 数 名       : Init_Time1
* 函数功能		   : 定时器1初始化程序
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/

void Timer1_Init()
{
	TMOD |= 0x10;						 				// 设为工作方式1
	TH1 = ((65536 - 10000) >> 8);		// 赋值高8位
	TL1 = ((65536 - 10000) & 0xff); // 赋值低8位，50000us溢出
	TR0 = 1;								 				// 开定时器1
	EA  = 1;
	/*TMOD |= 0x20;						 				// 设为工作方式2
	TH0 = TL0 = 0; 									// 256us溢出
	TR0 = 1;								 				// 开定时器1*/
}




void Timer1_usDelay(int us)
{
/*#define		Timer1_CNTR		((TH0 << 8) | TL0)
	
	unsigned int cnt = us; 					// 1us对应1个计数值
	unsigned int pre = Timer1_CNTR;	// 获得当前计数值
	unsigned int cur;
	unsigned int delta;
	
	while(cnt > 0)
	{
		cur = Timer1_CNTR;	// 获得最新计数值
		if(cur >= pre)
			delta = cur - pre;
		else
			delta = cur + (50000 - pre);
		cnt = cnt - delta;
		pre = cur;
	}*/
	
	int cnt = us; 					// 1us对应1个计数值
	int pre = TL0;					// 获得当前计数值
	int cur;
	int delta;
	
	while(cnt > 0)
	{
		cur = TL0;						// 获得最新计数值
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

//******************************软件延时函数************************* 
void Delayms(unsigned int ms) 
{    
  unsigned int  i;      
  do    
   {        
     for(i=700;i;i--);                 //以1ms为延时单位   
   } while(--ms);   
} 



/*******************************************************************************
* 函 数 名       : main
* 函数功能		   : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/

void main()
{	
//	p00 = 0;
//	p06 = 0;
//	p01 = 1;
	GND_P00 = 0;
	//Timer0_Init();	// 定时器0初始化
	//Timer1_Init();	// 定时器1初始化
	Disp_Init();		// 显示模块初始化
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
			Disp_Data();	// 显示温湿度数据
			//DHT11_receive();
			Keys_Scan();  // 按键扫描
			DS1302_Get(); // 获得时钟数据
			DHT11_Get();	// 获得温湿度数据
			Dete_Data();	// 数据处理
		}
	}
}



/*******************************************************************************
* 函 数 名       : Time1_Int
* 函数功能		   : 定时器0中断服务程序
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/

void Timer1_Int() interrupt 3
{	
	//static unsigned char Cnt_Timer0;
	

	TH0 = (65536 - 10000)/256;
	TL0 = (65536 - 10000)%256; // 10ms溢出
	
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



