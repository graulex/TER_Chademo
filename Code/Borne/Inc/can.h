/**
  ******************************************************************************
  * @file           : can.h
  * @brief          : Déclarations des fonctions et structures liées à la
  *                   communication CAN pour le côté borne de recharge.
  ******************************************************************************
  * @note           : Ce fichier gère la réception et l'envoi des trames CAN
  *                   entre l'EVSE et le véhicule selon le protocole CHAdeMO.
  ******************************************************************************
  */

#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdio.h>
#include "lcd1.h"
#include "i2c.h"
#include "ui.h"
#include "usart.h"

/** @defgroup CAN_Communication_EVSE
  * @brief Définitions et fonctions liées au bus CAN pour l’EVSE
  * @{
  */

extern CAN_HandleTypeDef hcan1;

/** @brief Flag indiquant si la batterie est compatible */
extern volatile uint8_t BATT_CHECK;

/** @brief Flag indiquant si le véhicule a activé la demande de charge */
extern volatile uint8_t CHARGE_ENABLE;

/** @brief Identifiant de la trame envoyée par l’EVSE contenant les paramètres de charge */
#define EVSE_CHARGE_PARAM_ID  0x108

/** @brief Tension maximale délivrée par l’EVSE (en Volts) */
#define MAX_VOLTAGE_EVSE      600

/**
 * @brief Structure représentant une trame CAN générique.
 */
typedef struct {
    uint32_t id;       /**< Identifiant CAN (11 bits ) */
    uint8_t dlc;       /**< Nombre d’octets de données (max 8) */
    uint8_t data[8];   /**< Tableau des données de la trame */
} CAN_Message;

/** @brief Trame contenant les paramètres de charge envoyés par l’EVSE */
extern CAN_Message evse_charge_param;

/**
 * @brief Initialise le périphérique CAN1.
 */
void MX_CAN1_Init(void);

/**
 * @brief Envoie une trame CAN via le périphérique spécifié.
 * @param hcan Pointeur vers le périphérique CAN
 * @param id Identifiant de la trame
 * @param data Pointeur vers les données à envoyer
 * @param dlc Longueur des données
 */
void Send_CAN_Message(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *data, uint8_t dlc);

/**
 * @brief Callback appelée automatiquement lorsqu’un message est en attente dans FIFO0.
 * @param hcan Pointeur vers le périphérique CAN concerné
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */
