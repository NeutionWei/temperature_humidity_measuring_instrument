/**
  ******************************************************************************
  * @file    main.c
  * @author  �ִ����Ӽ����ۺ���Ƶ�10��
  * @date    2019-04~2019-05
  * @brief   ����STC89C52RC����ʪ����ʾ�밴���ɵ���ʱ����ʾ
  ******************************************************************************
  */ 

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "intrins.h"
#include "display.h"
#include "ds1302.h"
//#include "bmp.h"
#include "oled.h"
#include "key.h"
#include "detect.h"



 /**
  * @brief  ��ʱ����
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
  * @brief  ������
  * @param  none
  * @retval none
  */
void main()
{	
	Disp_Init();		// ��ʾģ���ʼ��
	DS1302_Init();	// DS1302��ʼ��
	Delay(200);			// ��ʱ�ȴ��ȶ�
	while(1)
	{
		Disp_Data();	// ��ʾ��ʪ����ʱ������
		Keys_Scan();  // ����ɨ��
		DS1302_Get(); // ���ʱ������
		DHT11_Get();	// �����ʪ������
		Dete_Data();	// ���ݼӹ�
	}
}



