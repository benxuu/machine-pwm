#ifndef __PPOWER_H
#define __PPOWER_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�̿ص�Դ���� 
//�޸�����:2019/3/20
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) Ben 2019-2029
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

void power_Init(void);//��ʼ��
void power_setC(u16 Set_Current);
void power_setV(u16 Set_voltage);	
void query_voltageout(void); 
void query_Current(void);
void power_shutdown(void);
void power_start(void);
//?????????,?????;
#endif
