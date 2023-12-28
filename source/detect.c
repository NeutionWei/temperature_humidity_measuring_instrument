//*****************************头文件声明***************************
#include "reg52.h"
#include "display.h"
#include "oled.h"
#include "detect.h"
#include "ds1302.h"
#include "dht11.h"
#include "key.h"

sbit p01 = P0^1;

volatile unsigned char DS1302_Data[6];
volatile unsigned char DS1302_Data_Tmp[6];
volatile unsigned char DHT11_Data[4];
volatile unsigned char DHT11_Data_Tmp[2];
volatile unsigned char Flag_detect_data1;
volatile unsigned char Flag_detect_data2;
volatile unsigned char Flag_rh_get;
volatile unsigned char Flag_tmp_get;
volatile unsigned char ave;



void DS1302_Get()
{
	if(Flag_key_menu == MENU_NoADJ)
	{
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
		DS1302_Data_Tmp[0]	= DS1302_Data[0];
		DS1302_Data_Tmp[1]	= DS1302_Data[1];
		DS1302_Data_Tmp[2]	= DS1302_Data[2];
		DS1302_Data_Tmp[3]	= DS1302_Data[3];
		DS1302_Data_Tmp[4]	= DS1302_Data[4];
		DS1302_Data_Tmp[5]	= DS1302_Data[5];
	}
	//DisplayData[0] = smgduan[TIME[2]/16];				//时
	//DisplayData[1] = smgduan[TIME[2]&0x0f];				 
	//DisplayData[2] = 0x40;
	//DisplayData[3] = smgduan[TIME[1]/16];				//分
	//DisplayData[4] = smgduan[TIME[1]&0x0f];	
	//DisplayData[5] = 0x40;
	//DisplayData[6] = smgduan[TIME[0]/16];				//秒
	//DisplayData[7] = smgduan[TIME[0]&0x0f];
}


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
		//DHT11_Data_Tmp[0] = RH;				//接收湿度高八位
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
	//DHT11_Data_Tmp[3] = TL;         //接收温度低八位
	/*int hum, temp;
	
	if(0 == dht11_init())
	{
		if(0 == dht11_read(&hum, &temp))
		{
			//Flag_DHT11_Get = 1;
			OLED_ShowNum(25, 4, hum,  2, 16);
			OLED_ShowNum(35, 4, temp, 2, 16);
		}
	}
	
	while (1)
	{
		if (dht11_read(&hum, &temp) !=0 )
		{
			//printf("\n\rdht11 read err!\n\r");
			dht11_init();
		}
		else
		{
			//printf("\n\rDHT11 : %d humidity, %d temperature\n\r", hum, temp);
		}
	}*/
}

void Dete_Data()
{
	//int ret1, ret2;
	unsigned char tmp;
	//static unsigned char ave1;
	//static unsigned char ave2;
	
	//ret1 = Ave_Process();
	//ret2 = Ave_Process(DHT11_Data_Tmp[1], &ave2);
	
	//if(0 == ret1)
	if(Flag_rh_get == 1)
	{
		Flag_rh_get = 0;//zengjia
		tmp = DHT11_Data_Tmp[0];
		DHT11_Data[0] = tmp/10;
		DHT11_Data[1] = tmp%10;
		Flag_detect_data1 = 1;
	}
	//if(0 == ret2)
	if(Flag_tmp_get == 1)
	{
		Flag_tmp_get = 0;//zengjia
		tmp = DHT11_Data_Tmp[1];
		DHT11_Data[2] = tmp/10;
		DHT11_Data[3] = tmp%10;
		Flag_detect_data2 = 1;
	}
	
	/*if(Flag_key_menu = MENU_ADJ_HOUR)
	{
		// 时间停止增加(√)
		// 时间闪烁(√)
		// 时间调整按键生效
		if(i = 0)// 第一次调用该程序
		{
			for(i=0; i<3; i++)
				DS1302_Data_Tmp[i] = TIME[i];
			i = -1;
		}
		
		if(Flag_key_incre == 1)
		{
			Flag_key_incre = 0;	
			DS1302_Data_Tmp[2]++;
		}
		else if(Flag_key_decre == 1)
		{
			Flag_key_decre = 0;
			DS1302_Data_Tmp[2]--;
		}
	}
	else if(Flag_key_menu == MENU_ADJ_MIN)
	{
		if(Flag_key_incre == 1)
		{
			Flag_key_incre = 0;	
			DS1302_Data_Tmp[1]++;
		}
		else if(Flag_key_decre == 1)
		{
			Flag_key_decre = 0;
			DS1302_Data_Tmp[1]--;
		}
	}
	else if(Flag_key_menu == MENU_ADJ_SEC)
	{
		if(Flag_key_incre == 1)
		{
			Flag_key_incre = 0;	
			DS1302_Data_Tmp[0]++;
		}
		else if(Flag_key_decre == 1)
		{
			Flag_key_decre = 0;
			DS1302_Data_Tmp[0]--;
		}
	}*/
}