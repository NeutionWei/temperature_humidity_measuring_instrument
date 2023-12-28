#include "key.h"


//#define		key_input	  ((PORT_K_U<<1) | PORT_K_D)
#define 	key_state_0   0		// 按键初始状态
#define		key_state_1   1		// 按键按下确认状态
#define		key_state_2   2		// 按键释放状态
#define	 	key_state_3   3		// 按键长按确认状态

#define		KEY_DECRE	(1<<0)
#define		KEY_INCRE	(1<<1)
#define		KEY_MENU  (1<<2)

enum {
	MENU_NoADJ,
	MENU_ADJ_HOUR,
	MENU_ADJ_MIN,
	MENU_ADJ_SEC,
	MENU_ADJ_NUM,
};

volatile unsigned char Flag_key_incre;
volatile unsigned char Flag_key_decre;
volatile unsigned char Flag_key_menu;

void Keys_Scan()
{
	static unsigned int key_state = 0;
	unsigned char key_press;
	unsigned char key_input;
	//u8 key_return = 0;	
        
	//key_input  = !PORT_K_U;
	//key_input  = key_input<<1;
	//key_input |= (!PORT_K_D);
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
					if(++Flag_key_menu >= MENU_ADJ_NUM)
						Flag_key_menu = 0;
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

