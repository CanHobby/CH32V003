
#include "debug.h"

void reset() {  asm(" j 0 " ); }

void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn     CHobby_EXTI_INIT
 *
 * @brief   Initializes EXTI collection including D7 = Reset.
 *
 * @return  none
 */
void CHobby_EXTI_INIT( int16_t pin )
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    EXTI_InitTypeDef EXTI_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    int pp = 0;
    if( (pin>-1) && (pin != 8) ) pp = 0x80;
    pin = abs(pin) & 0x07;
//    EXTI_ClearITPendingBit( 0xFFF );

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD, ENABLE );
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE );

    GPIO_InitStructure.GPIO_Pin = ( 1 << pin ) | pp;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 printf( "pins = 0x%X\n", ( 1 << pin ) | pp );
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, pin );
    if( pp ) {
    	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource7);
    		}
    EXTI_InitStructure.EXTI_Line =( 1 << pin ) | pp;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt ;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    printf( "pinSource = 0x%X\n", pin );
//    printf( "pinLine   = 0x%X\n", ( 1 << pin ) | EXTI_Line7 );
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI7_0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*********************************************************************
 * @fn      EXTI0_IRQHandler
 *
 * @brief   This function handles EXTI0 Handler.
 *
 * @return  none
 */

void EXTI7_0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	  { EXTI_ClearITPendingBit(EXTI_Line2);
	    printf( "IRQ from D2\n"); }  /* Clear Flag */

  if(EXTI_GetITStatus(EXTI_Line3)!=RESET)
	  { EXTI_ClearITPendingBit(EXTI_Line3);
	    printf( "IRQ from D3\n"); }  /* Clear Flag */

  if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	  { EXTI_ClearITPendingBit(EXTI_Line4);
	    printf( "IRQ from D4\n"); }  /* Clear Flag */

  if(EXTI_GetITStatus(EXTI_Line7)!=RESET)
  	  { EXTI_ClearITPendingBit( 0xFFF );   /* Clear All Flag - we are going to Reset */
  	    reset();  }
}
