#include "ui.h"
#include "lcd1.h"


//Déclaration des fonctions
void ui_led_on(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOx,GPIO_Pin, GPIO_PIN_SET);
}

void ui_led_off(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOx,GPIO_Pin, GPIO_PIN_RESET);
}

void affiche_lcd(I2C_HandleTypeDef* I2Cx, rgb_lcd* DataStruct,char *str)
{
	clearlcd();
	lcd_position(I2Cx,0,0);
	lcd_print(I2Cx, str);
}

