/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

//Déclaration des variables
volatile uint8_t START = 0;  // Flag de démarrage
volatile uint8_t J = 0;  // Flag de j (ligne k)

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_CHARGE_Pin|LED_ERREUR_Pin|RELAY_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, d1_Pin|d2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : BP_START_Pin BP_STOP_Pin */
  GPIO_InitStruct.Pin = BP_START_Pin|BP_STOP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_CHARGE_Pin LED_ERREUR_Pin RELAY_Pin LD2_Pin
                           d1_Pin d2_Pin */
  GPIO_InitStruct.Pin = LED_CHARGE_Pin|LED_ERREUR_Pin|RELAY_Pin|LD2_Pin
                          |d1_Pin|d2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : j_Pin */
  GPIO_InitStruct.Pin = j_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(j_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0)
    {  // Vérifie si c'est PC0 qui a déclenché l'interruption (appui sur le BP START)
        START = 1;  // Active le flag
    }

    else if (GPIO_Pin == GPIO_PIN_1)
    {
    	// Vérifie si c'est PC1 qui a déclenché l'interruption (appui sur le BP STOP)
    	//StateMachine_ForceStopState(); //Passe la machine à l'état STOP
    }

    else if (GPIO_Pin == GPIO_PIN_6)
    {  // Vérifie si c'est PB6 qui a déclenché l'interruption (optocoupleur j)
    	J ^= 1;  // Change létat du flag à chaque interruption
    }
}

/* USER CODE END 2 */
