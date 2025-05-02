#ifndef INC_SIGNALS_H_
#define INC_SIGNALS_H_

#define D1 GPIOA, GPIO_PIN_6
#define D2 GPIOA, GPIO_PIN_7

#include "stm32l4xx_hal.h"
#include "main.h"
#include "gpio.h"

void k_on();
void k_off();
void close_main_relay();
void open_main_relay();

#endif /* INC_SIGNALS_H_ */
