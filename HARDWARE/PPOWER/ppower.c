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
	power_setC(1000);//设置电流值为10A
	delay_ms(100);
	power_setV(0600);//设置电压值为6V；
}
void power_Init_vc(u16 v,u16 c)
{
	power_setV(v);//设置电压值为6V；
	delay_ms(100);
	power_setC(c);//设置电流值为10A
}
//wi 命令（设定电源输出流值范围 0000-1012）
void power_setC(u16 Set_Current)
{  
  printf("awi%d\r\n",Set_Current);
	setC=Set_Current;
}
//设定电源输出电压值范围 0000-6000
void power_setV(u16 Set_voltage)
{  
  printf("awu%d\r\n",Set_voltage);
	setV=Set_voltage;	
}
//读取输出实际电压值
void query_voltageout(void)
{  
  printf("aru\r\n");
}
//读取输出实际电流值
void query_Current(void)
{  
  printf("ari\r\n");
}
//关闭电源输出
void power_shutdown(void)
{  
  printf("awo0\r\n");
}
//开启电源输出
void power_start(void)
{  
  printf("awo1\r\n");
}
