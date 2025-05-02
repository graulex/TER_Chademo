/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   Ce fichier contient les prototypes des fonctions pour le fichier usart.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * Tous droits réservés.
  *
  * Ce logiciel est distribué selon les termes précisés dans le fichier LICENSE.
  * Si aucun fichier LICENSE n’est présent, ce logiciel est fourni "EN L'ÉTAT".
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "state_machine.h"
/* USER CODE END Includes */

/**
 * @brief Handle de l’interface UART2.
 */
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/**
 * @brief Donnée reçue par interruption UART.
 *
 * Utilisé pour lire un octet entrant via USART2.
 */
extern uint8_t rx_data;

/**
 * @brief Flag d'arrêt (STOP) déclenché par la réception série.
 *
 * Ce flag est activé par la liaison avec Matlab
 */
extern volatile uint8_t STOP1;

/* USER CODE END Private defines */

/**
 * @brief Initialise l'interface UART2 avec les paramètres configurés dans STM32CubeMX.
 */
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
