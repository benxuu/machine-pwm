#include "adc.h"
#include "delay.h"					   
//////////////////////////////////////////////////////////////////////////////////	 
   
//初始化ADC
//这里我们仅以规则通道为例，
//PA1：ADC123_IN1	
//PA4：ADC12_IN4	
//PC4：ADC12_IN14	
//启用ADC1、2我们默认仅开启通道1																	   
void  Adc1_Init(void)
{    
	//先初始化IO口
 	RCC->APB2ENR|=1<<2;    //使能PORTA口时钟 
	GPIOA->CRL&=0XFFFFFF0F;//PA1 anolog输入
	//通道10/11设置			 
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能	  
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束	    
	RCC->CFGR&=~(3<<14);   //分频因子清零	
	//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式  
	ADC1->CR1&=~(1<<8);    //非扫描模式	  
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //软件控制转换  
	ADC1->CR2|=1<<20;      //使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC1->CR2&=~(1<<11);   //右对齐	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     //1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道1的采样时间
	ADC1->SMPR2&=~(7<<3);  //通道1采样时间清空	  
 	ADC1->SMPR2|=7<<3;     //通道1  239.5周期,提高采样时间可以提高精确度	 
	ADC1->CR2|=1<<0;	   //开启AD转换器	 
	ADC1->CR2|=1<<3;       //使能复位校准  
	while(ADC1->CR2&1<<3); //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        //开启AD校准	   
	while(ADC1->CR2&1<<2);  //等待校准结束
	//该位由软件设置以开始校准，并在校准结束时由硬件清除  
}
//PA4：ADC12_IN4	
//PC4：ADC12_IN14	
//启用ADC1 通道4 PA4
void  Adc1_Init4(void)
{    
	//先初始化IO口
 	RCC->APB2ENR|=1<<2;    //使能PORTA口时钟 
	GPIOA->CRL&=0XFFF0FFFF;//PA4 anolog输入
	//通道10/11设置			 
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能	  
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束	    
	RCC->CFGR&=~(3<<14);   //分频因子清零	
	//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式  
	ADC1->CR1&=~(1<<8);    //非扫描模式	  
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //软件控制转换  
	ADC1->CR2|=1<<20;      //使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC1->CR2&=~(1<<11);   //右对齐	 
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;     //1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道4的采样时间
	ADC1->SMPR2&=~(7<<12);  //通道14采样时间清空	  
 	ADC1->SMPR2|=7<<12;     //通道14  239.5周期,提高采样时间可以提高精确度	 
	ADC1->CR2|=1<<0;	   //开启AD转换器	 
	ADC1->CR2|=1<<3;       //使能复位校准  
	while(ADC1->CR2&1<<3); //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        //开启AD校准	   
	while(ADC1->CR2&1<<2);  //等待校准结束
	//该位由软件设置以开始校准，并在校准结束时由硬件清除  
}

//PC4：ADC12_IN14	
//启用ADC2 通道14 PC4
void  Adc2_Init14(void)
{    
	//先初始化IO口
 	RCC->APB2ENR|=1<<4;    //使能PORTC口时钟 
	GPIOC->CRL&=0XFFF0FFFF;//PC4 anolog输入
	//通道10/11设置			 
	RCC->APB2ENR|=1<<10;    //ADC2时钟使能	  
	RCC->APB2RSTR|=1<<10;   //ADC2复位
	RCC->APB2RSTR&=~(1<<10);//复位结束	    
	RCC->CFGR&=~(3<<14);   //分频因子清零,11	,PCLK2 8分频后作为ADC时钟,所有ADC相同
	//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降! 
	RCC->CFGR|=2<<14;     
	
	ADC2->CR1&=0XF0FFFF;   //工作模式清零
	ADC2->CR1|=0<<16;      //独立工作模式 
	
	ADC2->CR1&=~(1<<8);    //非扫描模式	  
	ADC2->CR2&=~(1<<1);    //单次转换模式，该位由软件设置和清除。如果设置了此位，则转换将连续进行直到该位被清除。0：单次转换模式；1：连续转换模式。
	ADC2->CR2&=~(7<<17);	//选择启动规则通道组转换的外部事件,111：SWSTART 
	
	ADC2->CR2|=7<<17;	   //软件控制转换  
	ADC2->CR2|=1<<20;      //使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC2->CR2&=~(1<<11);   //右对齐	 
	ADC2->SQR1&=~(0XF<<20);
	ADC2->SQR1|=0<<20;     //1个转换在规则序列中 也就是只转换规则序列1 			   
	//设置通道14的采样时间
	ADC2->SMPR1&=~(7<<12);  //通道14采样时间清空	  
 	ADC2->SMPR1|=7<<12;     //通道14  239.5周期,提高采样时间可以提高精确度	 
	
	ADC2->CR2|=1<<0;	   //开启AD转换器	 
	ADC2->CR2|=1<<3;       //使能复位校准  
	while(ADC2->CR2&1<<3); //等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC2->CR2|=1<<2;        //开启AD校准	   
	while(ADC2->CR2&1<<2);  //等待校准结束
	//该位由软件设置以开始校准，并在校准结束时由硬件清除  
}

//获得ADC值
//ch:通道值 0~16
//返回值:转换结果
u16 Get_Adc1(u8 ch)   
{
	//设置转换序列	  		 
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=ch;		  			    
	ADC1->CR2|=1<<22;       //启动规则转换通道 
	while(!(ADC1->SR&1<<1));//等待转换结束	 	   
	return ADC1->DR;		//返回adc值	
}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc1_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc1(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 

//获得ADC值
//ch:通道值 0~16
//返回值:转换结果
u16 Get_Adc1ch4(void)   
{
	//设置转换序列	  		 
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=4;		  			    
	ADC1->CR2|=1<<22;       //启动规则转换通道 
	while(!(ADC1->SR&1<<1));//等待转换结束	 	   
	return ADC1->DR;		//返回adc值	
}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc1ch4_Average(u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc1ch4();
		delay_ms(5);
	}
	return temp_val/times;
} 
	 
//获得ADC值
//ch:通道值 0~16
//返回值:转换结果
u16 Get_Adc2ch14(void)   
{
	//设置转换序列	  		 
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=14;		  			    
	ADC1->CR2|=1<<22;       //启动规则转换通道 
	while(!(ADC1->SR&1<<1));//等待转换结束	 	   
	return ADC1->DR;		//返回adc值	
}
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc2ch14_Average(u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc2ch14();
		delay_ms(5);
	}
	return temp_val/times;
} 
	 
	 









