#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

							  	 	    
#define ADC_CH1  1  	//ͨ��1		 	    
	   									   
void Adc1_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc1(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc1_Average(u8 ch,u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 	


void Adc1_Init4(void); 				//ADCͨ����ʼ��
u16  Get_Adc1ch4(void); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc1ch4_Average(u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ

void Adc2_Init14(void); 				//ADCͨ����ʼ��
u16  Get_Adc2ch14(void); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc2ch4_Average(u8 times);//�õ�ĳ��ͨ��10�β�����ƽ��ֵ 	  

#endif 

 
	   									   













