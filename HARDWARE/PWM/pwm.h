#ifndef __PWM_H
#define __PWM_H
#include "sys.h"


//extern u8  PWM_CD;// 占空比
//extern u16 PWM_fq;	// 频率
//extern u16 PWM_arr;	// 自动重装值，psc=0，PWM频率=72000/(arr+1)=80Khz	
//extern u16 PWM_val;//time1定时器值，占空比细调

void TIM1_PWM_Init_Reg(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);
//根据预设频率初始化PWM,单位KHZ；不分频。PWM频率=72000/(arr+1)=80Khz
void PWM_Init_fq(u16 fq);	
void PWM_disable(void);  //禁用TIM1
void PWM_enable(void);

//设置PWM占空比
void PWM_SET_CD(u8 cd);

//设置PWM占空值
void PWM_SET_val(u16 val);
//上调PWM占空值
void PWM_up(u16 val);
//下调PWM占空值
void PWM_down(u16 val);
void PWM_demo(void);

#endif
