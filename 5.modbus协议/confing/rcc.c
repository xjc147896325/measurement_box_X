#include "include.h"
void RCC_Configuration(void)
{
  SystemInit();
  RCC_HSE_Configuration();
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |RCC_APB2Periph_AFIO, ENABLE);

}
/*******************************************************************************
* ��������:  RCC_HSE_Configuration
* ��������: ����ϵͳ������ʱ��
* ��������: NONE
* ȫ�ֱ���: NONE
* ���ú���:
* ��    ��: ����ף 
* ��дʱ��: 2014-10-20
* �޸�ʱ��: 
* ��    ��: V1.0 
* ״    ̬:�������
*******************************************************************************/

void RCC_HSE_Configuration(void) //HSE��ΪPLLʱ�ӣ�PLL��ΪSYSCLK 
{ 
   RCC_DeInit();                                                               /*������RCC�Ĵ�������Ϊȱʡֵ */ 
   RCC_HSEConfig(RCC_HSE_ON); 	                                               /*�����ⲿ���پ���HSE�� HSE�����(ON)*/ 
   if(RCC_WaitForHSEStartUp() == SUCCESS) {                                    /*�ȴ�HSE����,  SUCCESS��HSE�����ȶ��Ҿ���*/  
   RCC_HCLKConfig(RCC_SYSCLK_Div1);                                            /*����AHBʱ��(HCLK)RCC_SYSCLK_Div1����AHBʱ�� = ϵͳʱ*/  
   RCC_PCLK2Config(RCC_HCLK_Div1);                                             /*���ø���AHBʱ��(PCLK2)RCC_HCLK_Div1����APB2ʱ�� = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2);                                             /*���õ���AHBʱ��(PCLK1)RCC_HCLK_Div2����APB1ʱ�� = HCLK / 2*/      
   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);                        /*����PLLʱ��Դ����Ƶϵ��*/    
   RCC_PLLCmd(ENABLE); 	                                                       /*ʹ��PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ;                        /*���ָ����RCC��־λ(PLL׼���ñ�־)�������*/     
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                                  /*����ϵͳʱ�ӣ�SYSCLK�� */  
   while(RCC_GetSYSCLKSource() != 0x08);                                       /*0x08��PLL��Ϊϵͳʱ�� */	    
 } 
} 
  
 /*��STM32����5��ʱ��Դ��
�١�HSI�Ǹ����ڲ�ʱ�ӣ�RC������Ƶ��Ϊ 8MHz��
�ڡ�HSE�Ǹ����ⲿʱ�ӣ��ɽ�ʯӢ/�մ�г���������߽��ⲿʱ��Դ��Ƶ�ʷ�ΧΪ4MHz~16MHz��
�ۡ�LSI�ǵ����ڲ�ʱ�ӣ�RC������Ƶ��Ϊ40kHz��
�ܡ�LSE�ǵ����ⲿʱ�ӣ���Ƶ��Ϊ32.768kHz��ʯӢ���塣
�ݡ�PLLΪ���໷��Ƶ�������ʱ������Դ��ѡ��ΪHIS/2��HSE��HSE/2����Ƶ��ѡ��Ϊ2~16�����������Ƶ����󲻵ó���72MHz��
ϵͳʱ��SYSCLK�����ǹ�STM32�о��󲿷�����������ʱ��Դ��ϵͳʱ�ӿ�ѡ��ΪPLL�����HSI����HSE��ϵͳʱ�ӵ�����Ƶ��Ϊ72MHz��
��ͨ��AHB��Ƶ����Ƶ���͸���ģ��ʹ�ã�AHB��Ƶ����ѡ��1��2��4��8��16��32��64��128��256��512��Ƶ��AHB��Ƶ�������ʱ���͸�5��ģ��ʹ�ã�
1.       �͸�AHB���ߡ��ںˡ��ڴ��DMAʹ�õ�HCLKʱ�ӡ�
2.       ͨ��8��Ƶ���͸�Cortex��ϵͳ��ʱ��ʱ�ӡ�
3.       ֱ���͸�Cortex�Ŀ�������ʱ��PCLK��
4.       �͸�APB1��Ƶ����APB1��Ƶ����ѡ��1��2��4��8��16��Ƶ�������һ·��APB1����ʹ�ã�PCLK1�����Ƶ��36MHz����
��һ·�͸���ʱ����Timer��2��3��4��Ƶ��ʹ�á��ñ�Ƶ����ѡ��1����2��Ƶ��ʱ���������ʱ��2��3��4ʹ�á�
5.       �͸�APB2��Ƶ����APB2��Ƶ����ѡ��1��2��4��8��16��Ƶ�������һ·��APB2����ʹ��(PCLK2�����Ƶ��72MHz)��
��һ·�͸���ʱ��(Timer)1��Ƶ��ʹ�á��ñ�Ƶ����ѡ��1����2��Ƶ��ʱ���������ʱ��1ʹ�á����⣬APB2��Ƶ������һ·�����ADC��Ƶ��ʹ�ã���Ƶ���͸�ADCģ��ʹ�á�ADC��Ƶ����ѡ��Ϊ2��4��6��8��Ƶ��
������APB1���������裩�ϵ��豸�У���Դ�ӿڡ����ݽӿڡ�CAN��USB��I2C1��I2C2��UART2��UART3��SPI2�����ڿ��Ź���Timer2��Timer3��Timer4��
������APB2���������裩�ϵ��豸�У�UART1��SPI1��Timer1��ADC1��ADC2��������ͨIO�ڡ��ڶ�����IO�ڡ�*/  

