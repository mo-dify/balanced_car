#include "timer2.h"


//��ʼ��tim2��ʱ��
void timer2_init()
{
	//��tim2��ʱ��
	RCC->APB1ENR |= 0x01;
	//��gpioA��ʱ��
	//RCC->APB2ENR |=	0x5;
	RCC->APB2ENR |= 1<<2;
	
	//reset��8λ
	GPIOA->CRL &=0xffffff00;
	//1010�����������������ٶ�2hz
	GPIOA->CRL |=0xaa;
	//��Ƶ���������
	TIM2->PSC=71;
	//��������
	TIM2->ARR=50000;
	TIM2->CCMR1=0x7070;
	TIM2->CCMR1|=1<<3;
	TIM2->CCMR1|=1<<11;
	TIM2->CR1|=1<<7;
	TIM2->CCER|=0x11;
	TIM2->CR1 |=0x1;

}
