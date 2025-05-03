function envoyerStartUART()
    try
        % Ouvrir une connexion série sur le port COM4 à 115200 bauds
        s = serialport('COM3', 115200);
        
        % Envoyer la chaîne de caractères "START" sur le port série
        writeline(s, "S");
        
        % Pause pour s’assurer que le message est bien transmis
        pause(0.1);
        
        % Fermer proprement la connexion série (libérer le port COM)
        clear s;
        
    catch
        % En cas d’erreur (ex : port indisponible), afficher un message
        disp('Erreur envoi START.');
    end
end
