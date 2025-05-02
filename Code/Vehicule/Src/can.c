/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

/*------------------------------------------------------------------------
/Définition des variables pour la communication CAN
/------------------------------------------------------------------------*/

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8], RxData[8];
uint32_t TxMailbox;

/*------------------------------------------------------------------------
/Définition des flags
/------------------------------------------------------------------------*/

volatile uint8_t EVSE_CHECK = 0; //Flag de compatibilité de la borne

/*------------------------------------------------------------------------
/Définition des octets de data des trames CAN
/------------------------------------------------------------------------*/

CAN_Message car_batt_msg = {
    .id = CARSIDE_BATT_ID,
    .dlc = 8,
    .data = {0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x01, 0x00} //400V ; 50% de charge
};

CAN_Message car_duree_charge = {
    .id = CARSIDE_DUREE_ID,
    .dlc = 8,
    .data = {0x00, 0xFF, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00} //Temps max de recharge = 144min, durée estimée de charge = 96min
};

CAN_Message car_statut = {
    .id = CARSIDE_STATUT_ID,
    .dlc = 8,
    .data = {0x02, 0x01, 0xF4, 0x00, 0x00, 0x00, 0x32, 0x00} //Chademo V1 ; Tension de charge = 500V ; Amperage demandé = 125A ; kW à charger = 50kW
};


/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 16;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_8TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
  CAN_FilterTypeDef canfilterconfig;
          canfilterconfig.FilterBank = 0;
          canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
          canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
          canfilterconfig.FilterIdHigh = 0x108 << 5; //FIltre pour ne recevoir que la trame 0x108
          canfilterconfig.FilterIdLow = 0;
          canfilterconfig.FilterMaskIdHigh = 0x7FF << 5;
          canfilterconfig.FilterMaskIdLow = 0;
          canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
          canfilterconfig.FilterActivation = ENABLE;
          HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

//Fonction d'envoie d'une trame CAN

void Send_CAN_Message(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *data, uint8_t dlc) {
    CAN_TxHeaderTypeDef TxHeader;
    uint32_t TxMailbox;

    // Configuration de l'en-tête CAN
    TxHeader.DLC = 8;//dlc;
    TxHeader.StdId = id;               // Identifiant standard (11 bits)
    TxHeader.IDE = CAN_ID_STD;          // Mode standard
    TxHeader.RTR = CAN_RTR_DATA;        // Trame de données
    TxHeader.TransmitGlobalTime = DISABLE;

    // Envoi du message CAN
    if (HAL_CAN_AddTxMessage(hcan, &TxHeader, data, &TxMailbox) != HAL_OK) {
        //Error_Handler();
    }
}

/*------------------------------------------------------------------------
/Fonction d'interruption CAN. Quand une trame est reçue, cette fonction est appelée
/------------------------------------------------------------------------*/

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {

    // Lire le message du FIFO0
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
        // Gérer une erreur de réception
        Error_Handler();
    }

    // Vérifier si l'ID correspond à la trame 0x108
    if (RxHeader.StdId == 0x108)
    {
        // Traiter la trame CHAdeMO 0x108
    	uint16_t tension_max_evse = (RxData[2] << 8) | RxData[1];
        uint16_t intensite_max_evse = RxData[3];
        uint16_t tension_seuil_evse = (RxData[5] << 8) | RxData[4];

        // Affichage ou traitement des données

        if ((VMAX_BATT_EV <= tension_max_evse) && (VMAX_BATT_EV<=tension_seuil_evse)  && (IMAX_BATT_EV<=intensite_max_evse)) //Test de compatibilité
        {
        	EVSE_CHECK = 1;
        }

    }
}

/*------------------------------------------------------------------------
/Fonction qui permet changer l'octet i d'une trame CAN id.
/------------------------------------------------------------------------*/

void update_CAN_data(uint8_t i, uint16_t id, uint8_t data) {
    if (i >= 8) return; // Sécurité : éviter les débordements

    CAN_Message* msg = NULL;

    // Sélectionner la bonne structure en fonction de l’ID
    if (id == car_batt_msg.id) {
        msg = &car_batt_msg;
    } else if (id == car_duree_charge.id) {
        msg = &car_duree_charge;
    } else if (id == car_statut.id) {
        msg = &car_statut;
    }

    if (msg != NULL) {
        msg->data[i] = data;
    }
}
/* USER CODE END 1 */
