#include "include.h"
/*******************************************************************************
* ��������:  GPIO_Configuration
* ��������: ����gpio�ڵĲ���
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-17
* �޸�ʱ��: 
* ��    ��: V0.0 
* ״    ̬:�������
*******************************************************************************/
void GPIO_Configuration(void)//Config(����)
{		
        /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
        GPIO_InitTypeDef GPIO_InitStructure;//�˾�����У�����һ���ṹ��
       /*ѡ��Ҫ���Ƶ�GPIOC����*/															   
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//ѡ������Ҫ�Ŀڣ�����һ�£�	
        /*��������ģʽΪͨ���������*/
        GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //��������ģʽ��
        /* STM32����������ܽ�������8�ֿ��ܵ����ã���4����+2���+2���������
            �� ��������_GPIO_Mode_IN_FLOATING 
            �� ����������GPIO_Mode_IPU
            �� ����������GPIO_Mode_IPD
            �� ģ������ GPIO_Mode_AIN
            �� ��©��� GPIO_Mode_Out_OD
            �� ������� GPIO_Mode_Out_PP
            �� ���ù��ܵ��������GPIO_Mode_AF_PP 
            �� ���ù��ܵĿ�©��� GPIO_Mode_AF_OD*/                        
        /*������������Ϊ50MHz */   
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                   // ������������Ϊ50MHz 
        GPIO_Init(GPIOB, &GPIO_InitStructure);                              //��ʼ������	  
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_3;		 			
        GPIO_Init(GPIOD, &GPIO_InitStructure);
        GPIO_SetBits(GPIOB, GPIO_Pin_5);                                    //�ϵ縴λ�ߵ�ƽ 
        GPIO_SetBits(GPIOD, GPIO_Pin_3 | GPIO_Pin_6);                       //�ϵ縴λ�ߵ�ƽ 

	/*****************KEYGIOPconfig**********************/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

