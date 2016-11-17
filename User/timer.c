#include "stm32f10x.h"
#include "timer.h"
#include "misc.h"
#include "usart2.h"
#include "usart1.h"

uint32_t Timer3_Count = 0;//��¼Timer3�жϴ���
uint16_t Timer3_Frequency;//Timer3�ж�Ƶ��

int flag_1HZ=0;
uint32_t Timer3_Count100Hz = 0;
int flag_100HZ=0;
int delay_count = 0;


//��ʼ��tim3��ʱ��
void timer3_init(uint16_t Handler_Frequency)
{
	//����һ����ʱ���ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	Timer3_Frequency=Handler_Frequency;
		TIM_DeInit(TIM3);
	//���ö�ʱ���ṹ���ʼֵ
	TIM_TimeBaseStructure.TIM_Period=1000*1000/Handler_Frequency;
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	//���ö�ʱ����ʼ������
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//�򿪶�ʱ��
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	//�趨��ʱ���ж�
	TIM_Cmd(TIM3,ENABLE);
	//�򿪶�ʱ���ж�

	//��ʼ���жϽṹ�����
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	//��ʼ���ж�
	NVIC_Init(&NVIC_InitStructure);

}


//��ʱ���жϺ���
void TIM3_IRQHandler(void)//Timer3�ж�
{
	if(TIM3->SR & TIM_IT_Update)//���tim3��ʱ�������ж��Ƿ���
	{     
		TIM3->SR = ~TIM_FLAG_Update;//����жϱ�־
		//delay_count++;
		Timer3_Count++;
		delay_count++;
		if(Timer3_Count == 20)
		{
			USART_SendData(USART2,0x55);
			Timer3_Count=0;
		}
		if(Timer3_Count100Hz++ == 30)
			{
				if(lcs<100)
				{
					flag_w=0;
					flag_s=0;
					flag_a=0;
					flag_d=1;
				}
				else 
				{
					flag_w=1;
					flag_s=0;
					flag_a=0;
					flag_d=0
					;
				}
			Timer3_Count100Hz = 0;
		}
	}
}
//�ӳ�
void ndelay(int ms)
{
	delay_count=0;
	while(delay_count<ms);
}
