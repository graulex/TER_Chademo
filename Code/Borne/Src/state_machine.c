#include "state_machine.h"

// Structure de gestion de l'écran LCD I2C
static rgb_lcd lcdData;

// Mémorise l’état précédent de J (permet de détecter une transition de 1 → 0)
uint8_t J_previous = 0;

// État courant de la machine d’état
CHAdeMO_State state = IDLE;

/**
 * Force l'arrêt immédiat de la machine d'état.
 */
void StateMachine_ForceStopState() {
    state = STOP;
}

/**
 * Initialise la machine d’état (mise à IDLE).
 */
void StateMachine_Init() {
    state = IDLE;
}

/**
 * Exécute la machine d’état.
 */
void StateMachine_Run() {
    switch (state) {

        // Attente de l’appui sur le bouton START
        case IDLE:
        	affiche_lcd(&hi2c1,&lcdData,"App START");

        	if (START == 1) {
                state = BATT_COMPATIBILITY;
                START = 0;

                // Fermeture du relais D1
                affiche_lcd(&hi2c1,&lcdData,"Fermeture d1");
                dx_on(D1);
                HAL_Delay(1000);
            }
            break;

        // Vérification de la compatibilité batterie/chargeur
        case BATT_COMPATIBILITY:
        	if (BATT_CHECK == 1) { // Batterie compatible
        		state = CHARGE_PERMISSION;
        		affiche_lcd(&hi2c1,&lcdData,"batt check ok");
        		HAL_Delay(1000);

        		// Envoi des paramètres de charge vers EVSE
        		Send_CAN_Message(&hcan1, evse_charge_param.id, evse_charge_param.data, evse_charge_param.dlc);
        	}
        	else {
        		// Batterie incompatible → arrêt
        		state = TERMINATING;
        		affiche_lcd(&hi2c1,&lcdData,"batt incompatible");
        		HAL_Delay(1000);
        	}
            break;

        // Attente de la permission de charge (ligne J à 1)
        case CHARGE_PERMISSION:
            if (J == 1) {
                state = CHARGING;
                affiche_lcd(&hi2c1,&lcdData,"Ferm. port charge");

                // Fermeture de D2 (lancement de la charge)
                dx_off(D2);
                HAL_Delay(1000);
            }
            break;

        // Boucle de charge : gestion active de la charge tant que CHARGE_ENABLE == 1
        case CHARGING: {
            J_previous = J;
            ui_led_on(LED_CHARGE);
            uint8_t charge_percent = 0;

            while (CHARGE_ENABLE == 1 && state == CHARGING) {

                // Affiche le pourcentage de charge simulé
                char buffer[32];
                sprintf(buffer, "Charge: %d %%", charge_percent);
                affiche_lcd(&hi2c1, &lcdData, buffer);

                HAL_Delay(80); // Délai entre deux "incréments" de charge

                // Incrément de charge simulé
                if (charge_percent < 100) {
                    charge_percent++;
                }

                // Arrêt si déconnexion de la ligne J (J passe de 1 à 0)
                if ((J == 0) && (J_previous == 1)) {
                    state = TERMINATING;
                    break;
                }

                // Arrêt si appui bouton STOP (GPIOC_PIN_1 à 0) ou STOP logiciel
                if ((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0) || (STOP1 == 1)) {
                    state = STOP;
                    STOP1 = 0;
                    break;
                }
            }
            break;
        }

        // Fin de charge : extinction des LEDs, ouverture des relais
        case TERMINATING:
        	ui_led_off(LED_CHARGE);
        	dx_on(D2);   // Ouvre D2
        	dx_off(D1);  // Ouvre D1
        	affiche_lcd(&hi2c1,&lcdData,"Fin de charge");
        	HAL_Delay(5000);
            state = IDLE;
            break;

        // Mode STOP : erreur ou arrêt d’urgence
        case STOP: {
            affiche_lcd(&hi2c1, &lcdData, "STOP");

            // Sécurité : couper relais et LED
            ui_led_off(LED_CHARGE);
            dx_on(D2);
            dx_off(D1);

            // Clignotement LED erreur pendant 5 secondes
            uint32_t startTime = HAL_GetTick();
            while ((HAL_GetTick() - startTime) < 5000) {
                ui_led_on(LED_ERREUR);
                HAL_Delay(200);
                ui_led_off(LED_ERREUR);
                HAL_Delay(200);
            }

            // Retour à l'état IDLE
            state = IDLE;
            break;
        }
    }
}
