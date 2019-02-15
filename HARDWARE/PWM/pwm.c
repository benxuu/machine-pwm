#include "pwm.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//PWM  ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWM�����ʼ��
//arr���Զ���װֵ��psc=0��PWMƵ��=72000/(arr+1)=80Khz
//psc��ʱ��Ԥ��Ƶ��
u8  PWM_CD;// ռ�ձ�
u16 PWM_fq;	// Ƶ��
u16 PWM_arr;	// �Զ���װֵ��psc=0��PWMƵ��=72000/(arr+1)=80Khz
u16 PWM_val;//time1��ʱ��ֵ��ռ�ձ�ϸ��

void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	PWM_val=0;
	TIM_SetCompare1(TIM1,PWM_val);//Ĭ��PWM���Ϊ0��
 
   
}

//����Ԥ��Ƶ�ʳ�ʼ��PWM,��λKHZ������Ƶ��PWMƵ��=72000/(arr+1)=80Khz
void PWM_Init_fq(u16 fq){	
	PWM_arr=72000/fq-1;
	PWM_fq=fq; 
	TIM1_PWM_Init(PWM_arr,0);
	//TIM1_PWM_Init(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
}
	
void PWM_disable(){
	TIM_SetCompare1(TIM1,0);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, DISABLE);// �رն�ʱ��1ʱ��
	TIM_CtrlPWMOutputs(TIM1,DISABLE);	//MOE �����ʹ��	 
	TIM_Cmd(TIM1, DISABLE);  //����TIM1	
	//GPIOA->BRR=GPIO_Pin_8;//����ߵ�ƽ��BSRR���0  
}

void PWM_enable(){
TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
}

//����PWMռ�ձ�
void PWM_SET_CD(u8 cd){	
	PWM_val=(PWM_arr+1)*cd/100;
	PWM_CD=cd;
	TIM_SetCompare1(TIM1,PWM_val);
}

//����PWMռ��ֵ
void PWM_SET_val(u16 val){	
	PWM_val=val;	
	TIM_SetCompare1(TIM1,val);
}

//�ϵ�PWMռ��ֵ
void PWM_up(u16 val){
	PWM_val+=val;	
	TIM_SetCompare1(TIM1,PWM_val);
}
//�µ�PWMռ��ֵ
void PWM_down(u16 val){	
	PWM_val-=val;
	if (PWM_val>60000) PWM_val=0;	
	TIM_SetCompare1(TIM1,PWM_val);
}

//pwm��ʾ��led0�����Զ��仯
void PWM_demo(){
	   
	u8 dir=1;		
	u16 i=600;
	TIM1_PWM_Init(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
   	while(i)
	{
		if (PWM_val>60000) PWM_val=50; 
		i--;
 		delay_ms(10);	 
		if(dir)PWM_val++;
		else PWM_val--;	 
 		if(PWM_val>300){dir=0;}
		if(PWM_val==0)dir=1;	   					 
		TIM_SetCompare1(TIM1,PWM_val);	   
	} 
	
}


