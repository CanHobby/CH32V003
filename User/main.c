/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 External interrupt line routine:
 EXTI_Line0(PD0)
 PD0 sets the pull-up input, and the falling edge triggers the interrupt.

*/

#include "debug.h"

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */

int main(void)
{
	int q = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("\nEXTI Test -- SystemClk = %d MHz\r\n", SystemCoreClock / 1000000 );

    printf("\nEXTI D4 IRQ Test\r\n");

    CHobby_EXTI_INIT( 3 );  //  4 = D4 and Reset Enabled  --  -4 = D4 only
    						//  only D2, D3 and D4 supported for now

    Delay_Ms( 2000 );

    while(1)
    {
        Delay_Ms( 2000 );
        printf("Loop cnt = %d\r\n", q++ );
    }
}



