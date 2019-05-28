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
//#include "GUIDemo.h"
#include "PWMControlDLG.h"
#include "WM.h"
#include "DIALOG.h"
#include "ppower.h"

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



u16 _setV=600,_setC=1000,_setFQ=10,_setDC=50;//设置电压、电流、频率、占空比的默认值，初始值
extern u16 setV,setC,rtV,rtC;//电压、电流的设置值，当前实际值；
extern u16  PWM_DC;//占空比
extern u16 PWM_fq;	//频率
extern char uimessage[50];
extern char * uimsg;
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
	CreateUI(); 
} 
int main(void)
{	
	u16 i;
	//赋值为初始值
	setV=_setV;
	setC=_setC;
	PWM_fq=_setFQ;
	PWM_DC=_setDC;
	delay_init();	    	//延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(72,4800);  //串口初始化 
 	//LED_Init();			    //LED端口初始化
	TFTLCD_Init();			//LCD初始化	
	KEY_Init();	 			//按键初始化
 	TP_Init();				//触摸屏初始化
	
	// TIM1_PWM_Init_Reg(899,0);//不分频。PWM频率=72000/(899+1)=80Khz 
	// TIM2_PWM_Init_Reg(899,0);//不分频。PWM频率=72000/(899+1)=80Khz ,调压PWM
	PWM_Init_fq(_setFQ);//初始化频率；
	
	//PWM_SET_DC(_setDC);//初始化占空比；默认开机不启动
	TIM3_Int_Init(999,71);	//1KHZ 定时器1ms ,为STemwin提供时钟
	TIM6_Int_Init(999,719);	//10ms中断,定时调用触摸屏处理函数
	

	mem_init(); 			//初始化内部内存池
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//使能CRC时钟，否则STemWin不能使用 
	WM_SetCreateFlags(WM_CF_MEMDEV);	//?内存管理？
	
	GUI_Init();		//初始化GUI stemWin
	display_UI();	
	power_Init_vc(_setV,_setC);//按默认输出初始化程控电源模块
 
	while(1){
				 if(USART_RX_STA&0x8000)//串口中断接收完毕，处理相关信息；
				{ 
						int m;
					//USART_RX_BUF
					if(USART_RX_BUF[1]=='w'&& USART_RX_BUF[2]=='u'&& USART_RX_BUF[3]=='o')
					{
						uimsg="Set U success!";	//表示设定电压成功						
						RefreshUIMsg();
						query_voltageout();
						
					}else if(USART_RX_BUF[1]=='w'&& USART_RX_BUF[2]=='i'&& USART_RX_BUF[3]=='o')
					{
						uimsg="Set C success!";//表示设定i成功	
						RefreshUIMsg();
						query_Current();	//读一次电压//读一次电流
					
					}else if(USART_RX_BUF[1]=='r'&& USART_RX_BUF[2]=='u')
					{
					//表示read u
						m=(USART_RX_BUF[10]-'0')*1000+(USART_RX_BUF[11]-'0')*100+(USART_RX_BUF[12]-'0')*10+USART_RX_BUF[13]-'0';//计算并转化返回值后4位
						rtV=m;
						uimsg="read U success!";//表示读取电压成功						
						RefreshUIMsg();//刷新UI
						
					}else if(USART_RX_BUF[1]=='r' && USART_RX_BUF[2]=='i')
					{			
						//表示read i	
						m=(USART_RX_BUF[10]-'0')*1000+(USART_RX_BUF[11]-'0')*100+(USART_RX_BUF[12]-'0')*10+USART_RX_BUF[13]-'0';//计算并转化返回值后4位
						rtC=m;
						uimsg="read C success!";//表示读取电流成功						
						RefreshUIMsg();//刷新UI
					}
					USART_RX_STA=0; 
				} 
				i++;
				if(i==250){ query_voltageout();}//轮询电压
				if(i>=500){ query_Current();i=0;}//轮询电流 
				
				GUI_Delay(10); //调用GUI_Delay函数延时10MS(最终目的是调用GUI_Exec()函数)
	
	};
}


