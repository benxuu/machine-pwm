#include "ppower.h"
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
void power_Init(void)
{
}

void setSet_Currentout(u16 Set_Current)
{  
  printf("awu%d\r\n",Set_Current);
}
void setSet_voltageout(u16 Set_voltage)
{  
  printf("awu%d\r\n",Set_voltage);
}

void query_voltageout(void)
{  
  printf("aru\r\n");
}

void query_Current(void)
{  
  printf("ari\r\n");
}
