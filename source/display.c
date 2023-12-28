#include "display.h"
#include "oled.h"
#include "bmp.h"
#include "detect.h"

void Disp_Init()
{
	OLED_Init();			// OLED初始化
	OLED_Clear(); 		// OLED清屏
	OLED_ShowCHinese(0,  0, 4);	// “时”
	OLED_ShowCHinese(16, 0, 5);	// “间”
	OLED_ShowChar(32, 0, ':');
	OLED_ShowChar(48, 0, '-');
	OLED_ShowChar(56, 0, '-');
	OLED_ShowChar(64, 0, ':');
	OLED_ShowChar(72, 0, '-');
	OLED_ShowChar(80, 0, '-');
	OLED_ShowChar(88, 0, ':');
	OLED_ShowChar(96, 0, '-');
	OLED_ShowChar(104,0, '-');
	OLED_ShowCHinese(0,  3, 0); // “温”
	OLED_ShowCHinese(16, 3, 1);	// “度”
	OLED_ShowChar(32, 3, ':');
	OLED_ShowChar(48, 3, '-');
	OLED_ShowChar(56, 3, '-');
	//OLED_ShowChar(64, 3, '.');
	//OLED_ShowChar(72, 3, '-');
	//OLED_ShowChar(80, 3, '-');
	//OLED_ShowChar(96-24, 3, 'C');
	OLED_ShowCHinese(96-24, 3, 6);	// “度”
	OLED_ShowCHinese(0,  6, 2);	// “湿”
	OLED_ShowCHinese(16, 6, 3);	// “度”
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

void Disp_Data()
{
	//OLED_Clear();
	
	// 时间显示
	OLED_ShowNum(48, 0, DS1302_Data[0], 1, 16);
	OLED_ShowNum(56, 0, DS1302_Data[1], 1, 16);
	//OLED_ShowChar(45, 2, ':');
	OLED_ShowNum(72, 0, DS1302_Data[2], 1, 16);
	OLED_ShowNum(80, 0, DS1302_Data[3], 1, 16);
	//OLED_ShowChar(75, 2, ':');	
	OLED_ShowNum(96, 0, DS1302_Data[4], 1, 16);
	OLED_ShowNum(104,0, DS1302_Data[5], 1, 16);

	/*
	// 按键调整显示
	if(Flag_key_menu == 0)
	{
			// 时间显示
			OLED_ShowNum(48, 0, DS1302_Data[0], 1, 16);
			OLED_ShowNum(56, 0, DS1302_Data[1], 1, 16);
			//OLED_ShowChar(45, 2, ':');
			OLED_ShowNum(72, 0, DS1302_Data[2], 1, 16);
			OLED_ShowNum(80, 0, DS1302_Data[3], 1, 16);
			//OLED_ShowChar(75, 2, ':');	
			OLED_ShowNum(96, 0, DS1302_Data[4], 1, 16);
			OLED_ShowNum(104,0, DS1302_Data[5], 1, 16);
	}*/

	
	if(Flag_detect_data2)
	{
		//Flag_detect_data = 0;
		// 温度显示
		OLED_ShowNum(48, 3, DHT11_Data[2], 1, 16);
		OLED_ShowNum(56, 3, DHT11_Data[3], 1, 16);
		//OLED_ShowNum(72, 3, DHT11_Data[3]/10, 1, 16);
		//OLED_ShowNum(80, 3, DHT11_Data[3]%10, 1, 16);
	}
	if(Flag_detect_data1)
	{
		// 湿度显示
		OLED_ShowNum(48, 6, DHT11_Data[0], 1, 16);
		OLED_ShowNum(56, 6, DHT11_Data[1], 1, 16);
		//OLED_ShowNum(72, 6, DHT11_Data[1]/10, 1, 16);
		//OLED_ShowNum(80, 6, DHT11_Data[1]%10, 1, 16);
	}
/*OLED_Clear();
	OLED_ShowCHinese(0,0,0);//中
	OLED_ShowCHinese(18,0,1);//景
	OLED_ShowCHinese(36,0,2);//园
	OLED_ShowCHinese(54,0,3);//电
	OLED_ShowCHinese(72,0,4);//子
	OLED_ShowCHinese(90,0,5);//科
	OLED_ShowCHinese(108,0,6);//技
	OLED_ShowString(0,2,"1.3' OLED TEST");
	OLED_ShowString(8,2,"ZHONGJINGYUAN");  
	OLED_ShowString(20,4,"2014/05/01"); */ 
}
