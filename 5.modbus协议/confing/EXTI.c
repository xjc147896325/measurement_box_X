#include "include.h"
/***************************************************************************************/

/*�Ķ�exti���ⲿ�豸�жϺ���
�ҵ���⡪���ⲿ�豸ͨ�����Ÿ�����Ӳ���жϣ�Ҳ���Բ�������жϣ�19���������½��򶼴�����EXTI0��EXTI15���ӵ��ܽţ�
EXTI��16���ӵ�PVD��VDD���ӣ���EXTI��17���ӵ�RTC�����ӣ���EXTI��18���ӵ�USB�����ѣ���
����Ӧ��1���趨�ⲿ�жϳ�ʼ�������������󣬲��Ǳ�����롣*/
/***************************************************************************************/

void EXTI_Configuration(void)	                                   
{
    EXTI_InitTypeDef EXTI_InitStructure;                                     //�ṹ��
    /*----�����ⲿ�ж�Դ�������ж�Դ��GPIO������-----*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);              //  ѡ���ⲿ�ж���Ϊ������  ӳ�䵽PC1�ⲿ�ж�����
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource2);              //  ѡ���ⲿ�ж���Ϊ������  ӳ�䵽PC2�ⲿ�ж�����
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource3);              //  ѡ���ⲿ�ж���Ϊ������  ӳ�䵽PC3�ⲿ�ж�����
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);              //  ѡ���ⲿ�ж���Ϊ������  ӳ�䵽PC5�ⲿ�ж�����
    
    EXTI_ClearITPendingBit(EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line5);     //��� EXTI ��·����λ 
    EXTI_InitStructure.EXTI_Line=EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line5;//ѡ���ж���                             //ѡ���ж���
    EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	                     //����Ϊ�жϷ�ʽ
    EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;                    //�½��ش�����ʽ
    EXTI_InitStructure.EXTI_LineCmd=ENABLE;			             // ʹ��
    EXTI_Init(&EXTI_InitStructure);			                     //��ʼ���ṹ��
}
/****************************************************************************
* ��    �ƣ�void EXTI9_5_IRQHandler(void)
* ��    �ܣ�EXTI9-5�жϴ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5)==SET)                                      //�Ƿ�����ж�
  {
   	EXTI_ClearITPendingBit(EXTI_Line5);	                             //����ж�EXTI_Line5
	delay_ms(10);                                                        //������ 
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==Bit_RESET)               //�жϰ���������Ƿ�Ϊ�͵�ƽ
	{
            if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //��ȡ����ڵĸߵ͵�ƽ
            {
               GPIO_SetBits(GPIOB,GPIO_Pin_5);	
            }
            else
            {
                GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            }
	}
  }	
}
/****************************************************************************
* ��    �ƣ�void EXTI1_IRQHandler(void)
* ��    �ܣ�EXTI1�жϴ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1)==SET)                                      //�Ƿ�����ж�
  {
   	EXTI_ClearITPendingBit(EXTI_Line1);	                             //����ж�EXTI_Line5
	delay_ms(10);                                                        //������ 
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)==Bit_RESET)               //�жϰ���������Ƿ�Ϊ�͵�ƽ
	{
            if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //��ȡ����ڵĸߵ͵�ƽ
            {
               GPIO_SetBits(GPIOB,GPIO_Pin_5);	
            }
            else
            {
                GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            }
	}
  }	
}

/****************************************************************************
* ��    �ƣ�void EXTI1_IRQHandler(void)
* ��    �ܣ�EXTI2�жϴ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2)==SET)                                      //�Ƿ�����ж�
  {
   	EXTI_ClearITPendingBit(EXTI_Line2);	                             //����ж�EXTI_Line5
	delay_ms(10);                                                        //������ 
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)==Bit_RESET)               //�жϰ���������Ƿ�Ϊ�͵�ƽ
	{
            if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)==Bit_RESET)          //��ȡ����ڵĸߵ͵�ƽ
            {
               GPIO_SetBits(GPIOB,GPIO_Pin_5);	
            }
            else
            {
                GPIO_ResetBits(GPIOB,GPIO_Pin_5);
            }
	}
  }	
}

