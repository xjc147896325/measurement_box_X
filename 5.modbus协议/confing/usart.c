#include "include.h"

u8 USART1_RX_BUF[64];  	                                                       //���ջ���,���64���ֽ�
u8 USART1_RX_CNT;                                                              //�����ֽڼ�����
u8 flagFrame = 0;                                                              //֡������ɱ�־�������յ�һ֡������
u8 feedback_data[40]={"�ѽ��յ����ݳ���Ϊ  ��\r\n"};  	                                                       //������Ϣ
unsigned char regGroup[5];  //Modbus�Ĵ����飬��ַΪ0x00��0x04

int fputc(int ch,FILE *f)                         //���printf�������
{
	USART_SendData(USART1,(u8)ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}


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

void usart_Configuration(u32 boot)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);                     //��usart1��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);                       //�򿪸��ù���ʱ��
    GPIO_InitTypeDef GPIO_InitStructure;	                              //����һ��GPIO_InitTypeDef���͵Ľṹ��
    USART_InitTypeDef  USART_InitStructure;                                   //����һ��USART_InitTypeDef���͵Ľṹ��
    NVIC_InitTypeDef NVIC_InitStructure;                                      //����һ��NVIC_InitTypeDef���͵Ľṹ��
    //USART ���Ͷ˿�����
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;                                   //TX�����Ͷ˿�
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;                           //�����ٶ�50MHZ
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;                             //���ù��ܵ��������
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //��ʼ��
    //USART ���ܶ˿�����
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;                                  //RX:���ն�
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;                       //��������ģʽ
    GPIO_Init(GPIOA,&GPIO_InitStructure);                                     //��ʼ��
    //USART1 ��������
    USART_InitStructure.USART_BaudRate=boot;                                  //�����ʵ�����
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;                 //����λΪ8λ
    USART_InitStructure.USART_StopBits=USART_StopBits_1;                      //һλֹͣλ
    USART_InitStructure.USART_Parity=USART_Parity_No;                         //��У��λ
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ��������
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;               //�շ�ģʽ
    USART_Init(USART1,&USART_InitStructure);                                  //��ʼ������
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);                              //�����ж���Ӧ
    USART_Cmd(USART1,ENABLE);                                                 //ʹ�ܴ�������
    USART_ClearFlag(USART1,USART_FLAG_TC);                                    //������ڱ�־λ
    //usart �ж�����
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                           //ѡ���ж����ȼ����飬�˴�ѡ��0��ʹ0����ռʽ���ȼ���16�������ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                         //����USAET1 Ϊ�ж����
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                 //������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                        //�����ȼ�����
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                           //ʹ��ͨ��
    NVIC_Init(&NVIC_InitStructure);                                           //��ʼ���ṹ�� 
}

/*******************************************************************************
* ��������: UartRxMonitor
* ��������: USART1���ڼ�غ���
* ��������: u8 ms  ʱ�������ã�����Ϊ1ms�����ʾһ֡���ݽ������
* ȫ�ֱ���: NONE
* ���ú���: �ڶ�ʱ��2�е��ã�1ms����һ�μ��һ��
* ��    ��: ����ף 
* ��дʱ��: 2014-11-6
* �޸�ʱ��: 
* ��    ��: V1.0 
* ״    ̬:�������
*******************************************************************************/
void Usart1RxMonitor(u8 ms)    
{
    static u8 USART1_RX_BKP = 0;                                               //����USART1_RX_BKP��ʱ�洢���ݳ�����ʵ�ʳ��ȱȽ�
    static u8 idletmr = 0;                                                     //������ʱ��

    if (USART1_RX_CNT > 0)                                                     //���ռ�����������ʱ��������߿���ʱ��
    {
        if (USART1_RX_BKP != USART1_RX_CNT)                                    //���ռ������ı䣬���ս��յ�����ʱ��������м�ʱ
        {
            USART1_RX_BKP = USART1_RX_CNT;                                     //��ֵ��������ʵ�ʳ��ȸ�USART1_RX_BKP
            idletmr = 0;                                                       //�����ʱ������
        }
        else                                                                   //���ռ�����δ�ı䣬�����߿���ʱ���ۻ�����ʱ��
        {
            if (idletmr < 2)                                                   //���м�ʱС��1msʱ�������ۼ�
            {
                idletmr += ms;
                if (idletmr >= 1)                                              //����ʱ��ﵽ1msʱ�����ж�Ϊһ֡�������
                {
                    flagFrame = 1;                                             //����֡������ɱ�־
                }
            }       
        }
    }
    else
    {
        USART1_RX_BKP = 0;
    }
}
/*******************************************************************************
* ��������: UartRead
* ��������: ���㷢�͵����ݳ��ȣ����ҽ����ݴ�ŵ�*buf������
* ��������: u8 *buf ָ������  u8 len ָ������ĳ���
* ȫ�ֱ���: NONE
* ���ú���:  len = UartRead(buf, sizeof(buf));
* ��    ��: ����ף 
* ��дʱ��: 2014-11-6
* �޸�ʱ��: 
* ��    ��: V1.0 
* ״    ̬:�������
*******************************************************************************/

u8 UartRead(u8 *buf, u8 len)
{
    u8  i;
    if (len > USART1_RX_CNT)                                                   //ָ����ȡ���ȴ���ʵ�ʽ��յ������ݳ���ʱ��
    {                                                 
        len = USART1_RX_CNT;                                                   //��ȡ��������Ϊʵ�ʽ��յ������ݳ���
    }
    for (i=0; i<len; i++)                                                      //�������յ������ݵ�����ָ����
    {
        *buf++ = USART1_RX_BUF[i];                                             //�����ݸ��Ƶ�buf��
    }
    USART1_RX_CNT = 0;                                                         //���ռ���������
    return len;                                                                //����ʵ�ʶ�ȡ����
}
/* ���������������������֡�Ľ��գ����ȹ��ܺ�����������ѭ���е��� */
void UartDriver(void)
{ 
    unsigned char i,cnt;
    unsigned int  crc;
    unsigned char crch, crcl;
    static u8 len;
    static u8  buf[60];
   if(flagFrame>0)                                                            //֡������ɱ�־�������յ�һ֡������    
    {
      flagFrame = 0;                                                           //֡������ɱ�־����
      len = UartRead(buf, sizeof(buf));                                        //�����յ��������ȡ����������
      if(buf[0]==0x01)                                                         //�жϵ�ַ�ǲ���01
      {
        crc = GetCRC16(buf, len-2); //����CRCУ��ֵ
        crch = crc >> 8;
        crcl = crc & 0xFF;
          if ((buf[len-2] == crch) && (buf[len-1] == crcl)) //�ж�CRCУ���Ƿ���ȷ
           {
              switch (buf[1]) //��������ִ�в���
              {
                    case 0x03:  //��ȡһ���������ļĴ���
                        if ((buf[2] == 0x00) && (buf[3] <= 0x05)) //�Ĵ�����ַ֧��0x0000��0x0005
                        {
                            if (buf[3] <= 0x04)
                            {
                                i = buf[3];      //��ȡ�Ĵ�����ַ
                                cnt = buf[5];    //��ȡ����ȡ�ļĴ�������
                                buf[2] = cnt*2;  //��ȡ���ݵ��ֽ�����Ϊ�Ĵ�����*2����Modbus����ļĴ���Ϊ16λ
                                len = 3;
                                while (cnt--)
                                {
                                    buf[len++] = 0x00;          //�Ĵ������ֽڲ�0
                                    buf[len++] = regGroup[i++]; //�Ĵ������ֽ�
                                }
                            }
                            else  //��ַ0x05Ϊ������״̬
                            {
                                buf[2] = 2;  //��ȡ���ݵ��ֽ���
                                buf[3] = 0x00;
                                buf[4] = 0;
                                len = 5;
                            }
                            break;
                        }
                        else  //�Ĵ�����ַ����֧��ʱ�����ش�����
                        {
                            buf[1] = 0x83;  //���������λ��1
                            buf[2] = 0x02;  //�����쳣��Ϊ02-��Ч��ַ
                            len = 3;
                            break;
                        }
                    case 0x06:  //д�뵥���Ĵ���
                        if ((buf[2] == 0x00) && (buf[3] <= 0x05)) //�Ĵ�����ַ֧��0x0000��0x0005
                        {
                            if (buf[3] <= 0x04)
                            {
                                i = buf[3];             //��ȡ�Ĵ�����ַ
                                regGroup[i] = buf[5];   //����Ĵ�������
                                cnt = regGroup[i] >> 4; //��ʾ��Һ����
                            }
                            len -= 2; //����-2�����¼���CRC������ԭ֡
                            break;
                        }
                        else  //�Ĵ�����ַ����֧��ʱ�����ش�����
                        {
                            buf[1] = 0x86;  //���������λ��1
                            buf[2] = 0x02;  //�����쳣��Ϊ02-��Ч��ַ
                            len = 3;
                            break;
                        }
                        
                    default:  //������֧�ֵĹ�����
                        buf[1] |= 0x80;  //���������λ��1
                        buf[2] = 0x01;   //�����쳣��Ϊ01-��Ч����
                        len = 3;
                        break;
                        
                        
                        
              }
                crc = GetCRC16(buf, len); //����CRCУ��ֵ
                buf[len++] = crc >> 8;    //CRC���ֽ�
                buf[len++] = crc & 0xFF;  //CRC���ֽ�
                rs485_UartWrite(buf, len);      //������Ӧ֡
             
           }
 
      }
      
      
/*    printf("�ѽ��յ����ݳ���Ϊ:%d\r\n",len);
      Uart_length(feedback_data,len);                                          //���ͽ������ݵĳ���
      LCD_ShowString(20,200,200,12,16,buf);                                    //��buf�е�����д��
      for(i=0;i<=len;i++)                                                      //��buf��������
      {
      buf[i]=' ';
      }
*/      
    }   
}

