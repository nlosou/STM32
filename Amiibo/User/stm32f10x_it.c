/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "middleware/sw_uart.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

static inline void sw_uart_tick(void)
{
    CLEAR_TIM2_UIF();
    CLEAR_TIM2_CNT();
    sw_uart_recieve_state = Wait_start_bit;
    TIMER_SET_TIM2_ARR(52);
    OPEN_TIM2();
}

static inline void sw_uart_rx_process(void)
{
    if(sw_uart_recieve_state == Wait_start_bit)
    {
        get_pin_level = STM32_FAST_GET_GPIOA_PIN_LEVEL(1<<2);
        if(get_pin_level)
        {
            sw_uart_recieve_state = Idel;
            CLOSE_TIM2();
            CLEAR_EXTI_PR(0x01 << 2);   
            OPEN_EXTIx(1<<2);
        }
        else
        {
            CLOSE_EXTIx(1<<2);
            CLEAR_EXTI_PR(0x01 << 2);   
            TIMER_SET_TIM2_ARR(104);
            CLEAR_TIM2_CNT();
            sw_uart_recieve_state = Sampling;
        }
    }
    else if(sw_uart_recieve_state == Sampling)
    {
        get_pin_level = STM32_FAST_GET_GPIOA_PIN_LEVEL(1<<2);
        
        uart_receive_data|=get_pin_level << (bit_idx++);
        if(bit_idx>7)
        {
            bit_idx = 0;
            CLOSE_TIM2();
            OPEN_EXTIx(1<<2);
            sw_uart_recieve_state = Completed;
            fetch_complete = 1;
        }
    }
}

void EXTI0_IRQHandler(void)
{
    //OLED_ShowString(0,0,"hello");
    CLEAR_EXTI_PR(0x01); 
}
//uart的rx接收数据 
void EXTI2_IRQHandler(void)//下降沿触发
{
    sw_uart_tick();
    CLOSE_EXTIx(1<<2);
    CLEAR_EXTI_PR(0x01 << 2);   
}

//Uart的RX
void TIM2_IRQHandler(void)
{
   CLEAR_TIM2_UIF();
   sw_uart_rx_process();
}

//Uart的TX
void TIM3_IRQHandler(void)
{
   CLEAR_TIM3_UIF();
   if(Uart_tx_idx>9)
   {
       Uart_tx_busy = 0;
       CLOSE_TIM3();
   }
   if(Uart_tx_busy)
   {
        if(TX_tmep_bit[Uart_tx_idx++])
        {
            STM32_FAST_SET_GPIOA_PIN_HIGH(1<<0);
        }
        else
        {

            STM32_FAST_SET_GPIOA_PIN_LOW(1<<0);
        }
   }
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
