/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "inverter_control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
 * Divide the signal into 6 steps
 * ITR1: U_SW high, U_NSD high, W_SW low, W_NSD low
 * ITR2: W_NSD high, V_NSD low
 * ITR3: U_SW low, U_NSD low, V_SW high, V_NSD high
 * ITR4: U_NSD high, W_NSD low
 * ITR5: V_SW low, V_NSD low, W_SW high, W_NSD high
 * ITR6: U_NSD low, V_NSD high
 */
volatile int period_counter = 0;
int gpio_toggle = 0;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
extern TIM_HandleTypeDef htim8;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USB low priority or CAN_RX0 interrupts.
  */
void USB_LP_CAN_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 0 */

  /* USER CODE END USB_LP_CAN_RX0_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_FS);
  /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 1 */

  /* USER CODE END USB_LP_CAN_RX0_IRQn 1 */
}

/**
  * @brief This function handles TIM8 update interrupt.
  */
void TIM8_UP_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_UP_IRQn 0 */
  
  period_counter %= 6;
  switch(period_counter) 
  {
    case (0):
      HAL_GPIO_WritePin(GPIO_PORT_U_SW, GPIO_PIN_U_SW, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_U_NSD, GPIO_PIN_U_NSD, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_W_SW, GPIO_PIN_W_SW, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIO_PORT_W_NSD, GPIO_PIN_W_NSD, GPIO_PIN_RESET);
      break;
    case (1):
      HAL_GPIO_WritePin(GPIO_PORT_W_NSD, GPIO_PIN_W_NSD, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_V_NSD, GPIO_PIN_V_NSD, GPIO_PIN_RESET);
      break;
    case (2):
      HAL_GPIO_WritePin(GPIO_PORT_V_SW, GPIO_PIN_V_SW, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_V_NSD, GPIO_PIN_V_NSD, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_U_SW, GPIO_PIN_U_SW, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIO_PORT_U_NSD, GPIO_PIN_U_NSD, GPIO_PIN_RESET);
      break;
    case (3):
      HAL_GPIO_WritePin(GPIO_PORT_U_NSD, GPIO_PIN_U_NSD, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_W_NSD, GPIO_PIN_W_NSD, GPIO_PIN_RESET);
      break;
    case (4):
      HAL_GPIO_WritePin(GPIO_PORT_W_SW, GPIO_PIN_W_SW, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_W_NSD, GPIO_PIN_W_NSD, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_V_SW, GPIO_PIN_V_SW, GPIO_PIN_RESET);
      HAL_GPIO_WritePin(GPIO_PORT_V_NSD, GPIO_PIN_V_NSD, GPIO_PIN_RESET);
      break;
    case (5):
      HAL_GPIO_WritePin(GPIO_PORT_V_NSD, GPIO_PIN_V_NSD, GPIO_PIN_SET);
      HAL_GPIO_WritePin(GPIO_PORT_U_NSD, GPIO_PIN_U_NSD, GPIO_PIN_RESET);
      break;
  }
  period_counter++;
  
  /* USER CODE END TIM8_UP_IRQn 0 */
  HAL_TIM_IRQHandler(&htim8);
  /* USER CODE BEGIN TIM8_UP_IRQn 1 */

  /* USER CODE END TIM8_UP_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
