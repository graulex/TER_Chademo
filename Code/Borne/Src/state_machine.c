#include "state_machine.h"

static rgb_lcd lcdData;
uint8_t J_previous = 0;


CHAdeMO_State state = IDLE;


void StateMachine_ForceStopState() {
    state = STOP;
}

void StateMachine_Init() {
    state = IDLE;
}

void StateMachine_Run() {
    switch (state) {
        case IDLE:
        	affiche_lcd(&hi2c1,&lcdData,"App START");
        	if (START == 1) {
                state = BATT_COMPATIBILITY;
                START = 0;
                affiche_lcd(&hi2c1,&lcdData,"Fermeture d1");
                dx_on(D1); //Ferme le relai d1
                HAL_Delay(1000);
            }
            break;

        case BATT_COMPATIBILITY:
        	if (BATT_CHECK == 1) { //Batterie compatible
        		state = CHARGE_PERMISSION;
        		affiche_lcd(&hi2c1,&lcdData,"batt check ok");
        		HAL_Delay(1000);
        		Send_CAN_Message(&hcan1, evse_charge_param.id, evse_charge_param.data, evse_charge_param.dlc);
        	}
        	else //Batterie pas compatible
        	{
        		state = TERMINATING;
        		affiche_lcd(&hi2c1,&lcdData,"batt incompatible");
        		HAL_Delay(1000);
        	}

            break;

        case CHARGE_PERMISSION:
            if (J == 1)
            {
                state = CHARGING;
                affiche_lcd(&hi2c1,&lcdData,"Ferm. port charge");
                dx_off(D2); //Ferme D2
                HAL_Delay(1000);
            }
            break;

        case CHARGING: {
            J_previous = J;
            ui_led_on(LED_CHARGE);
            uint8_t charge_percent = 0;

            while (CHARGE_ENABLE == 1 && state == CHARGING) {

                // Affichage du pourcentage
                char buffer[32];
                sprintf(buffer, "Charge: %d %%", charge_percent);
                affiche_lcd(&hi2c1, &lcdData, buffer);

                HAL_Delay(80); // Attendre 500 ms

                // Simuler une charge qui monte
                if (charge_percent < 100) {
                    charge_percent++;
                }

                // Conditions d'arrêt
                if ((J == 0) && (J_previous == 1)) {
                    state = TERMINATING;
                    break;
                }

                if ((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0) || (STOP1 == 1)) {
                    state = STOP;
                    STOP1 = 0;
                    break;
                }
            }
            break;
        }

        case TERMINATING:
        	ui_led_off(LED_CHARGE);
        	dx_on(D2);
        	dx_off(D1);
        	affiche_lcd(&hi2c1,&lcdData,"Fin de charge");
        	HAL_Delay(5000);
            state = IDLE;
            break;

        case STOP: {
            affiche_lcd(&hi2c1, &lcdData, "STOP");
            ui_led_off(LED_CHARGE);
            dx_on(D2);
            dx_off(D1);

            uint32_t startTime = HAL_GetTick();
            while ((HAL_GetTick() - startTime) < 5000) { // 5 secondes
                ui_led_on(LED_ERREUR);
                HAL_Delay(200);
                ui_led_off(LED_ERREUR);
                HAL_Delay(200);
            }

            state = IDLE;
            break;
        }
    }
}


