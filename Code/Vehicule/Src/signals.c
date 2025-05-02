#include "signals.h"
#include "stm32l4xx_hal.h"
#include "main.h"
#include "gpio.h"
#include "state_machine.h"


// ===================================================================
// Active le signal K (GPIOB PIN 6) pour autoriser la charge côté véhicule
// ===================================================================
void k_on()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET); // Met la broche PB6 à l'état haut
}


// ===================================================================
// Désactive le signal K (GPIOB PIN 6), coupe l'autorisation de charge
// ===================================================================
void k_off()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); // Met la broche PB6 à l'état bas
}


// ===================================================================
// Ferme le relais principal (GPIOA PIN 9), permet le passage du courant
// ===================================================================
void close_main_relay()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // Active le relais (logique inverse)
}


// ===================================================================
// Ouvre le relais principal (GPIOA PIN 9), interrompt le courant de charge
// ===================================================================
void open_main_relay()
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // Désactive le relais (logique inverse)
}
