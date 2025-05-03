function envoyerStopUART()
    try
        % Ouvrir le port série COM4 avec le même débit (115200 bauds)
        s = serialport('COM3', 115200);
        
        % Envoyer la chaîne "STOP" à la carte STM32
        writeline(s, "X");
        
        % Pause pour laisser le temps à l'envoi de se terminer
        pause(0.1);
        
        % Fermer la communication série pour éviter les conflits
        clear s;
        
    catch
        % Afficher une erreur si le port est occupé ou absent
        disp('Erreur envoi STOP.');
    end
end
