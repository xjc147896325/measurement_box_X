#include "include.h"

/*******************************************************************************
* ��������:  usart_Configuration
* ��������:USART1 ���ڵ�����
* ��������: u32 boot  �����ʵ�����
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-11-6
* �޸�ʱ��: 
* ��    ��: V1.0 
* ״    ̬:�������
*******************************************************************************/

void rs485_Configuration(u32 boot)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);                     //��usart1��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                       //�򿪸��ù���ʱ��
    GPIO_InitTypeDef GPIO_InitStructure;	                              //����һ��GPIO_InitTypeDef���͵Ľṹ��
    USART_InitTypeDef  USART_InitStructure;                                   //����һ��USART_InitTypeDef���͵Ľṹ��
    NVIC_InitTypeDef NVIC_InitStructure;                                      //����һ��NVIC_InitTypeDef���͵Ľṹ��
    //CS_485
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    //USART ���Ͷ˿�����
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;                                   //TX�����Ͷ˿�
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;                           //�����ٶ�50MHZ
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;                             //���ù��ܵ��������
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //��ʼ��
    //USART ���ܶ˿�����
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;                                  //RX:���ն�
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;                       //��������ģʽ
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //��ʼ��
    //USART1 ��������
    USART_InitStructure.USART_BaudRate=boot;                                  //�����ʵ�����
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;                 //����λΪ8λ
    USART_InitStructure.USART_StopBits=USART_StopBits_1;                      //һλֹͣλ
    USART_InitStructure.USART_Parity=USART_Parity_No;                         //��У��λ
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ��������
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;               //�շ�ģʽ
    USART_Init(USART2,&USART_InitStructure);                                  //��ʼ������
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);                              //�����ж���Ӧ
    USART_Cmd(USART2,ENABLE);                                                 //ʹ�ܴ�������
    USART_ClearFlag(USART2,USART_FLAG_TC);                                    //������ڱ�־λ
    //usart �ж�����
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                           //ѡ���ж����ȼ����飬�˴�ѡ��0��ʹ0����ռʽ���ȼ���16�������ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;                         //����USAET1 Ϊ�ж����
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;                 //������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                        //�����ȼ�����
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                           //ʹ��ͨ��
    NVIC_Init(&NVIC_InitStructure);                                           //��ʼ���ṹ�� 
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);                                         //�����źţ�ʹ485���ڽ���״̬
}

/*******************************************************************************
* ��������:  rs485_UartWrite
* ��������:485���ڷ��ͺ���
* ��������: u32 boot  �����ʵ�����
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-11-16
* �޸�ʱ��: 
* ��    ��: V1.0 
* ״    ̬:�������
*******************************************************************************/
void rs485_UartWrite(u8 *buf ,u8 len)
{ u8 i=0; 
   GPIO_SetBits(GPIOE,GPIO_Pin_5);                                            //����ģʽ
   delay_ms(3);                                                               //3MS��
    for(i=0;i<=len;i++)
    {
	USART_SendData(USART2,buf[i]);	                                      //ͨ������USARTx���͵�������
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);             //���ָ����USART��־λ������� �������ݼĴ����ձ�־λ
    }
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);                                         //���ý���ģʽ

}
/*******************************************************************************
* ��������:  Uart_length
* ��������: 485���ڷ������ݳ��ȼ��㺯��
* ��������: *buf feedback_data  len ���յ������ݳ���
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-11-16
* �޸�ʱ��: 
* ��    ��: V1.0 
* ״    ̬:�������
*******************************************************************************/
void Uart_length(unsigned char *buf, unsigned char len)
{
                                                                              //�ڽ��յ�������֡����ӻ������з��󷢻�
      feedback_data[18]=0x30+len/10;                                          //�����յ��ֽڸ�λλ����ת��ΪASCII��ʽ
      feedback_data[19]=0x30+len%10;                                          //�����յ��ֽڵ�λ����ת��ΪASCII��ʽ
      rs485_UartWrite(buf, 23);
}

