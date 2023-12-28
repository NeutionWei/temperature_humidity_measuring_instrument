/**
  ******************************************************************************
  * @file    detect.c
  * @author  现代电子技术综合设计第10组
  * @date    2019-04~2019-05
  * @brief   数据获取与加工相关Function
  ******************************************************************************
  */ 

#include "reg52.h"
#include "display.h"
#include "oled.h"
#include "detect.h"
#include "ds1302.h"
#include "dht11.h"
#include "key.h"


volatile unsigned char DS1302_Data[6];
volatile unsigned char DS1302_Data_Tmp[6];
volatile unsigned char DHT11_Data[4];
volatile unsigned char DHT11_Data_Tmp[2];
volatile unsigned char Flag_detect_data1;
volatile unsigned char Flag_detect_data2;
volatile unsigned char Flag_rh_get;
volatile unsigned char Flag_tmp_get;
volatile unsigned char Flag_DS1302_Write;
volatile unsigned char Flag_read_only_one;
volatile unsigned char Flag_read_only_get;
volatile unsigned char ave;


 /**
  * @brief  获得时钟数据
  * @param  none
  * @retval none
  */
void DS1302_Get()
{	
	if(Flag_key_menu == MENU_NoADJ)
	{
		// 读时间
		DS1302_ReadTime();
		DS1302_Data[0] = TIME[2]/16;	//时
		DS1302_Data[1] = TIME[2]&0x0f;
		DS1302_Data[2] = TIME[1]/16;	//分
		DS1302_Data[3] = TIME[1]&0x0f;
		DS1302_Data[4] = TIME[0]/16;	//秒
		DS1302_Data[5] = TIME[0]&0x0f;
	}
	else
	{
		// 不读时间
		if(Flag_read_only_one == 1)
		{
			Flag_read_only_one = 0;
			Flag_read_only_get = 1;
			DS1302_Data_Tmp[0]	= DS1302_Data[0];
			DS1302_Data_Tmp[1]	= DS1302_Data[1];
			DS1302_Data_Tmp[2]	= DS1302_Data[2];
			DS1302_Data_Tmp[3]	= DS1302_Data[3];
			DS1302_Data_Tmp[4]	= DS1302_Data[4];
			DS1302_Data_Tmp[5]	= DS1302_Data[5];
		}
	}
}



 /**
  * @brief  获得温湿度数据
  * @param  none
  * @retval none
  */
void DHT11_Get()
{
	static volatile unsigned char temp1, temp2, oldtemp1, oldtemp2;
	unsigned char delta;
	static volatile unsigned int delay;
	static volatile unsigned char cnt;

	if(cnt == 0)
	{
		DHT11_receive();
		oldtemp1 = RH;
		oldtemp2 = TH;
		cnt++;
	}

	
	if(++delay >= 100)
	{
		delay = 0;
		
		DHT11_receive();
		temp1 = RH; 
		
		if(temp1 >= oldtemp1)
			delta = temp1 - oldtemp1;
		else
			delta = oldtemp1 - temp1;

		if(delta <= 20)
		{
			DHT11_Data_Tmp[0] = temp1;				//接收湿度高八位
			oldtemp1 = temp1;
			Flag_rh_get = 1;
		}
		//DHT11_Data_Tmp[0] = RH;			  	//接收湿度高八位
		//DHT11_Data_Tmp[1] = RL;        //接收湿度低八位
		
		temp2 = TH;         
		if(temp2 >= oldtemp2)
			delta = temp2 - oldtemp2;
		else
			delta = oldtemp2 - temp2;

		if(delta <= 3)
		{
			DHT11_Data_Tmp[1] = temp2;         //接收温度高八位
			oldtemp2 = temp2;
			Flag_tmp_get = 1;
		}
	}

}



 /**
  * @brief  数据加工
  * @param  none
  * @retval none
  */
void Dete_Data()
{
	unsigned char tmp;
	static volatile unsigned char flag_adj_sec;
	unsigned char time_write_tmp[3];
	
	if(Flag_rh_get == 1)
	{
		Flag_rh_get = 0;
		tmp = DHT11_Data_Tmp[0];
		DHT11_Data[0] = tmp/10;
		DHT11_Data[1] = tmp%10;
		Flag_detect_data1 = 1;
	}
	
	if(Flag_tmp_get == 1)
	{
		Flag_tmp_get = 0;
		tmp = DHT11_Data_Tmp[1];
		DHT11_Data[2] = tmp/10;
		DHT11_Data[3] = tmp%10;
		Flag_detect_data2 = 1;
	}
	
	if(Flag_key_menu == MENU_ADJ_HOUR)
	{
		// 时间停止增加(√)
		// 时间闪烁(√)
		// 时间调整按键生效(√)
		// 循环按菜单键后，写入时间(√)
		if(Flag_read_only_get == 0)
			Flag_read_only_one	= 1;
		
		if(Flag_key_incre == 1)
		{
			Flag_key_incre = 0;	
			//DS1302_Data_Tmp[1]++;
			if(++DS1302_Data_Tmp[1] >= 10)
			{
				DS1302_Data_Tmp[0]++;
				DS1302_Data_Tmp[1] = 0;
				//if(++DS1302_Data_Tmp[0] >= 2)
					//DS1302_Data_Tmp[0] = 0;
				//DS1302_Data_Tmp[1] = 0;
			}
			if((DS1302_Data_Tmp[1] == 4) && (DS1302_Data_Tmp[0] == 2))
			{
				DS1302_Data_Tmp[0] = 0;
				DS1302_Data_Tmp[1] = 0;
			}

		}
		else if(Flag_key_decre == 1)
		{
			Flag_key_decre = 0;
			if(--DS1302_Data_Tmp[1] >= 255)
			{
				if(--DS1302_Data_Tmp[0] >= 255)
					DS1302_Data_Tmp[0] = 2;
				DS1302_Data_Tmp[1] = 3;
			}
		}
	}
	else if(Flag_key_menu == MENU_ADJ_MIN)
	{
		if(Flag_key_incre == 1)
		{
			Flag_key_incre = 0;	
			if(++DS1302_Data_Tmp[3] >= 10)
			{
				if(++DS1302_Data_Tmp[2] >= 6)
					DS1302_Data_Tmp[2] = 0;
				DS1302_Data_Tmp[3] = 0;
			}
		}
		else if(Flag_key_decre == 1)
		{
			Flag_key_decre = 0;
			if(--DS1302_Data_Tmp[3] >= 255)
			{
				if(--DS1302_Data_Tmp[2] >= 255)
					DS1302_Data_Tmp[2] = 5;
				DS1302_Data_Tmp[3] = 9;
			}
		}
	}
	else if(Flag_key_menu == MENU_ADJ_SEC)
	{
		flag_adj_sec = 1;// 该分支已执行标志
		if(Flag_key_incre == 1)
		{
			Flag_key_incre = 0;	
			if(++DS1302_Data_Tmp[5] >= 10)
			{
				if(++DS1302_Data_Tmp[4] >= 6)
					DS1302_Data_Tmp[4] = 0;
				DS1302_Data_Tmp[5] = 0;
			}
		}
		else if(Flag_key_decre == 1)
		{
			Flag_key_decre = 0;
			if(--DS1302_Data_Tmp[5] >= 255)
			{
				if(--DS1302_Data_Tmp[4] >= 255)
					DS1302_Data_Tmp[4] = 5;
				DS1302_Data_Tmp[5] = 9;
			}
		}
	}
	else
	{
		if(flag_adj_sec == 1)
		{
			flag_adj_sec = 0;
			Flag_read_only_get = 0;
			
			time_write_tmp[0] = ((DS1302_Data_Tmp[4]<<4) | DS1302_Data_Tmp[5]);
			time_write_tmp[1] = ((DS1302_Data_Tmp[2]<<4) | DS1302_Data_Tmp[3]);
			time_write_tmp[2] = ((DS1302_Data_Tmp[0]<<4) | DS1302_Data_Tmp[1]);
			
			DS1302_Write(0x8E,0x00);		 //禁止写保护，就是关闭写保护功能
			DS1302_Write(WRITE_RTC_ADDR[0], time_write_tmp[0]);
			DS1302_Write(WRITE_RTC_ADDR[1], time_write_tmp[1]);
			DS1302_Write(WRITE_RTC_ADDR[2], time_write_tmp[2]);
			DS1302_Write(WRITE_RTC_ADDR[3], TIME[3]);
			DS1302_Write(WRITE_RTC_ADDR[4], TIME[4]);
			DS1302_Write(WRITE_RTC_ADDR[5], TIME[5]);
			DS1302_Write(0x8E,0x80);		 //打开写保护功能
			Flag_DS1302_Write = 1;
		}
	}
}