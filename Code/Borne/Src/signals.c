#include "signals.h"

/**
 * Active la ligne de signal de commande D1 ou D2 en mettant la broche à l'état bas (logique 0).
 */
void dx_on(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

/**
 * Désactive la ligne de signal de commande D1 ou D2 en mettant la broche à l'état haut (logique 1).
 */
void dx_off(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}
