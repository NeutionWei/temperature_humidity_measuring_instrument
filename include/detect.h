#ifndef	_DETECT_H
#define _DETECT_H

extern unsigned char DS1302_Data[6];
extern unsigned char DS1302_Data_Tmp[6];
extern unsigned char DHT11_Data[4];
extern unsigned char DHT11_Data_Tmp[2];
extern unsigned char Flag_detect_data1;
extern unsigned char Flag_detect_data2;
extern unsigned char Flag_rh_get;
extern unsigned char Flag_tmp_get;
extern unsigned char Flag_DS1302_Write;


void DS1302_Get(); // 获得时钟数据
void DHT11_Get();	 // 获得温湿度数据
void Dete_Data();	 // 数据加工

#endif /* _DETECT_H */


