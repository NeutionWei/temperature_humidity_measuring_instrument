/**
  ******************************************************************************
  * @file    display.c
  * @author  �ִ����Ӽ����ۺ���Ƶ�10��
  * @date    2019-04~2019-05
  * @brief   ����ʾ���Function
  ******************************************************************************
  */ 

#include "display.h"
#include "oled.h"
#include "bmp.h"
#include "detect.h"
#include "key.h"


 /**
  * @brief  ��ʾģ���ʼ��
  * @param  none
  * @retval none
  */
void Disp_Init()
{
	OLED_Init();			// OLED��ʼ��
	OLED_Clear(); 		// OLED����
	OLED_ShowCHinese(0,  0, 4);	// ��ʱ��
	OLED_ShowCHinese(16, 0, 5);	// ���䡱
	OLED_ShowChar(32, 0, ':');
	OLED_ShowChar(48, 0, '-');
	OLED_ShowChar(56, 0, '-');
	OLED_ShowChar(64, 0, ':');
	OLED_ShowChar(72, 0, '-');
	OLED_ShowChar(80, 0, '-');
	OLED_ShowChar(88, 0, ':');
	OLED_ShowChar(96, 0, '-');
	OLED_ShowChar(104,0, '-');
	OLED_ShowCHinese(0,  3, 0); // ���¡�
	OLED_ShowCHinese(16, 3, 1);	// ���ȡ�
	OLED_ShowChar(32, 3, ':');
	OLED_ShowChar(48, 3, '-');
	OLED_ShowChar(56, 3, '-');
	//OLED_ShowChar(64, 3, '.');
	//OLED_ShowChar(72, 3, '-');
	//OLED_ShowChar(80, 3, '-');
	//OLED_ShowChar(96-24, 3, 'C');
	OLED_ShowCHinese(96-24, 3, 6);	// ���ȡ�
	OLED_ShowCHinese(0,  6, 2);	// ��ʪ��
	OLED_ShowCHinese(16, 6, 3);	// ���ȡ�
	OLED_ShowChar(32, 6, ':');
	OLED_ShowChar(48, 6, '-');
	OLED_ShowChar(56, 6, '-');
	//OLED_ShowChar(64, 6, '.');
	//OLED_ShowChar(72, 6, '-');
	//OLED_ShowChar(80, 6, '-');
	//OLED_ShowChar(96-24, 6, '%');
	OLED_ShowChar(96-24, 6, 'R');
	OLED_ShowChar(104-24,6, 'H');
}


 /**
  * @brief  ��ʾ��ʪ����ʱ������
  * @param  none
  * @retval none
  */
void Disp_Data()
{
	static unsigned int delay_hour;
	static unsigned int delay_min;
	static unsigned int delay_sec;
	
	
	// ����������ʾ
	if(Flag_key_menu == MENU_NoADJ)
	{
		if(Flag_DS1302_Write == 1)
		{
			Flag_DS1302_Write = 0;
			// д����һ�β���ʾ
		}
		else
		{
			// ʱ����ʾ
			OLED_ShowNum(48, 0, DS1302_Data[0], 1, 16);
			OLED_ShowNum(56, 0, DS1302_Data[1], 1, 16);
			//OLED_ShowChar(45, 2, ':');
			OLED_ShowNum(72, 0, DS1302_Data[2], 1, 16);
			OLED_ShowNum(80, 0, DS1302_Data[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			OLED_ShowNum(96, 0, DS1302_Data[4], 1, 16);
			OLED_ShowNum(104,0, DS1302_Data[5], 1, 16);
		}
	}
	else if(Flag_key_menu == MENU_ADJ_HOUR)
	{
		if(++delay_hour >= 50)
			delay_hour = 0;
		
		if(delay_hour <= 25)
		{
			// ʱ����ʾ
			OLED_ShowNum(48, 0, DS1302_Data_Tmp[0], 1, 16);
			OLED_ShowNum(56, 0, DS1302_Data_Tmp[1], 1, 16);
			//OLED_ShowChar(45, 2, ':');
			OLED_ShowNum(72, 0, DS1302_Data_Tmp[2], 1, 16);
			OLED_ShowNum(80, 0, DS1302_Data_Tmp[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			OLED_ShowNum(96, 0, DS1302_Data_Tmp[4], 1, 16);
			OLED_ShowNum(104,0, DS1302_Data_Tmp[5], 1, 16);
		}
		else
		{
			//OLED_ShowNum(48, 0, DS1302_Data_Tmp[0], 1, 16);
			//OLED_ShowNum(56, 0, DS1302_Data_Tmp[1], 1, 16);
			OLED_ShowChar(48, 0, ' ');
			OLED_ShowChar(56, 0, ' ');
			OLED_ShowNum(72, 0, DS1302_Data_Tmp[2], 1, 16);
			OLED_ShowNum(80, 0, DS1302_Data_Tmp[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			OLED_ShowNum(96, 0, DS1302_Data_Tmp[4], 1, 16);
			OLED_ShowNum(104,0, DS1302_Data_Tmp[5], 1, 16);
		}
	}
	else if(Flag_key_menu == MENU_ADJ_MIN)
	{
		if(++delay_min >= 50)
			delay_min = 0;
		
		if(delay_min <= 25)
		{
			// ʱ����ʾ
			OLED_ShowNum(48, 0, DS1302_Data_Tmp[0], 1, 16);
			OLED_ShowNum(56, 0, DS1302_Data_Tmp[1], 1, 16);
			//OLED_ShowChar(45, 2, ':');
			OLED_ShowNum(72, 0, DS1302_Data_Tmp[2], 1, 16);
			OLED_ShowNum(80, 0, DS1302_Data_Tmp[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			OLED_ShowNum(96, 0, DS1302_Data_Tmp[4], 1, 16);
			OLED_ShowNum(104,0, DS1302_Data_Tmp[5], 1, 16);
		}
		else
		{
			OLED_ShowNum(48, 0, DS1302_Data_Tmp[0], 1, 16);
			OLED_ShowNum(56, 0, DS1302_Data_Tmp[1], 1, 16);
			OLED_ShowChar(72, 0, ' ');
			OLED_ShowChar(80, 0, ' ');
			//OLED_ShowNum(72, 0, DS1302_Data_Tmp[2], 1, 16);
			//OLED_ShowNum(80, 0, DS1302_Data_Tmp[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			OLED_ShowNum(96, 0, DS1302_Data_Tmp[4], 1, 16);
			OLED_ShowNum(104,0, DS1302_Data_Tmp[5], 1, 16);
		}
	}
	else if(Flag_key_menu == MENU_ADJ_SEC)
	{
		if(++delay_sec >= 50)
			delay_sec = 0;
		
		if(delay_sec <= 25)
		{
			// ʱ����ʾ
			OLED_ShowNum(48, 0, DS1302_Data_Tmp[0], 1, 16);
			OLED_ShowNum(56, 0, DS1302_Data_Tmp[1], 1, 16);
			//OLED_ShowChar(45, 2, ':');
			OLED_ShowNum(72, 0, DS1302_Data_Tmp[2], 1, 16);
			OLED_ShowNum(80, 0, DS1302_Data_Tmp[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			OLED_ShowNum(96, 0, DS1302_Data_Tmp[4], 1, 16);
			OLED_ShowNum(104,0, DS1302_Data_Tmp[5], 1, 16);
		}
		else
		{
			OLED_ShowNum(48, 0, DS1302_Data_Tmp[0], 1, 16);
			OLED_ShowNum(56, 0, DS1302_Data_Tmp[1], 1, 16);
			OLED_ShowChar(96, 0, ' ');
			OLED_ShowChar(104, 0, ' ');
			OLED_ShowNum(72, 0, DS1302_Data_Tmp[2], 1, 16);
			OLED_ShowNum(80, 0, DS1302_Data_Tmp[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			//OLED_ShowNum(96, 0, DS1302_Data_Tmp[4], 1, 16);
			//OLED_ShowNum(104,0, DS1302_Data_Tmp[5], 1, 16);
		}
	}
	
	if(Flag_detect_data2)
	{
		//Flag_detect_data = 0;
		// �¶���ʾ
		OLED_ShowNum(48, 3, DHT11_Data[2], 1, 16);
		OLED_ShowNum(56, 3, DHT11_Data[3], 1, 16);
		//OLED_ShowNum(72, 3, DHT11_Data[3]/10, 1, 16);
		//OLED_ShowNum(80, 3, DHT11_Data[3]%10, 1, 16);
	}
	if(Flag_detect_data1)
	{
		// ʪ����ʾ
		OLED_ShowNum(48, 6, DHT11_Data[0], 1, 16);
		OLED_ShowNum(56, 6, DHT11_Data[1], 1, 16);
		//OLED_ShowNum(72, 6, DHT11_Data[1]/10, 1, 16);
		//OLED_ShowNum(80, 6, DHT11_Data[1]%10, 1, 16);
	}
}
