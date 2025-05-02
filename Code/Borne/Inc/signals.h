/**
  ******************************************************************************
  * @file    signals.h
  * @brief   Déclarations des fonctions pour contrôler les signaux D1 et D2
  *          (sorties GPIO utilisées pour piloter des LEDs ou relais).
  * @date    27 mars 2025
  * @author  aguil
  ******************************************************************************
  */

#ifndef INC_SIGNALS_H_
#define INC_SIGNALS_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "main.h"
#include "lcd1.h"
#include "ui.h"
#include "gpio.h"

/**
 * @defgroup Signaux GPIO
 * @brief Fonctions de commande pour les broches D1 et D2.
 * @{
 */

/**
 * @brief Définition de la broche D1 (GPIOA, Pin 6). D1 est le premier signal de commande
 */
#define D1 GPIOA, GPIO_PIN_6

/**
 * @brief Définition de la broche D2 (GPIOA, Pin 7). D2 est le second signal de commande
 */
#define D2 GPIOA, GPIO_PIN_7

/**
 * @brief Active la sortie de commande D1 ou D2 (met la broche à l'état haut).
 * @param GPIOx Le port GPIO
 * @param GPIO_Pin Le numéro de broche (D1 ou D2)
 */
void d1_on(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Désactive la sortie de commande D1 ou D2 (met la broche à l'état bas).
 * @param GPIOx Le port GPIO
 * @param GPIO_Pin Le numéro de broche (D1 ou D2)
 */
void d1_off(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);


#endif /* INC_SIGNALS_H_ */
