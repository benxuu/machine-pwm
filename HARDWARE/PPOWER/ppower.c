#include "ppower.h"
#include "delay.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�̿ص�Դ���� 
//�޸�����:2019/3/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) Ben 2019-2029
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////    
//LED IO��ʼ��
u16 setV,setC,rtV,rtC;
void power_Init(void)
{
	power_setC(1000);//���õ���ֵΪ10A
	delay_ms(100);
	power_setV(0600);//���õ�ѹֵΪ6V��
}
void power_Init_vc(u16 v,u16 c)
{
	power_setV(v);//���õ�ѹֵΪ6V��
	delay_ms(100);
	power_setC(c);//���õ���ֵΪ10A
}
//wi ����趨��Դ�����ֵ��Χ 0000-1012��
void power_setC(u16 Set_Current)
{  
  printf("awi%d\r\n",Set_Current);
	setC=Set_Current;
}
//�趨��Դ�����ѹֵ��Χ 0000-6000
void power_setV(u16 Set_voltage)
{  
  printf("awu%d\r\n",Set_voltage);
	setV=Set_voltage;	
}
//��ȡ���ʵ�ʵ�ѹֵ
void query_voltageout(void)
{  
  printf("aru\r\n");
}
//��ȡ���ʵ�ʵ���ֵ
void query_Current(void)
{  
  printf("ari\r\n");
}
//�رյ�Դ���
void power_shutdown(void)
{  
  printf("awo0\r\n");
}
//������Դ���
void power_start(void)
{  
  printf("awo1\r\n");
}
