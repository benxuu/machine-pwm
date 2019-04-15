#ifndef __PPOWER_H
#define __PPOWER_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//程控电源驱动 
//修改日期:2019/3/20
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) Ben 2019-2029
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

void power_Init(void);//初始化
void power_setC(u16 Set_Current);
void power_setV(u16 Set_voltage);	
void query_voltageout(void); 
void query_Current(void);
void power_shutdown(void);
void power_start(void);
//?????????,?????;
#endif
