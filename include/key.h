#ifndef	_KEY_H
#define _KEY_H


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


extern volatile unsigned char Flag_key_incre;
extern volatile unsigned char Flag_key_decre;
extern volatile unsigned char Flag_key_menu;


void Keys_Scan();  // 按键扫描



#endif /* _KEY_H */


