#include "include.h"
void RCC_Configuration(void)
{
  SystemInit();
  RCC_HSE_Configuration();
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE |RCC_APB2Periph_AFIO, ENABLE);

}
/*******************************************************************************
* 函数名称:  RCC_HSE_Configuration
* 函数功能: 设置系统各部分时钟
* 参数变量: NONE
* 全局变量: NONE
* 调用函数:
* 作    者: 董自祝 
* 编写时间: 2014-10-20
* 修改时间: 
* 版    本: V1.0 
* 状    态:调试完成
*******************************************************************************/

void RCC_HSE_Configuration(void) //HSE作为PLL时钟，PLL作为SYSCLK 
{ 
   RCC_DeInit();                                                               /*将外设RCC寄存器重设为缺省值 */ 
   RCC_HSEConfig(RCC_HSE_ON); 	                                               /*设置外部高速晶振（HSE） HSE晶振打开(ON)*/ 
   if(RCC_WaitForHSEStartUp() == SUCCESS) {                                    /*等待HSE起振,  SUCCESS：HSE晶振稳定且就绪*/  
   RCC_HCLKConfig(RCC_SYSCLK_Div1);                                            /*设置AHB时钟(HCLK)RCC_SYSCLK_Div1——AHB时钟 = 系统时*/  
   RCC_PCLK2Config(RCC_HCLK_Div1);                                             /*设置高速AHB时钟(PCLK2)RCC_HCLK_Div1——APB2时钟 = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2);                                             /*设置低速AHB时钟(PCLK1)RCC_HCLK_Div2——APB1时钟 = HCLK / 2*/      
   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);                        /*设置PLL时钟源及倍频系数*/    
   RCC_PLLCmd(ENABLE); 	                                                       /*使能PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ;                        /*检查指定的RCC标志位(PLL准备好标志)设置与否*/     
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                                  /*设置系统时钟（SYSCLK） */  
   while(RCC_GetSYSCLKSource() != 0x08);                                       /*0x08：PLL作为系统时钟 */	    
 } 
} 
  
 /*在STM32中有5个时钟源：
①、HSI是高速内部时钟，RC震荡器，频率为 8MHz。
②、HSE是高速外部时钟，可接石英/陶瓷谐振器，或者接外部时钟源，频率范围为4MHz~16MHz。
③、LSI是低速内部时钟，RC振荡器，频率为40kHz。
④、LSE是低速外部时钟，接频率为32.768kHz的石英晶体。
⑤、PLL为锁相环倍频输出，其时钟输入源可选择为HIS/2、HSE或HSE/2。倍频可选择为2~16倍，但其输出频率最大不得超过72MHz。
系统时钟SYSCLK，它是供STM32中绝大部分器件工作的时钟源，系统时钟可选择为PLL输出、HSI或者HSE。系统时钟的做大频率为72MHz，
它通过AHB分频器分频后送给个模块使用，AHB分频器可选择1、2、4、8、16、32、64、128、256、512分频。AHB分频器输出的时钟送给5大模块使用：
1.       送给AHB总线、内核、内存和DMA使用的HCLK时钟。
2.       通过8分频后送给Cortex的系统定时器时钟。
3.       直接送给Cortex的空闲运行时钟PCLK。
4.       送给APB1分频器。APB1分频器可选择1、2、4、8、16分频，其输出一路供APB1外设使用（PCLK1，最大频率36MHz），
另一路送给定时器（Timer）2、3、4倍频器使用。该倍频器可选择1或者2倍频，时钟输出供定时器2、3、4使用。
5.       送给APB2分频器。APB2分频器可选择1、2、4、8、16分频，其输出一路供APB2外设使用(PCLK2，最大频率72MHz)，
另一路送给定时器(Timer)1倍频器使用。该倍频器可选择1或者2倍频，时钟输出供定时器1使用。另外，APB2分频器还有一路输出供ADC分频器使用，分频后送给ADC模块使用。ADC分频器可选择为2、4、6、8分频。
连接在APB1（低速外设）上的设备有：电源接口、备份接口、CAN、USB、I2C1、I2C2、UART2、UART3、SPI2、窗口看门狗、Timer2、Timer3、Timer4。
连接在APB2（高速外设）上的设备有：UART1、SPI1、Timer1、ADC1、ADC2、所有普通IO口、第二功能IO口。*/  

