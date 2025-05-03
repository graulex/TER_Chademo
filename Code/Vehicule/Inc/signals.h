/**
  ******************************************************************************
  * @file           : signals.h
  * @brief          : Déclarations des fonctions de contrôle des signaux physiques
  *                   (commande du relais principal et du signal K).
  ******************************************************************************
  */

#ifndef INC_SIGNALS_H_
#define INC_SIGNALS_H_

#include "stm32l4xx_hal.h"
#include "main.h"
#include "gpio.h"

/** @defgroup Signaux_Entrée
  * @brief Définition des broches d'entrée D1 et D2
  * @{
  */
#define D1 GPIOA, GPIO_PIN_6  /**< Broche d’entrée D1 (interruption/événement) */
#define D2 GPIOA, GPIO_PIN_7  /**< Broche d’entrée D2 (interruption/événement) */
/** @} */

/** @defgroup Fonctions_Commande_Signaux
  * @brief Fonctions pour contrôler les signaux de puissance
  * @{
  */

/**
 * @brief Active le signal K (autorisation de charge).
 */
void k_on(void);

/**
 * @brief Désactive le signal K.
 */
void k_off(void);

/**
 * @brief Ferme le relais principal.
 */
void close_main_relay(void);

/**
 * @brief Ouvre le relais principal.
 */
void open_main_relay(void);

/** @} */

#endif /* INC_SIGNALS_H_ */
