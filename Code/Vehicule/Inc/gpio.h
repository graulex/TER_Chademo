/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   Fichier d'en-tête pour la configuration des GPIOs.
  *
  * Ce fichier contient la déclaration de la fonction d'initialisation des broches
  * GPIO ainsi que des variables globales utilisées pour le contrôle d'événements
  * sur les entrées numériques.
  *
  * @attention
  * Copyright (c) 2025 STMicroelectronics.
  * Tous droits réservés.
  * Ce logiciel est distribué selon les termes de la licence fournie dans le
  * répertoire racine du projet. En l'absence de fichier LICENSE, ce logiciel
  * est fourni "EN L'ÉTAT".
  ******************************************************************************
  */

#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/**
 * @brief Variable globale indiquant l'état de la ligne d1.
 * @note Utilisée dans la machine à états pour passer de l’état IDLE à CHECK_EVSE.
 */
extern volatile uint8_t d1;

/**
 * @brief Variable globale indiquant l'état de la ligne d2.
 */
extern volatile uint8_t d2;

/**
 * @brief Initialise tous les GPIOs configurés dans CubeMX.
 *
 * Cette fonction est générée automatiquement par STM32CubeMX et appelle
 * les fonctions HAL nécessaires à la configuration des broches.
 */
void MX_GPIO_Init(void);

#ifdef __cplusplus
}
#endif
#endif /* __GPIO_H__ */
