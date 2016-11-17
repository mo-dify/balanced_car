#include "stm32f10x_conf.h"
#include "usart1.h"
#include "usart3.h"
#define RX_BUFF_SIZE	256
uint8_t USART3_TxCount=0;
uint8_t USART3_Count=0;
static uint8_t USART3_TxBuff[256];	//���ڷ��ͻ�����
uint8_t set_mux[256]="AT+CIPMUX=1\r\n";
uint8_t set_server[256]="AT+CIPSERVER=1,8080\r\n";
//��Ϣ���У���δʵ��
static uint8_t USART3_RxBuff[RX_BUFF_SIZE];
static uint8_t USART3_Rx_wr=0;
static uint8_t USART3_Rx_rd=0;
//��ʼ������3
void Uart3_Init(uint32_t baud)
{
	USART_InitTypeDef USART_init;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
	
	USART_init.USART_BaudRate=baud;
	USART_init.USART_WordLength=USART_WordLength_8b;
	USART_init.USART_StopBits=USART_StopBits_1;
	USART_init.USART_Parity=USART_Parity_No;
	USART_init.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_init.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART3,&USART_init);
	
	//ʹ�ܴ���3�����ж�
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	//ʹ�ܴ���3
	USART_Cmd(USART3,ENABLE);
	//esp8266���ԣ���������ɱ�־λ
	USART_ClearFlag(USART3,USART_FLAG_TC);
}

//����3�жϺ�������ȡ��Ϣ
void USART3_IRQHandler(void)
{
		uint8_t com_data;
	//uart1_putchar('t');
	if(USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)//ORE�ж�
	{
	//	uart1_putchar('g');
		com_data=USART_ReceiveData(USART3);
		uart1_putchar(com_data);
	}
	if(USART3->SR & USART_SR_TC && (USART3->CR1 & USART_CR1_TXEIE) )//�����ж�
	{
		USART3->DR = USART3_TxBuff[USART3_TxCount++];//дDR����жϱ�־          
		if(USART3_TxCount == USART3_Count)
		{
			USART3->CR1 &= ~USART_CR1_TXEIE;//�ر�TXE�ж�
		}
	}
	if(USART3->SR & USART_SR_RXNE)//�����ж�
	{
		
		com_data = USART3->DR;
	//	uart1_putchar('c');
		uart1_putchar(com_data);
		//+IPD,0,1:w
		//���յ������ݱ��浽�ַ�������
		b_check(com_data);
	//	USART3_RxBuff[USART3_Rx_wr++%RX_BUFF_SIZE]=com_data;
		//receive_higt(com_data);
	}
//	USART_ClearITPendingBit(USART1, USART_IT_ORE);//�崮�����ж�
}
//ͨ������3��wifiģ�鷢������
void USART3_PrintHexU8(uint8_t data)
{
	USART3_TxBuff[USART3_Count++] = data;  
	if(!(USART3->CR1 & USART_CR1_TXEIE))
		USART_ITConfig(USART3, USART_IT_TXE, ENABLE); //��TXE�ж�
}
//��ʱ
void send_delay(int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<1000;j++);
}
//��ʼ��wifiģ�顢����sever����
void wifi_init()
{
	int i=0;
	while(set_mux[i])
	{
		USART3_PrintHexU8(set_mux[i]);
		//uart1_putchar(set_mux[i]);
		i++;
	}
	send_delay(1000);
	i=0;
	while(set_server[i])
	{
		USART3_PrintHexU8(set_server[i]);
		i++;
	}
}
//������Ϣ���д�����Ϣ����δʵ��
int USART3_bytes(void)
{
	return USART3_Rx_wr - USART3_Rx_rd;
}
//��ȡ����
uint8_t USART_GdtHexU8()
{
	if(USART3_bytes()==0)
		return 0;
	uart1_putchar(USART3_RxBuff[USART3_Rx_rd%RX_BUFF_SIZE]);
		return USART3_RxBuff[USART3_Rx_rd++%RX_BUFF_SIZE];
}
