/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : En-tête pour le fichier main.c.
  *                   Ce fichier contient les définitions globales du projet.
  *
  * @attention
  * Copyright (c) 2025 STMicroelectronics.
  * Tous droits réservés.
  * Ce logiciel est distribué selon les termes de la licence présente dans le
  * dossier racine du projet. À défaut, ce logiciel est fourni tel quel ("AS-IS").
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l4xx_hal.h"

/** @defgroup Constantes_Charge_Batterie
  * @brief Constantes spécifiques à la batterie EV
  * @{
  */
#define VMAX_BATT_EV 400  /**< Tension maximale de charge de la batterie (en Volts) */
#define IMAX_BATT_EV 125  /**< Courant maximal de charge de la batterie (en Ampères) */
/** @} */

/**
 * @brief Fonction appelée en cas d’erreur critique du système.
 */
void Error_Handler(void);

/** @defgroup GPIO_Definitions
  * @brief Définition des broches utilisées dans le projet
  * @{
  */
#define B1_Pin             GPIO_PIN_13
#define B1_GPIO_Port       GPIOC

#define USART_TX_Pin       GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA

#define USART_RX_Pin       GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

#define LD2_Pin            GPIO_PIN_5
#define LD2_GPIO_Port      GPIOA

#define d1_Pin             GPIO_PIN_6        /**< Entrée déclenchement D1 (interruption) */
#define d1_GPIO_Port       GPIOA
#define d1_EXTI_IRQn       EXTI9_5_IRQn

#define main_relay_Pin     GPIO_PIN_9        /**< Sortie pour le relais principal */
#define main_relay_GPIO_Port GPIOA

#define TMS_Pin            GPIO_PIN_13
#define TMS_GPIO_Port      GPIOA

#define TCK_Pin            GPIO_PIN_14
#define TCK_GPIO_Port      GPIOA

#define SWO_Pin            GPIO_PIN_3
#define SWO_GPIO_Port      GPIOB

#define d2_Pin             GPIO_PIN_4        /**< Entrée déclenchement D2 (interruption) */
#define d2_GPIO_Port       GPIOB
#define d2_EXTI_IRQn       EXTI4_IRQn

#define k_Pin              GPIO_PIN_6        /**< Sortie commande signal K */
#define k_GPIO_Port        GPIOB
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
