/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   Header du module de gestion CAN (initialisation, envoi, réception)
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

#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/*                               INCLUSIONS                                   */
/* -------------------------------------------------------------------------- */
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "usart.h"
#include "gpio.h"
/* USER CODE END Includes */

/* -------------------------------------------------------------------------- */
/*                             DECLARATION DES HANDLES                        */
/* -------------------------------------------------------------------------- */
extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */

/* -------------------------------------------------------------------------- */
/*                         IDENTIFIANTS DE TRAMES CAN VEHICULE               */
/* -------------------------------------------------------------------------- */
#define CARSIDE_BATT_ID     0x100  // Trame d'information batterie (car_batt_msg)
#define CARSIDE_DUREE_ID    0x101  // Trame de durée estimée de charge
#define CARSIDE_STATUT_ID   0x102  // Trame de statut général du véhicule

/* -------------------------------------------------------------------------- */
/*                            VARIABLES EXTERNES                              */
/* -------------------------------------------------------------------------- */
extern volatile uint8_t EVSE_CHECK;      // Drapeau pour valider l'état de la borne

/* USER CODE END Private defines */

/* -------------------------------------------------------------------------- */
/*                          INITIALISATION DE L'INTERFACE CAN                */
/* -------------------------------------------------------------------------- */
/**
  * @brief Initialise le périphérique CAN1.
  */
void MX_CAN1_Init(void);

/* USER CODE BEGIN Prototypes */

/* -------------------------------------------------------------------------- */
/*                          PROTOTYPES DES FONCTIONS CAN                      */
/* -------------------------------------------------------------------------- */

/**
  * @brief Redirige les fonctions printf vers l’USART.
  */
int _write(int file, char *ptr, int len);

/**
  * @brief Envoie une trame CAN.
  * @param hcan : pointeur vers le handle CAN utilisé
  * @param id   : identifiant de la trame
  * @param data : tableau de données (max 8 octets)
  * @param dlc  : nombre d’octets à transmettre
  */
void Send_CAN_Message(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *data, uint8_t dlc);

/**
  * @brief Callback appelé lors de la réception d'une trame CAN.
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

/**
  * @brief Met à jour un octet spécifique d'une trame CAN identifiée.
  * @param i    : index de l’octet à modifier
  * @param id   : identifiant de la trame
  * @param data : nouvelle valeur de l’octet
  */
void update_CAN_data(uint8_t i, uint16_t id, uint8_t data);

/* -------------------------------------------------------------------------- */
/*                       STRUCTURE DE DONNÉES POUR LES TRAMES CAN            */
/* -------------------------------------------------------------------------- */

/**
  * @brief Représente une trame CAN.
  */
typedef struct {
    uint32_t id;       // Identifiant de la trame
    uint8_t dlc;       // Taille des données (Data Length Code, max 8)
    uint8_t data[8];   // Données à transmettre
} CAN_Message;

/* -------------------------------------------------------------------------- */
/*                         TRAMES CAN VÉHICULE PRÉ-DÉCLARÉES                 */
/* -------------------------------------------------------------------------- */
extern CAN_Message car_batt_msg;
extern CAN_Message car_duree_charge;
extern CAN_Message car_statut;

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */
