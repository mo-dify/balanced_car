#include "stm32f10x.h"
#include "timer2.h"
#include "timer.h"
#include "led.h"
#include	"usart1.h"
#include "usart2.h"
#include "usart3.h"



int main()
{
	//��ʼ��led
	led_init();
	//���ʻ�����1��
	usart_init1();
	//��ʼ����ʱ��2
	timer2_init();
	//��ʼ����ʱʱ��3
	timer3_init(1000);
	//��ʼ������2��3
	usart_init2();
	Uart3_Init(115200);
	//�����ж�
	NVIC_Configuration1();
	delay1();
	reset_bit();
	//��dp_ch�˿ڸߵ�ƽ������ģ��
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	delay1();
	//��ʼ��wifiģ�顢����server����
	wifi_init();
	while(1)
	{	
		//ǰ��
		if(flag_w)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
		//����
		if(flag_s)
		{
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
		//˳ʱ����ת
		if(flag_a)
		{
			
			GPIO_SetBits(GPIOB,GPIO_Pin_7);
			GPIO_ResetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
		//��ʱ����ת
		if(flag_d)
		{
			GPIO_ResetBits(GPIOB,GPIO_Pin_7);
			GPIO_SetBits(GPIOB,GPIO_Pin_13);
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			TIM2->CCR1=30000;
			TIM2->CCR1=30000;
			TIM2->CCR2=30000;
		}
	
	}
}
