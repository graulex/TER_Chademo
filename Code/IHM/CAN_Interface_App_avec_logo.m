classdef CAN_Interface_App_avec_logo < matlab.apps.AppBase

    % === Déclaration des éléments de l'interface ===
    properties (Access = public)
        UIFigure         matlab.ui.Figure       % Fenêtre principale
        LogoImage        matlab.ui.control.Image % Image (logo)
        DateLabel        matlab.ui.control.Label % Affiche la date/heure
        AuthorsLabel     matlab.ui.control.Label % Noms des auteurs
        GroupLabel       matlab.ui.control.Label % Nom du groupe
        StationButton    matlab.ui.control.Button % Bouton pour ouvrir l'IHM station CHAdeMO
        SimuButton       matlab.ui.control.Button % Bouton pour lancer la simulation CHAdeMO
        TitleLabel       matlab.ui.control.Label % Titre principal
        ImportButton     matlab.ui.control.Button % Bouton "Importer fichier"
        VisualiserButton matlab.ui.control.Button % Bouton "Visualiser signal"
        DecoderButton    matlab.ui.control.Button % Bouton "Décoder trames"
    end

    % === Méthodes privées ===
    methods (Access = private)

        % Fonction exécutée au démarrage : initialise la date
        function startupFcn(app)
            app.DateLabel.Text = datestr(now, 'dd/mm/yyyy – HH:MM:SS');
        end

        % Callback du bouton Importer : affiche une fenêtre d'information
        function ImportButtonPushed(app, event)
            fig = uifigure('Name', 'Importer un signal');
            uilabel(fig, 'Text', 'Fonction d''import en cours...', 'Position', [20 50 300 22]);
        end

        % Callback du bouton Visualiser : ouvre un graphique vide
        function VisualiserButtonPushed(app, event)
            fig = uifigure('Name', 'Visualisation du signal CAN');
            ax = uiaxes(fig, 'Position', [50 50 500 300]);
            title(ax, 'Fenêtre de visualisation');
        end

        % Callback du bouton Décoder : affiche une zone de texte simulée
        function DecoderButtonPushed(app, event)
            fig = uifigure('Name', 'Décodage des trames');
            txt = uitextarea(fig, 'Position', [20 50 400 200]);
            txt.Value = {'Décodage en cours...', 'Fonction à implémenter'};
        end

        % Callback du bouton Simulation CHAdeMO : lance le simulateur
        function SimuButtonPushed(app, event)
            disp("🔁 Simulation CHAdeMO lancée...");
            simulateur_chademo(); % Appel de la fonction de simulation externe
        end

    end

    % === Méthodes publiques ===
    methods (Access = public)

        % Constructeur : crée l'interface et appelle la fonction de démarrage
        function app = CAN_Interface_App_avec_logo
            createComponents(app)                % Crée les éléments graphiques
            runStartupFcn(app, @startupFcn)      % Exécute startupFcn
        end

        % Destructeur : détruit la figure à la fermeture
        function delete(app)
            delete(app.UIFigure)
        end
    end

    % === Création de tous les composants de l'IHM ===
    methods (Access = private)

        function createComponents(app)

            % Fenêtre principale
            app.UIFigure = uifigure('Position', [100 100 700 550], 'Name', 'Projet TER – Interface CAN');

            % Logo en haut (image)
            app.LogoImage = uiimage(app.UIFigure);
            app.LogoImage.ImageSource = fullfile(pwd, 'téléchargement.jpeg'); % Image dans le dossier courant
            app.LogoImage.Position = [275 470 150 60];

            % Label de date et heure
            app.DateLabel = uilabel(app.UIFigure);
            app.DateLabel.Position = [200 445 300 22];
            app.DateLabel.FontSize = 14;
            app.DateLabel.HorizontalAlignment = 'center';

            % Noms des auteurs
            app.AuthorsLabel = uilabel(app.UIFigure);
            app.AuthorsLabel.Text = 'Salah OUARET, Alexandre GUICHLER, Damien GONFO';
            app.AuthorsLabel.Position = [100 420 500 22];
            app.AuthorsLabel.FontWeight = 'bold';
            app.AuthorsLabel.HorizontalAlignment = 'center';

            % Nom du groupe
            app.GroupLabel = uilabel(app.UIFigure);
            app.GroupLabel.Text = 'Groupe M1 SME';
            app.GroupLabel.Position = [100 395 500 22];
            app.GroupLabel.HorizontalAlignment = 'center';

            % Titre du projet
            app.TitleLabel = uilabel(app.UIFigure);
            app.TitleLabel.Text = 'Projet TER - Analyseur de trames CAN';
            app.TitleLabel.Position = [100 360 500 22];
            app.TitleLabel.FontSize = 18;
            app.TitleLabel.FontWeight = 'bold';
            app.TitleLabel.HorizontalAlignment = 'center';

            % === Ligne supérieure de boutons ===

            % Bouton Importer fichier
            app.ImportButton = uibutton(app.UIFigure, 'push');
            app.ImportButton.Position = [110 300 150 35];
            app.ImportButton.Text = 'Importer fichier';
            app.ImportButton.ButtonPushedFcn = createCallbackFcn(app, @ImportButtonPushed, true);

            % Bouton Visualiser signal
            app.VisualiserButton = uibutton(app.UIFigure, 'push');
            app.VisualiserButton.Position = [275 300 150 35];
            app.VisualiserButton.Text = 'Visualiser signal';
            app.VisualiserButton.ButtonPushedFcn = createCallbackFcn(app, @VisualiserButtonPushed, true);

            % Bouton Décoder trames
            app.DecoderButton = uibutton(app.UIFigure, 'push');
            app.DecoderButton.Position = [440 300 150 35];
            app.DecoderButton.Text = 'Décoder trames';
            app.DecoderButton.ButtonPushedFcn = createCallbackFcn(app, @DecoderButtonPushed, true);

            % === Ligne inférieure de boutons ===

            % Bouton pour lancer l'interface MATLAB de la station
            app.StationButton = uibutton(app.UIFigure, 'push');
            app.StationButton.Position = [250 250 200 35];
            app.StationButton.Text = 'Ouvrir IHM MATLAB';
            app.StationButton.ButtonPushedFcn = @(~,~) StationCHAdeMO_App();

            % Bouton pour lancer la simulation CHAdeMO
            app.SimuButton = uibutton(app.UIFigure, 'push');
            app.SimuButton.Position = [250 200 200 35];
            app.SimuButton.Text = 'Mode Simulation CHAdeMO';
            app.SimuButton.ButtonPushedFcn = createCallbackFcn(app, @SimuButtonPushed, true);
        end
    end
end
