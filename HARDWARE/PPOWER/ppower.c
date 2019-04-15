#include "ppower.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//程控电源驱动 
//修改日期:2019/3/20
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) Ben 2019-2029
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////    
//LED IO初始化
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
