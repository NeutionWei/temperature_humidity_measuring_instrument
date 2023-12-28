/**
  ******************************************************************************
  * @file    main.c
  * @author  现代电子技术综合设计第10组
  * @date    2019-04~2019-05
  * @brief   基于STC89C52RC的温湿度显示与按键可调的时钟显示
  ******************************************************************************
  */ 

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "intrins.h"
#include "display.h"
#include "ds1302.h"
//#include "bmp.h"
#include "oled.h"
#include "key.h"
#include "detect.h"



 /**
  * @brief  延时函数
  * @param  x
  * @retval none
  */
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


 /**
  * @brief  主函数
  * @param  none
  * @retval none
  */
void main()
{	
	Disp_Init();		// 显示模块初始化
	DS1302_Init();	// DS1302初始化
	Delay(200);			// 延时等待稳定
	while(1)
	{
		Disp_Data();	// 显示温湿度与时钟数据
		Keys_Scan();  // 按键扫描
		DS1302_Get(); // 获得时钟数据
		DHT11_Get();	// 获得温湿度数据
		Dete_Data();	// 数据加工
	}
}



