#include "ui.h"
#include "lcd1.h"

// Allume une LED connectée à la broche spécifiée (niveau logique haut)
void ui_led_on(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

// Éteint une LED connectée à la broche spécifiée (niveau logique bas)
void ui_led_off(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

// Affiche une chaîne de caractères sur l'écran LCD I2C
void affiche_lcd(I2C_HandleTypeDef* I2Cx, rgb_lcd* DataStruct, char *str)
{
	clearlcd();                 // Efface l'affichage précédent
	lcd_position(I2Cx, 0, 0);   // Place le curseur en haut à gauche
	lcd_print(I2Cx, str);       // Affiche la chaîne de caractères
}
