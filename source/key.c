#include "key.h"
#include <reg52.h>

/*
sbit key8 = P1^7;
sbit key1 = P1^0;
sbit p00 = P0^0;
sbit p01 = P0^1;
sbit p06 = P0^6;


void key_test()
{
	key8 = 0;
	if(key1 == 0)
	{
		Delayms(20);
		if(key1 == 0)
		{
			if(++Flag_key_menu >= MENU_ADJ_NUM)
				Flag_key_menu = 0;
		}
		while(!key1);
	}
	
}*/



volatile unsigned char Flag_key_incre;
volatile unsigned char Flag_key_decre;
volatile unsigned char Flag_key_menu;

//sbit GND = P1^7;
sbit PORT_K_MENU = P0^7;
sbit PORT_K_INCR = P0^6;
sbit PORT_K_DECR = P0^5;
sbit LED1 = P0^1;

void Keys_Scan()
{
	static unsigned int key_state = 0;
	unsigned char key_press;
	unsigned char key_input;
	//u8 key_return = 0;	
  //GND = 0;
	key_input  = !PORT_K_MENU;
	key_input  = key_input<<1;
	key_input |= (!PORT_K_INCR);
	key_input  = key_input<<1;
	key_input |= (!PORT_K_DECR);
	//key_input  = key_input<<1;
	
	key_press  = key_input;					// 读按键I/O电平
	switch (key_state)
	{
		case key_state_0:					// 按键初始态
			//if (key_press) key_state = key_state_1; // 键被按下，状态转换到键确认态
			if (key_press)
			{
				key_state = key_state_1;
				//ON_LED_R();
			}
			break;
			
		case key_state_1:					// 按键确认态
			if (key_press)
			{
				if(key_press & KEY_INCRE)
				{
						Flag_key_incre = 1;
				}
				else if(key_press & KEY_DECRE)
				{
						Flag_key_decre = 1;
				}
				else if(key_press & KEY_MENU)
				{
					// 每按一次，光标时间向后挪，直到最后才正常显示时间
					//Flag_key_menu = 1;
					//LED1 = ~LED1;
					//Flag_key_menu = !Flag_key_menu;
					if(++Flag_key_menu >= MENU_ADJ_NUM)
						Flag_key_menu = MENU_NoADJ;
				}
        key_state = key_state_2;
			}
			else
				key_state = key_state_0;	// 按键已抬起，转换到按键初始态
			break;
		case key_state_2:
			if (!key_press)
      {
				key_state = key_state_0;	// 按键已释放，转换到按键初始态
      }
			break;
/*		case key_state_3:
			if (!key_press)
				key_state = key_state_0; //按键已释放，转换到按键初始态
			
			break;*/
		default:break;
	}	
	//return key_return;
}

