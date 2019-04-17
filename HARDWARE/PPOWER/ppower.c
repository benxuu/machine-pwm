#include "ppower.h"
#include "delay.h"
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
u16 setV,setC,rtV,rtC;
void power_Init(void)
{
	power_setC(1000);
	delay_ms(50);
	power_setV(0100);
}

void power_setC(u16 Set_Current)
{  
  printf("awu%d\r\n",Set_Current);
	setC=Set_Current;
}
void power_setV(u16 Set_voltage)
{  
  printf("awu%d\r\n",Set_voltage);
	setV=Set_voltage;	
}

void query_voltageout(void)
{  
  printf("aru\r\n");
}

void query_Current(void)
{  
  printf("ari\r\n");
}

void power_shutdown(void)
{  
  printf("ari\r\n");
}
void power_start(void)
{  
  printf("ari\r\n");
}
