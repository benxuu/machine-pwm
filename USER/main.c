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
#include "PWMControlDLG.h"
#include "WM.h"
#include "DIALOG.h"
#include "ppower.h"

/************************************************
STemWin PWM ����ϵͳ
�����壺ALIENTEK MIni STM32������  V3.3
TIM1��PWM������ӹ�����
TIM2��PWM����ѹ����
TIM3��ΪSTemwin�ṩʱ��
TIM6����ʱ���ô�����������
IO���䣺
PA8��TIM1-CH1���PWM����ɫLED,41#
PA3��TIM2_CH4 PWM,17#,��47K����
PA1��ADC123_IN1	��15#��NRF24L01����
PA4��ADC12_IN4	��20#��NRF24L01�ӿڵ�CE�źţ���ȫ����
PC4��ADC12_IN14	��24#��NRF24L01�ӿڵ�Cs�źţ���ȫ����
PD2��ָʾ�ƣ���ɫLED��54#

Author����� 
Email��benxuu@163.com
************************************************/


extern u16 Out_Voltage;
extern u16 Out_Current;
extern int  rtV;
extern int  rtI;

//UI��ʾ
void display_UI(void)
{
	GUI_CURSOR_Show();
	//����Ƥ��
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
	
//	 hWin=CreatePWMControl();
//  hNumPad = GUI_CreateDialogBox(_aDialogNumPad,
//                                GUI_COUNTOF(_aDialogNumPad),
//                                _cbDialogNumPad, WM_HBKWIN, 300, 200); /* Create the numpad dialog */
// WM_HideWindow(hNumPad);
	//CreateFramewin();
//	while(1)
//	{
//		GUI_Delay(100); 
//	}
} 
int main(void)
{	
	u8 t; u8 len; 	
	delay_init();	    	//��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(72,4800);  //���ڳ�ʼ�� 
 	//LED_Init();			    //LED�˿ڳ�ʼ��
	TFTLCD_Init();			//LCD��ʼ��	
	KEY_Init();	 			//������ʼ��
 	TP_Init();				//��������ʼ��
	
	//TIM1_PWM_Init(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz 
	//TIM2_PWM_Init_Reg(899,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz ,��ѹPWM
	
	TIM3_Int_Init(999,71);	//1KHZ ��ʱ��1ms ,ΪSTemwin�ṩʱ��
	TIM6_Int_Init(999,719);	//10ms�ж�,��ʱ���ô�����������
	

	mem_init(); 			//��ʼ���ڲ��ڴ��
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);//ʹ��CRCʱ�ӣ�����STemWin����ʹ�� 
	WM_SetCreateFlags(WM_CF_MEMDEV);	//?�ڴ����
	
	GUI_Init();		//��ʼ��GUI stemWin
	display_UI();
	
	setSet_Currentout(1231);
	delay_ms(2000);	
	setSet_voltageout(3432);
 
	while(1){

				 if(USART_RX_STA&0x8000)
				{ 
					//	len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
						//printf("\r\n �����͵���ϢΪ:\r\n");
						int m;
			//USART_RX_BUF
					if(USART_RX_BUF[1]=='w'&& USART_RX_BUF[2]=='u')
						{
							//message="dian ya shen";
					//��ʾ�趨��ѹ�ɹ�
					}else if(USART_RX_BUF[1]=='w'&& USART_RX_BUF[2]=='i')
					{
		//��ʾ�趨i�ɹ�
					
					}else if(USART_RX_BUF[1]=='r'&& USART_RX_BUF[2]=='u')
					{
					//��ʾread u
						m=(USART_RX_BUF[10]-'0')*1000+(USART_RX_BUF[11]-'0')*100+(USART_RX_BUF[12]-'0')*10+USART_RX_BUF[13]-'0';//���㲢ת������ֵ��4λ
						Out_Voltage=m;
					}else if(USART_RX_BUF[1]=='r'&& USART_RX_BUF[2]=='i')
					{			
						//��ʾread i
		//				buffer4 =strncpy(*USART_RX_BUF,10,4);
						//Out_Current=atoi(buffer4);
						m=(USART_RX_BUF[10]-'0')*1000+(USART_RX_BUF[11]-'0')*100+(USART_RX_BUF[12]-'0')*10+USART_RX_BUF[13]-'0';//���㲢ת������ֵ��4λ
						Out_Current=m;
					}
					
					
//						for(t=0;t<len;t++)
//						{
//							USART1->DR=USART_RX_BUF[t];
//							while((USART1->SR&0X40)==0);//�ȴ����ͽ���
//						}
					//printf("\r\n\r\n");//���뻻��
					USART_RX_STA=0;
				} 
		GUI_Delay(20); //����GUI_Delay������ʱ20MS(����Ŀ���ǵ���GUI_Exec()����)
	
	};
}


