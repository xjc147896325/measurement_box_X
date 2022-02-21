#include "include.h"
/*******************************************************************************
* ��������:  NVIC_Configuration
* ��������: �����ж�Ƕ�����ȼ�
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/

void NVIC_Configuration(void)	//�����ж���Ӧ���ȼ�
{
   	NVIC_InitTypeDef NVIC_InitStructure;                                   //���ýṹ�� 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);                        //ѡ���ж����ȼ����飬�˴�ѡ��0��ʹ0����ռʽ���ȼ���16�������ȼ�
 	//���ж���EXTI1_IRQn
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;                       //�ж���ں���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;              //������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                     //�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //ʹ��ͨ��
	NVIC_Init(&NVIC_InitStructure);                                        //��ʼ���ṹ��   
 	//���ж���EXTI2_IRQn
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;                       //�ж���ں���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;              //������ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                     //�����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //ʹ��ͨ��
	NVIC_Init(&NVIC_InitStructure);                                        //��ʼ���ṹ��   
 	//���ж���EXTI3_IRQn
        NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 	               //��Ӧ��ͨ�����ã��˴�ѡ���ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;              //��ռʽ���ȼ����� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                     //�����ȼ����� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                        //ʹ��ͨ��
	NVIC_Init(&NVIC_InitStructure);                                        //��ʼ���ṹ��   
}


