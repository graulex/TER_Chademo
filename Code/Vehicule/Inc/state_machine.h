/**
  ******************************************************************************
  * @file           : state_machine.h
  * @brief          : Déclarations des fonctions liées à la machine d'états
  *                   pour le protocole de charge CHAdeMO simulé.
  ******************************************************************************
  */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

#include "signals.h"
#include "main.h"
#include "can.h"
#include "gpio.h"
#include "usart.h"
#include "stm32l476xx.h"
#include "stm32l4xx_hal.h"

/** @defgroup Machine_Etats
  * @brief Fonctions principales de gestion de la charge
  * @{
  */

/**
 * @brief Initialise la machine d'états (démarre CAN, active les interruptions).
 */
void StateMachine_Init(void);

/**
 * @brief Fonction principale de gestion de la machine d'états.
 *        Elle effectue les transitions entre les états : IDLE, CHECK_EVSE,
 *        CHARGING et TERMINATING.
 */
void StateMachine_Run(void);

/**
 * @brief Supervise la charge pendant l’état CHARGING.
 *        Elle gère les trames CAN et les délais.
 */
void charge_monitoring(void);

/**
 * @brief Vérifie si la charge est terminée (lecture de la broche de fin de charge).
 */
void end_of_charge(void);

/** @} */

#endif /* INC_STATE_MACHINE_H_ */
