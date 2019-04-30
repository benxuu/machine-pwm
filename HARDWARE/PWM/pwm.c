#include "pwm.h"
#include "led.h"
#include "delay.h"
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////
//ALIENTEK Mini STM32开发板
//PWM  驱动代码			   
//优先使用寄存器驱动，TIM1_PWM_Init_Reg；输出口PA8
//TIM2_PWM_Init_Reg；输出PA9
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


//PWM输出初始化
//arr：自动重装值，psc=0，PWM频率=72000/(arr+1)=80Khz
//psc：时钟预分频数
u8  PWM_DC;// 占空比
u16 PWM_fq;	// 频率
u16 PWM_arr=899;	// 自动重装值，psc=0，PWM频率=72000/(arr+1)=80Khz
u16 PWM_val=0;//time1定时器值，占空比细调

//TIM1_CH1 PWM输出初始化，PA8输出；PWM2模式，负脉冲
//arr：自动重装值
//psc：时钟预分频数
//相关寄存器使用说明，ARR：设定自动重装值；PSC：设置预分频器，0,不分频；CR1
void TIM1_PWM_Init_Reg(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<11; 	//TIM1时钟使能    
	GPIOA->CRH&=0XFFFFFFF0;	//PA8清除之前的设置
	GPIOA->CRH|=0X0000000B;	//复用功能输出 
	
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器设置
  
	TIM1->CCMR1|=7<<4;  	//即修改OC1M为111，CH1 PWM2模式；110/111两种PWM，6<<4时PWM输出极性相反；
	TIM1->CCMR1|=1<<3; 		//CH1预装载使能	 
 	TIM1->CCER|=1<<0;   	//OC1 输出使能，CCER寄存器0位为CC1E，1表示输出。0为输入	   
	TIM1->BDTR|=1<<15;   	//MOE 主输出使能	 ，高级定时器需配，普通定时器无此项  

	TIM1->CR1=0x0080;   	//ARPE使能，开启TIM1时钟 
	TIM1->CR1|=0x01;    	//使能定时器1 
	TIM1->CCR1=0x0000;		//CCR1寄存器值与CNT值相比较，控制输出脉宽。此处初始化为0
}  


//TIM1_CH1 PWM输出初始化，PA8输出；PWM1模式，正脉冲
//arr：自动重装值
//psc：时钟预分频数
//相关寄存器使用说明，ARR：设定自动重装值；PSC：设置预分频器，0,不分频；CR1
void TIM1_PWM1_Init(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB2ENR|=1<<11; 	//TIM1时钟使能    
	GPIOA->CRH&=0XFFFFFFF0;	//PA8清除之前的设置
	GPIOA->CRH|=0X0000000B;	//复用功能输出 
	
	TIM1->ARR=arr;			//设定计数器自动重装值 
	TIM1->PSC=psc;			//预分频器设置
  
	TIM1->CCMR1|=6<<4;  	//即修改OC1M为111，CH1 PWM2模式；110/111两种PWM，6<<4时PWM输出极性相反；
	TIM1->CCMR1|=1<<3; 		//CH1预装载使能	 
 	TIM1->CCER|=1<<0;   	//OC1 输出使能，CCER寄存器0位为CC1E，1表示输出。0为输入	   
	TIM1->BDTR|=1<<15;   	//MOE 主输出使能	 ，高级定时器需配，普通定时器无此项  

	TIM1->CR1=0x0080;   	//ARPE使能，开启TIM1时钟 
	TIM1->CR1|=0x01;    	//使能定时器1 
	TIM1->CCR1=0x0000;		//CCR1寄存器值与CNT值相比较，控制输出脉宽。此处初始化为0
} 


//TIM2_CH4 PWM输出初始化，使用PA3口输出
//arr：自动重装值
//psc：时钟预分频数
//相关寄存器使用说明，ARR：设定自动重装值；PSC：设置预分频器，0,不分频；CR1
void TIM2_PWM_Init_Reg(u16 arr,u16 psc)
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<0; 	//TIM2时钟使能，普通定时器，最大频率36M    
	GPIOA->CRL&=0XFFFF0FFF;	//PA3清除之前的设置
	GPIOA->CRL|=0X0000B000;	//复用功能输出 10：复用功能推挽输出模式，11：输出模式，最大速度50MHz
	
	TIM2->ARR=arr;			//设定计数器自动重装值 
	TIM2->PSC=psc;			//预分频器设置
  
	TIM2->CCMR1|=7<<4;  	//即修改OC1M为111，CH1 PWM2模式；110/111两种PWM，6<<4时PWM输出极性相反；
	TIM2->CCMR1|=1<<3; 		//CH1预装载使能	 
 	TIM2->CCER|=1<<0;   	//OC1 输出使能，CCER寄存器0位为CC1E，1表示输出。0为输入	   
	//TIM1->BDTR|=1<<15;   	//MOE 主输出使能	 ，高级定时器需配，普通定时器无此项  

	TIM2->CR1=0x0080;   	//ARPE使能，开启TIM1时钟 
	TIM2->CR1|=0x01;    	//使能定时器1 
	TIM2->CCR1=0x0000;		//CCR1寄存器值与CNT值相比较，控制输出脉宽。此处初始化为0
}  

void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
	PWM_val=0;
	TIM_SetCompare1(TIM1,PWM_val);//默认PWM输出为0；
 
   
}

//根据预设频率初始化PWM,单位KHZ；不分频。PWM频率=72000/(arr+1)=80Khz
void PWM_Init_fq(u16 fq){	
	PWM_arr=72000/fq-1;
	PWM_fq=fq; 
	TIM1_PWM_Init_Reg(PWM_arr,0);
	//TIM1_PWM_Init(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 
}
	
void PWM_disable(){
	TIM_SetCompare1(TIM1,0);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, DISABLE);// 关闭定时器1时钟
	TIM_CtrlPWMOutputs(TIM1,DISABLE);	//MOE 主输出使能	 
	TIM_Cmd(TIM1, DISABLE);  //禁用TIM1	
	//GPIOA->BRR=GPIO_Pin_8;//输出高电平，BSRR输出0  
}

void PWM_enable(){
TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}

//设置PWM占空比0-100
void PWM_SET_DC(u8 dutyCycle){	
	PWM_val=(PWM_arr+1)*dutyCycle/100;
	PWM_DC=dutyCycle;
	TIM1->CCR1=PWM_val;	
	//TIM_SetCompare1(TIM1,PWM_val);
}

//设置PWM占空值
void PWM_SET_val(u16 val){
	TIM1->CCR1=val;	
//	PWM_val=val;	
//	TIM_SetCompare1(TIM1,val);
}

//上调PWM占空值
void PWM_up(u16 val){
	TIM1->CCR1+=val;

}
//下调PWM占空值
void PWM_down(u16 val){	
	if(TIM1->CCR1<val){TIM1->CCR1=0;}
	else TIM1->CCR1-=val;

}

//pwm演示，led0亮度自动变化
void PWM_demo(){	   
	u8 dir=1;	
	u16 val=0;
	u16 i=600;
	TIM1_PWM_Init_Reg(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 
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


