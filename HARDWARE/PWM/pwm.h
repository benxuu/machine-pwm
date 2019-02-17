#ifndef __PWM_H
#define __PWM_H
#include "sys.h"


//extern u8  PWM_CD;// ռ�ձ�
//extern u16 PWM_fq;	// Ƶ��
//extern u16 PWM_arr;	// �Զ���װֵ��psc=0��PWMƵ��=72000/(arr+1)=80Khz	
//extern u16 PWM_val;//time1��ʱ��ֵ��ռ�ձ�ϸ��

void TIM1_PWM_Init_Reg(u16 arr,u16 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);
//����Ԥ��Ƶ�ʳ�ʼ��PWM,��λKHZ������Ƶ��PWMƵ��=72000/(arr+1)=80Khz
void PWM_Init_fq(u16 fq);	
void PWM_disable(void);  //����TIM1
void PWM_enable(void);

//����PWMռ�ձ�
void PWM_SET_CD(u8 cd);

//����PWMռ��ֵ
void PWM_SET_val(u16 val);
//�ϵ�PWMռ��ֵ
void PWM_up(u16 val);
//�µ�PWMռ��ֵ
void PWM_down(u16 val);
void PWM_demo(void);

#endif
