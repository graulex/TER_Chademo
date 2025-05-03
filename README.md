# Projet TER – Communication CAN avec STM32 pour la recharge CHAdeMO

##  Introduction

Ce dépôt GitHub présente le travail réalisé dans le cadre du **projet TER** intitulé :

**_Conception de cartes de communication CAN sur la base d’un microcontrôleur STM32 pour l’émulation de la gestion de charge de la voiture électrique avec le protocole CHAdeMO._**

Ce projet a été mené par :

- **Alexandre Guilcher**  
- **Damien Gonfo**  
- **Salah Ouaret**  

Sous la direction de **Damian Sal y Rosas**.

---

##  Organisation du dépôt

### `code/`
Contient l'ensemble des codes sources du projet :
-  **Code C STM32 - Borne de recharge (EVSE)** : développé avec STM32CubeIDE, implémente la logique de communication CHAdeMO côté borne.
-  **Code C STM32 - Véhicule électrique (EV)** : développé également sur STM32CubeIDE, simule le comportement d’un véhicule compatible CHAdeMO.
-  **Interface MATLAB** : IHM développée sous MATLAB permettant de communiquer avec la borne via une interface série (USART). Elle permet de lancer ou arrêter la charge et de suivre l’état de la batterie depuis un ordinateur.

---

### `documentation/`
Regroupe les ressources techniques utilisées :
-  **Articles scientifiques**
-  **Documentation technique officielle IEEE**

---

### `doxygen/`
Documentation logicielle générée automatiquement avec **Doxygen** :  
Décrit les fonctions, structures et comportements du code C (borne et véhicule).

---

### `uml/`
Diagrammes UML utilisés pendant la phase de conception :
- Diagrammes de cas d’usage
- Diagrammes de séquence
- Diagrammes de classes pour le logiciel embarqué de la borne et du véhicule
- Machines à états du véhicule et de la borne

---

### `kicad/`
Plans électroniques créés avec **KiCad** :
- 🛠 **Carte Borne de Recharge**
-  **Carte Véhicule Électrique**

Ces schémas permettent la fabrication physique des deux cartes de communication basées sur le protocole CAN.

---

##  Remarques

- Ce projet met en œuvre une **communication CAN bas-niveau**, conforme au protocole **CHAdeMO**, simulée entre une "borne" et un "véhicule" via des cartes STM32.
- L'IHM MATLAB agit comme un **outil de supervision et de contrôle**, permettant de **déclencher** et **suivre** une session de charge.

