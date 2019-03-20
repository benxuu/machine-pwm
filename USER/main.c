#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"	 
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "sram.h"
#include "timer.h"
#include "pwm.h"
#include "malloc.h"
#include "GUI.h"
#include "GUIDemo.h"
#include "FramewinDLG.h"
#include "WM.h"
#include "DIALOG.h"

/************************************************
STemWin PWM 控制系统
开发板：ALIENTEK MIni STM32开发板  V3.3
TIM1：PWM输出，加工脉冲
TIM2：PWM，电压调节
TIM3：为STemwin提供时钟
TIM6：定时调用触摸屏处理函数
IO分配：
PA8：TIM1-CH1输出PWM，红色LED,41#
PA3：TIM2_CH4 PWM,17#,带47K上拉
PA1：ADC123_IN1	，15#，NRF24L01接收
PA4：ADC12_IN4	，20#，NRF24L01接口的CE信号，完全独立
PC4：ADC12_IN14	，24#，NRF24L01接口的Cs信号，完全独立
PD2：指示灯：绿色LED，54#

Author：徐斌 
Email：benxuu@163.com
************************************************/


//UI显示
void display_UI(void)
{
	GUI_CURSOR_Show();
	//更换皮肤
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	CreateFramewin();
//	while(1)
//	{
//		GUI_Delay(100); 
//	}
} 
int main(void)
{	 	
	delay_init();	    	//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(72,9600);  //串口初始化 
 	//LED_Init();			    //LED端口初始化
	TFTLCD_Init();			//LCD初始化	
	KEY_Init();	 			//按键初始化
 	TP_Init();				//触摸屏初始化
	
	//TIM1_PWM_Init(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 
	//TIM2_PWM_Init_Reg(899,0);//不分频。PWM频率=72000/(899+1)=80Khz ,调压PWM
	
	TIM3_Int_Init(999,71);	//1KHZ 定时器1ms ,为STemwin提供时钟
	TIM6_Int_Init(999,719);	//10ms中断,定时调用触摸屏处理函数
	

	mem_init(); 			//初始化内部内存池
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//使能CRC时钟，否则STemWin不能使用 
	WM_SetCreateFlags(WM_CF_MEMDEV);	//?内存管理？
	GUI_Init();		//初始化GUI stemWin
	//GUIDEMO_Main();
	display_UI();

	while(1){
		GUI_Delay(100); //调用GUI_Delay函数延时20MS(最终目的是调用GUI_Exec()函数)
	
	};
}


