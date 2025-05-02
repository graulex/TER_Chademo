/**
  ******************************************************************************
  * @file    ui.h
  * @brief   Interface utilisateur : gestion des LEDs et affichage LCD.
  * @date    27 mars 2025
  * @author  aguil
  ******************************************************************************
  */

#ifndef __UI_H__
#define __UI_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "lcd1.h"

/**
 * @defgroup UI Interface Utilisateur
 * @brief Fonctions pour gérer les éléments de l'interface (LEDs, écran LCD).
 * @{
 */

/**
 * @brief Définition de la LED de charge (connectée à GPIOA_PIN_0).
 */
#define LED_CHARGE GPIOA, GPIO_PIN_0

/**
 * @brief Définition de la LED d’erreur (connectée à GPIOA_PIN_1).
 */
#define LED_ERREUR GPIOA, GPIO_PIN_1

/**
 * @brief Allume une LED connectée à la broche spécifiée.
 * @param GPIOx Le port GPIO
 * @param GPIO_Pin Le numéro de la broche
 */
void ui_led_on(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Éteint une LED connectée à la broche spécifiée.
 * @param GPIOx Le port GPIO
 * @param GPIO_Pin Le numéro de la broche
 */
void ui_led_off(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * @brief Affiche une chaîne de caractères sur l’écran LCD.
 * @param I2Cx Le handle de l'I2C utilisé
 * @param DataStruct Pointeur vers la structure de l’écran LCD
 * @param str Chaîne de caractères à afficher
 */
void affiche_lcd(I2C_HandleTypeDef* I2Cx, rgb_lcd* DataStruct, char *str);

/**
 * @brief Callback appelé lors d'une interruption externe (ex: bouton START, bouton STOP).
 * @param GPIO_Pin Numéro de la broche qui a déclenché l’interruption
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/** @} */ // Fin du groupe UI

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

#endif /* __UI_H__ */
