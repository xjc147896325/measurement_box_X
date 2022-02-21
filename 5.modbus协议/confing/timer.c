#include "include.h"
/*******************************************************************************
��1��       ����TIM_DeInit()������Timer����ΪĬ��ȱʡֵ��
��2��       TIM_InternalClockConfig()ѡ��TIMx�������ڲ�ʱ��Դ��
��3��       TIM_Perscaler������Ԥ��Ƶϵ����
��4��       TIM_ClockDivision������ʱ�ӷָ
��5��       TIM_CounterMode�����ü�����ģʽ��
��6��       TIM_Period�������Զ�װ���ֵ
��7��       TIM_ARRPerloadConfig()�������Ƿ�ʹ��Ԥװ�ػ�����
��8��       TIM_ITConfig()������TIMx���ж�
*******************************************************************************/
/*******************************************************************************
* ��������:  TIMER_Configuration
* ��������: �������ж�ʱ��������
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIMER_Configuration(void)
{
  //TIM1_Configuration();
  TIM2_Configuration();
  //TIM3_Configuration();
  //TIM4_Configuration();
  //TIM5_Configuration();
  //TIM6_Configuration();
  //TIM7_Configuration();
  //TIM8_Configuration();
}
/*******************************************************************************
* ��������:  TIM1_Configuration
* ��������: ��ʱ��1������Ϊ500ms
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM1_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);             //��APB2TIM1ʱ��
	//��ʱ��TIM2��ʼ��
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=999;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM1,ENABLE);	                                        //ʹ��TIM1
	//�ж����ȼ�NVIC����
        NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;              //TIM1_UP_IRQnΪ�ж˿�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���
}
/*******************************************************************************
* ��������:  TIM2_Configuration
* ��������: ��ʱ��2������Ϊ500ms
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);             //��APB1TIM2ʱ��
	//��ʱ��TIM2��ʼ��
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=1;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM2,ENABLE);	                                        //ʹ��TIMx
	//�ж����ȼ�NVIC����
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                 //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���
}

/*******************************************************************************
* ��������:  TIM3_Configuration
* ��������: ��ʱ��3������Ϊ1S
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM3_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);             //��APB1TIM3ʱ��
	//��ʱ��TIM3��ʼ��
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=1999;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM3,ENABLE);	                                        //ʹ��TIM3
	//�ж����ȼ�NVIC����
        NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                 //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���
}/*******************************************************************************
* ��������:  TIM3_Configuration
* ��������: ��ʱ��3������Ϊ1S
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM4_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);             //��APB1TIM4ʱ��
	//��ʱ��TIM4��ʼ��
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=1999;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM4,ENABLE);	                                        //ʹ��TIM4
	//�ж����ȼ�NVIC����
        NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 //TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���
}
/*******************************************************************************
* ��������:  TIM5_Configuration
* ��������: ��ʱ��5������Ϊ1S
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM5_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);             //��APB1TIM5ʱ��
	//��ʱ��TIM5��ʼ��
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=1999;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM5,ENABLE);	                                        //ʹ��TIM5
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                 //TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�5��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���

}
/*******************************************************************************
* ��������:  TIM6_Configuration
* ��������: ��ʱ��6������Ϊ1S
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-23
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM6_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);             //��APB1TIM6ʱ��
	//��ʱ��TIM5��ʼ��
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=1999;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM6,ENABLE);	                                        //ʹ��TIM6
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;                 //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���

}
/*******************************************************************************
* ��������:  TIM7_Configuration
* ��������: ��ʱ��7������Ϊ1S
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-23
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);             //��APB1TIM6ʱ��
	//��ʱ��TIM5��ʼ��
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=1999;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM7,ENABLE);	                                        //ʹ��TIM6
	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;                 //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���

}
/*******************************************************************************
* ��������:  TIM1_Configuration
* ��������: ��ʱ��1������Ϊ500ms
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void TIM8_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
        NVIC_InitTypeDef NVIC_InitStructure;                            //���ýṹ�� 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);             //��APB2TIM1ʱ��
	//��ʱ��TIM2��ʼ��
	TIM_ClearITPendingBit(TIM8,TIM_IT_Update);                      //��ն�ʱ���ж�
	TIM_TimeBaseStruct.TIM_Period=999;                             //װ��ֵ  ��Χ0����0xffff  65536	һ���Ӽ���2000
	TIM_TimeBaseStruct.TIM_Prescaler=35999;                         //Ԥ��Ƶ 72M/36000=2000
	TIM_TimeBaseStruct.TIM_ClockDivision=0;                         //����ʱ�ӷָ�
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;          //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStruct);	                //��ʼ��
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);                        //�򿪶�ʱ�����ж�  û���������������ж�
	TIM_Cmd(TIM8,ENABLE);	                                        //ʹ��TIM1
	//�ж����ȼ�NVIC����
        NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;              //TIM1_UP_IRQnΪ�ж˿�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;              //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 //��ʼ��NVIC�Ĵ���
}
