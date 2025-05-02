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

// Structures et buffers CAN
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8], RxData[8];
uint32_t TxMailbox;

// Drapeaux d'état liés à la batterie et à la charge
volatile uint8_t BATT_CHECK = 0; // Flag : batterie compatible
volatile uint8_t CHARGE_ENABLE = 0; // Flag : permission de charge reçue

// Variables extraites des trames CAN 0x100
uint16_t max_batt_voltage = 0;
uint16_t charged_rate_reference_constant = 0;

// Trame 0x101
uint16_t max_charge_time = 0;

// Trame 0x102
uint16_t chademo_version = 0;
uint16_t target_batt_voltage = 0;
uint16_t max_charge_current = 0;
uint16_t charge_enable = 0;
uint16_t charged_rate = 0;

// Données prédéfinies de la trame 0x108 (envoyée par l'EVSE vers l'EV)
CAN_Message evse_charge_param = {
    .id = EVSE_CHARGE_PARAM_ID,
    .dlc = 8,
    .data = { 0x01, 0x58, 0x02, 0xFF, 0xF4, 0x01, 0x00, 0x00 }
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

  // Configuration des filtres pour accepter les trames 0x100, 0x101, 0x102

  // Trame 0x100
  CAN_FilterTypeDef canfilterconfig;
  canfilterconfig.FilterBank = 0;
  canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
  canfilterconfig.FilterIdHigh = 0x100 << 5;
  canfilterconfig.FilterIdLow = 0;
  canfilterconfig.FilterMaskIdHigh = 0x7FF << 5;
  canfilterconfig.FilterMaskIdLow = 0;
  canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  canfilterconfig.FilterActivation = ENABLE;
  HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);

  // Trame 0x101
  canfilterconfig.FilterBank = 1;
  canfilterconfig.FilterIdHigh = 0x101 << 5;
  HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);

  // Trame 0x102
  canfilterconfig.FilterBank = 2;
  canfilterconfig.FilterIdHigh = 0x102 << 5;
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
    /* Activation de l’horloge CAN1 */
    __HAL_RCC_CAN1_CLK_ENABLE();

    /* Activation de l’horloge GPIOA */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /** Configuration des broches CAN1
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Initialisation de l'interruption CAN RX FIFO0 */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 2, 0);
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
    /* Désactivation de l’horloge CAN1 */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /** Dé-initialisation des broches GPIO liées au CAN1 */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* Désactivation de l’interruption CAN1 RX FIFO0 */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

// Envoie une trame CAN standard sur le bus
void Send_CAN_Message(CAN_HandleTypeDef *hcan, uint32_t id, uint8_t *data,
		uint8_t dlc) {

	// Préparation de l'en-tête CAN
	TxHeader.DLC = 8; // Longueur des données
	TxHeader.StdId = EVSE_CHARGE_PARAM_ID; // Identifiant standard (forcé ici)
	TxHeader.IDE = CAN_ID_STD; // Mode standard
	TxHeader.RTR = CAN_RTR_DATA; // Trame de données
	TxHeader.TransmitGlobalTime = DISABLE;

	// Envoi de la trame
	if (HAL_CAN_AddTxMessage(hcan, &TxHeader, data, &TxMailbox) != HAL_OK) {
		Error_Handler(); // Gestion d'erreur
	}
}

// Callback appelé à la réception d'une trame CAN
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {

	// Lecture de la trame
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
		Error_Handler();
	}

	// Traitement selon l'ID de la trame reçue

	if (RxHeader.StdId == 0x100) {
		// Trame : compatibilité batterie
		max_batt_voltage = (RxData[4] << 8) | RxData[5];
		charged_rate_reference_constant = RxData[6];

		if (max_batt_voltage <= MAX_VOLTAGE_EVSE) {
			BATT_CHECK = 1;
		}
	}
	else if (RxHeader.StdId == 0x101) {
		// Trame : durée max de charge
		max_charge_time = RxData[2];
	}
	else if (RxHeader.StdId == 0x102) {
		// Trame : consignes de charge
		uint16_t chademo_version = RxData[0];
		uint16_t target_batt_voltage = (RxData[1] << 8) | RxData[2];
		uint16_t max_charge_current = RxData[3];
		uint16_t charge_enable = RxData[5] & 0x01;
		uint16_t charged_rate = RxData[6];

		if (charge_enable == 1) {
			CHARGE_ENABLE = 1; // Permission de charge active
		}
	}
}

/* USER CODE END 1 */
