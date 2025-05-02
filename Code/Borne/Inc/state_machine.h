/**
  ******************************************************************************
  * @file    state_machine.h
  * @brief   Déclarations liées à la machine d'états du protocole CHAdeMO.
  * @date    2025
  ******************************************************************************
  */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

/* Includes ------------------------------------------------------------------*/
#include "ui.h"
#include "signals.h"
#include "main.h"
#include "i2c.h"
#include "can.h"
#include "gpio.h"

/**
 * @defgroup StateMachine Machine d'états CHAdeMO
 * @brief Gère les différents états du cycle de charge d’un véhicule électrique.
 * @{
 */

/**
 * @enum CHAdeMO_State
 * @brief Enumération des états possibles dans le protocole CHAdeMO.
 */
typedef enum {
    IDLE,                /**< Attente de connexion. */
    BATT_COMPATIBILITY,  /**< Vérification de la compatibilité batterie/EVSE. */
    CHARGE_PERMISSION,   /**< Attente de l'autorisation de charge. */
    CHARGING,            /**< Phase de recharge active. */
    TERMINATING,         /**< Fin de charge et arrêt des équipements. */
    STOP                 /**< Arrêt forcé ou erreur. */
} CHAdeMO_State;

/**
 * @brief Force immédiatement l'état STOP, généralement en cas d'erreur ou d'arrêt d'urgence.
 */
void StateMachine_ForceStopState(void);

/**
 * @brief Initialise la machine d'états. À appeler une seule fois au démarrage.
 */
void StateMachine_Init(void);

/**
 * @brief Fonction principale à appeler en boucle pour faire évoluer les états.
 */
void StateMachine_Run(void);

/** @} */ // Fin du groupe StateMachine

#endif /* INC_STATE_MACHINE_H_ */
