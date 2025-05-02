/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   Déclarations des fonctions et variables liées à la gestion des E/S GPIO.
  * @author  Votre Nom
  * @date    2025
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * Tous droits réservés.
  *
  * Ce logiciel est distribué sous la licence indiquée dans le fichier LICENSE
  * à la racine du projet. S'il est absent, il est fourni "EN L'ÉTAT".
  *
  ******************************************************************************
  */

#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/**
 * @defgroup GPIO Gestion des E/S
 * @brief Contient les définitions et fonctions pour configurer les GPIOs.
 * @{
 */

/**
 * @brief Flag déclenché par l'appui sur le bouton START (connecté à PC0).
 *
 * Ce flag passe à 1 quand l'utilisateur appuie sur le bouton START.
 */
extern volatile uint8_t START;

/**
 * @brief Entrée de ligne "permission de charge".
 *
 * Cette entrée reflète l'autorisation de charger envoyée par l'EV.
 */
extern volatile uint8_t J;

/**
 * @brief Initialise les broches GPIO configurées via STM32CubeMX.
 *
 * Cette fonction configure les entrées/sorties selon les paramètres définis
 * dans l'outil STM32CubeMX.
 */
void MX_GPIO_Init(void);

/** @} */ // Fin du groupe GPIO

#ifdef __cplusplus
}
#endif
#endif /* __GPIO_H__ */
