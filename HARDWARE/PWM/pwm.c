#include "pwm.h"
#include "led.h"
#include "delay.h"
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////
//ALIENTEK Mini STM32������
//PWM  ��������			   
//����ʹ�üĴ���������TIM1_PWM_Init_Reg�������PA8
//TIM2_PWM_Init_Reg�����PA9
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWM�����ʼ��
//arr���Զ���װֵ��psc=0��PWMƵ��=72000/(arr+1)=80Khz
//psc��ʱ��Ԥ��Ƶ��
u8  PWM_DC;// ռ�ձ�
u16 PWM_fq;	// Ƶ��
u16 PWM_arr=899;	// �Զ���װֵ��psc=0��PWMƵ��=72000/(arr+1)=80Khz
u16 PWM_val=0;//time1��ʱ��ֵ��ռ�ձ�ϸ��

//TIM1_CH1 PWM�����ʼ����PA8�����PWM2ģʽ��������
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//��ؼĴ���ʹ��˵����ARR���趨�Զ���װֵ��PSC������Ԥ��Ƶ����0,����Ƶ��CR1
void TIM1_PWM_Init_Reg(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��    
	GPIOA->CRH&=0XFFFFFFF0;	//PA8���֮ǰ������
	GPIOA->CRH|=0X0000000B;	//���ù������ 
	
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
  
	TIM1->CCMR1|=7<<4;  	//���޸�OC1MΪ111��CH1 PWM2ģʽ��110/111����PWM��6<<4ʱPWM��������෴��
	TIM1->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM1->CCER|=1<<0;   	//OC1 ���ʹ�ܣ�CCER�Ĵ���0λΪCC1E��1��ʾ�����0Ϊ����	   
	TIM1->BDTR|=1<<15;   	//MOE �����ʹ��	 ���߼���ʱ�����䣬��ͨ��ʱ���޴���  

	TIM1->CR1=0x0080;   	//ARPEʹ�ܣ�����TIM1ʱ�� 
	TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 
	TIM1->CCR1=0x0000;		//CCR1�Ĵ���ֵ��CNTֵ��Ƚϣ�������������˴���ʼ��Ϊ0
}  


//TIM1_CH1 PWM�����ʼ����PA8�����PWM1ģʽ��������
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//��ؼĴ���ʹ��˵����ARR���趨�Զ���װֵ��PSC������Ԥ��Ƶ����0,����Ƶ��CR1
void TIM1_PWM1_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB2ENR|=1<<11; 	//TIM1ʱ��ʹ��    
	GPIOA->CRH&=0XFFFFFFF0;	//PA8���֮ǰ������
	GPIOA->CRH|=0X0000000B;	//���ù������ 
	
	TIM1->ARR=arr;			//�趨�������Զ���װֵ 
	TIM1->PSC=psc;			//Ԥ��Ƶ������
  
	TIM1->CCMR1|=6<<4;  	//���޸�OC1MΪ111��CH1 PWM2ģʽ��110/111����PWM��6<<4ʱPWM��������෴��
	TIM1->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM1->CCER|=1<<0;   	//OC1 ���ʹ�ܣ�CCER�Ĵ���0λΪCC1E��1��ʾ�����0Ϊ����	   
	TIM1->BDTR|=1<<15;   	//MOE �����ʹ��	 ���߼���ʱ�����䣬��ͨ��ʱ���޴���  

	TIM1->CR1=0x0080;   	//ARPEʹ�ܣ�����TIM1ʱ�� 
	TIM1->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 
	TIM1->CCR1=0x0000;		//CCR1�Ĵ���ֵ��CNTֵ��Ƚϣ�������������˴���ʼ��Ϊ0
} 


//TIM2_CH4 PWM�����ʼ����ʹ��PA3�����
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//��ؼĴ���ʹ��˵����ARR���趨�Զ���װֵ��PSC������Ԥ��Ƶ����0,����Ƶ��CR1
void TIM2_PWM_Init_Reg(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<0; 	//TIM2ʱ��ʹ�ܣ���ͨ��ʱ�������Ƶ��36M    
	GPIOA->CRL&=0XFFFF0FFF;	//PA3���֮ǰ������
	GPIOA->CRL|=0X0000B000;	//���ù������ 10�����ù����������ģʽ��11�����ģʽ������ٶ�50MHz
	
	TIM2->ARR=arr;			//�趨�������Զ���װֵ 
	TIM2->PSC=psc;			//Ԥ��Ƶ������
  
	TIM2->CCMR1|=7<<4;  	//���޸�OC1MΪ111��CH1 PWM2ģʽ��110/111����PWM��6<<4ʱPWM��������෴��
	TIM2->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	 
 	TIM2->CCER|=1<<0;   	//OC1 ���ʹ�ܣ�CCER�Ĵ���0λΪCC1E��1��ʾ�����0Ϊ����	   
	//TIM1->BDTR|=1<<15;   	//MOE �����ʹ��	 ���߼���ʱ�����䣬��ͨ��ʱ���޴���  

	TIM2->CR1=0x0080;   	//ARPEʹ�ܣ�����TIM1ʱ�� 
	TIM2->CR1|=0x01;    	//ʹ�ܶ�ʱ��1 
	TIM2->CCR1=0x0000;		//CCR1�Ĵ���ֵ��CNTֵ��Ƚϣ�������������˴���ʼ��Ϊ0
}  

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
	TIM1_PWM_Init_Reg(PWM_arr,0);
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

//����PWMռ�ձ�0-100
void PWM_SET_DC(u8 dutyCycle){	
	PWM_val=(PWM_arr+1)*dutyCycle/100;
	PWM_DC=dutyCycle;
	TIM1->CCR1=PWM_val;	
	//TIM_SetCompare1(TIM1,PWM_val);
}

//����PWMռ��ֵ
void PWM_SET_val(u16 val){
	TIM1->CCR1=val;	
//	PWM_val=val;	
//	TIM_SetCompare1(TIM1,val);
}

//�ϵ�PWMռ��ֵ
void PWM_up(u16 val){
	TIM1->CCR1+=val;

}
//�µ�PWMռ��ֵ
void PWM_down(u16 val){	
	if(TIM1->CCR1<val){TIM1->CCR1=0;}
	else TIM1->CCR1-=val;

}

//pwm��ʾ��led0�����Զ��仯
void PWM_demo(){	   
	u8 dir=1;	
	u16 val=0;
	u16 i=600;
	TIM1_PWM_Init_Reg(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
   	while(i)
	{		
		i--;
 		delay_ms(10);	 
		if(dir)val++;
		else val--;	 
 		if(val>300){dir=0;}
		if(val==0)dir=1;	   					 
		TIM1->CCR1=val;	   
	} 
	
}


