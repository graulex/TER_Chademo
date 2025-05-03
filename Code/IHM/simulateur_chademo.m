function simulateur_chademo()

    stopRequested = false;
    soc_data = [];
    courant_data = [];
    pwm_data = [];

    % === Fenêtre principale
    f = figure('Name', 'Simulation CHAdeMO', ...
               'Position', [500 200 700 550], ...
               'Color', [1 1 1]);

    % === LED centrée
    axLED = axes(f, 'Position', [0.3 0.85 0.07 0.1]);
    imshow('led_orange.png', 'Parent', axLED); axis off;

    % === Étiquette État à droite de la LED
    txtEtat = uicontrol(f, 'Style', 'text', ...
        'String', 'En attente...', ...
        'FontSize', 12, ...
        'FontWeight', 'bold', ...
        'ForegroundColor', 'blue', ...
        'BackgroundColor', 'white', ...
        'Position', [280 470 300 22], ...
        'HorizontalAlignment', 'left');

    % === Image batterie centrée
    axBat = axes(f, 'Position', [0.38 0.55 0.25 0.3]);
    imshow('battery_0.png', 'Parent', axBat); axis off;

    % === Texte dynamique centré sous la batterie
    txtSOC = uicontrol(f, 'Style', 'text', 'String', 'SOC : 0 %', ...
        'FontSize', 12, 'BackgroundColor', 'white', ...
        'Position', [280 270 150 22], 'HorizontalAlignment', 'center');

    txtTension = uicontrol(f, 'Style', 'text', 'String', 'Tension : 0 V', ...
        'FontSize', 12, 'BackgroundColor', 'white', ...
        'Position', [280 240 150 22], 'HorizontalAlignment', 'center');

    txtCourant = uicontrol(f, 'Style', 'text', 'String', 'Courant : 0 A', ...
        'FontSize', 12, 'BackgroundColor', 'white', ...
        'Position', [280 210 150 22], 'HorizontalAlignment', 'center');

    txtPWM = uicontrol(f, 'Style', 'text', 'String', 'PWM : 0 %', ...
        'FontSize', 12, 'BackgroundColor', 'white', ...
        'Position', [280 180 150 22], 'HorizontalAlignment', 'center');

    % === Boutons centrés
    btnStart = uicontrol(f, 'Style', 'pushbutton', ...
        'String', 'Lancer Simulation', ...
        'FontSize', 12, ...
        'Position', [200 100 150 35], ...
        'Callback', @(~,~) startSimu());

    btnStop = uicontrol(f, 'Style', 'pushbutton', ...
        'String', 'Arrêter la charge', ...
        'FontSize', 12, ...
        'Position', [360 100 150 35], ...
        'Visible', 'off', ...
        'Callback', @(~,~) stopCharge());

    % === Fonctions internes ===

    function stopCharge()
        stopRequested = true;
    end

    function updateBatteryImage(soc)
        if soc <= 0
            img = 'battery_0.png';
        elseif soc <= 25
            img = 'battery_25.png';
        elseif soc <= 50
            img = 'battery_50.png';
        elseif soc <= 75
            img = 'battery_75.png';
        else
            img = 'battery_100.png';
        end
        imshow(img, 'Parent', axBat); axis off;
    end

    function startSimu()
        soc = 0;
        tension = 400;
        courant = 50;
        pwm = 0;

        stopRequested = false;
        imshow('led_orange.png', 'Parent', axLED); axis off;
        set(txtEtat, 'String', 'Véhicule détecté', 'ForegroundColor', 'black');
        pause(1);

        set(txtEtat, 'String', 'Échange de paramètres...', 'ForegroundColor', 'black');
        pause(1.5);

        % Erreur aléatoire simulée
        if rand() < 0.1
            set(txtEtat, 'String', 'Erreur : Défaut batterie détecté !', 'ForegroundColor', 'red');
            imshow('led_red.png', 'Parent', axLED); axis off;
            return;
        end

        set(txtEtat, 'String', 'Charge en cours...', 'ForegroundColor', [0 0.6 0]);
        imshow('led_green.png', 'Parent', axLED); axis off;
        set(btnStop, 'Visible', 'on');

        while soc < 100 && ~stopRequested
            soc = soc + 5;
            courant = max(0, courant - 1);
            pwm = min(100, pwm + 5);

            soc_data(end+1) = soc;
            courant_data(end+1) = courant;
            pwm_data(end+1) = pwm;

            set(txtSOC, 'String', sprintf('SOC : %d %%', soc));
            set(txtTension, 'String', sprintf('Tension : %d V', tension));
            set(txtCourant, 'String', sprintf('Courant : %d A', courant));
            set(txtPWM, 'String', sprintf('PWM : %d %%', pwm));
            updateBatteryImage(soc);

            pause(0.8);
        end

        set(btnStop, 'Visible', 'off');

        if stopRequested
            set(txtEtat, 'String', 'Charge interrompue par l’utilisateur', 'ForegroundColor', 'red');
            imshow('led_red.png', 'Parent', axLED); axis off;
        else
            set(txtEtat, 'String', 'Charge terminée', 'ForegroundColor', 'black');
            imshow('led_green.png', 'Parent', axLED); axis off;
        end

        exportData = table((1:length(soc_data))', soc_data', courant_data', pwm_data', ...
            'VariableNames', {'Temps_s', 'SOC_percent', 'Courant_A', 'PWM_percent'});
        writetable(exportData, 'donnees_charge.csv');
        disp('✅ Données exportées dans donnees_charge.csv');
    end
end
