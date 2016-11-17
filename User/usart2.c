#include "stm32f10x_conf.h"
#include "misc.h"
#include "usart1.h"

int lcs=101;
static int lh;
static int ll;

//���ô���2�ж�
void NVIC_Configuration2()
{
	NVIC_InitTypeDef NCVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NCVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NCVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NCVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NCVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NCVIC_InitStructure);
}
//��ʼ������
void usart_init2()
{
	GPIO_InitTypeDef GPIO_init;//��ʼ���ṹ��
	USART_InitTypeDef USART_init;
	GPIO_StructInit(&GPIO_init);//���ÿ⺯���Խṹ����г�ʼ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	//�޸Ľṹ��Ĳ�������
	GPIO_init.GPIO_Pin = GPIO_Pin_2;//TX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_AF_PP;
	//���ÿ⺯����ping�̽��г�ʼ��
	GPIO_Init(GPIOA,&GPIO_init);
	
	GPIO_init.GPIO_Pin = GPIO_Pin_3;//RX
	GPIO_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_init);
	USART_StructInit(&USART_init);//���ÿ⺯�����г�ʼ��
	USART_init.USART_BaudRate=9600;
	USART_Init(USART2,&USART_init);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//�����ж�
	USART_Cmd(USART2,ENABLE);//��������
	NVIC_Configuration2();//���ó���ʼ��
}
//ͨ������2��������
void putchar2(unsigned char c)
{
	USART_SendData(USART2,c);
}
//��ʱ
void delay2()
{
	int i,j;
	for(i=0;i<10000;i++)
		for(j=0;j<1000;j++);
}

//����2�жϺ������жϳ�����ģ�鷴��������
void USART2_IRQHandler()
{
	static int flag=0;
	int tmp;
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);
			tmp=USART_ReceiveData(USART2);
			if(flag==0)
			{
				lh=tmp;
				flag=1;
			}
			else
			{
					ll=tmp;
					lcs=ll*256+lh;
					flag=0;
			}
	}	
	USART_ClearITPendingBit(USART2,USART_IT_ORE);
}


