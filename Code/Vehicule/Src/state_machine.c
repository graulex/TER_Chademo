#include "state_machine.h"


// ============================================
// ========== Définition des états ============
// ============================================

typedef enum {
    IDLE,         // Attente de demande de charge
    CHECK_EVSE,   // Vérification de la borne (EVSE)
    CHARGING,     // Phase de charge active
    TERMINATING   // Fin de charge et remise à zéro
} CHAdeMO_State;


// ============================================
// ========== Variables globales ==============
// ============================================

CHAdeMO_State state = IDLE; // État courant de la machine à états
int EOC = 0;                // End Of Charge (0 : pas terminé, 1 : terminé)


// ============================================================
// ========== Initialisation de la machine à états ===========
// ============================================================

/**
 * @brief Initialise la machine à états et démarre la réception CAN
 */
void StateMachine_Init() {
    state = IDLE;
    HAL_CAN_Start(&hcan1); // Démarre le CAN
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING); // Active les interruptions CAN RX
}


// ============================================================
// ========== Exécution de la machine à états =================
// ============================================================

/**
 * @brief Fonction principale de gestion des états
 */
void StateMachine_Run() {
    switch (state) {

        case IDLE:
            // Attente de déclenchement par une variable externe (d1)
            if (d1 == 1)
            {
                state = CHECK_EVSE;

                // Envoie des premières trames CAN pour initier la charge
                Send_CAN_Message(&hcan1, car_batt_msg.id, car_batt_msg.data, car_batt_msg.dlc); // Trame 0x100
                HAL_Delay(1);
                Send_CAN_Message(&hcan1, car_statut.id, car_statut.data, car_statut.dlc);        // Trame 0x102
                HAL_Delay(100);

                d1 = 0; // Réinitialise le déclencheur
            }
            break;

        case CHECK_EVSE:
            // Si la borne est prête (EVSE_CHECK = 1), passe à la charge
            if (EVSE_CHECK == 1)
            {
                state = CHARGING;
                k_on();               // Active le signal K (autorisation de charge)
                HAL_Delay(1000);      // Attente de stabilisation
            }
            break;

        case CHARGING:
            // Si déclenchement de charge détecté (d2)
            if (d2 == 1) {
                close_main_relay();   // Active le relais principal
                charge_monitoring();  // Lance la surveillance de charge
                d2 = 0;
                state = TERMINATING;  // Passe à l'étape de terminaison
            }
            break;

        case TERMINATING:
            k_off();                          // Désactive le signal K
            open_main_relay();                // Coupe le relais principal
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET); // Éteint LED ou signal visuel
            state = IDLE;                     // Retour à l'état initial
            break;
    }
}


// ============================================================
// ========== Surveillance de la phase de charge ==============
// ============================================================

/**
 * @brief Surveille la phase de charge en cours
 *
 * Active les trames nécessaires pour maintenir la charge
 * et clignote une LED jusqu'à la fin de la charge.
 */
void charge_monitoring()
{
    EOC = 0;

    update_CAN_data(5, 0x102, 0x01); // Active le flag "Charging Enable"
    update_CAN_data(3, 0x102, 0x7D); // Demande 125 A à la borne

    uint32_t start_time = HAL_GetTick(); // Temps de départ

    while (EOC != 1) // Boucle jusqu’à la fin de charge
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); // Clignotement (LED ou indicateur)
        Send_CAN_Message(&hcan1, car_statut.id, car_statut.data, car_statut.dlc); // Mise à jour CAN
        HAL_Delay(100);

        // Fin automatique après 10 secondes si rien n'est détecté
        if ((HAL_GetTick() - start_time) >= 10000) {
            EOC = 1;
        }

        end_of_charge(); // Vérifie l’état de fin de charge via une entrée GPIO
    }
}


// ============================================================
// ========== Détection de fin de charge ======================
// ============================================================

void end_of_charge()
{
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == 1) {
        EOC = 1;
    }
}
