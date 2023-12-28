#ifndef	_KEY_H
#define _KEY_H


#define 	key_state_0   0		// ������ʼ״̬
#define		key_state_1   1		// ��������ȷ��״̬
#define		key_state_2   2		// �����ͷ�״̬
#define	 	key_state_3   3		// ��������ȷ��״̬

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


void Keys_Scan();  // ����ɨ��



#endif /* _KEY_H */


