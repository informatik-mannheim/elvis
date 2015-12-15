

% Verschiebungsparameter (Abstände der Motoren)
t15 = -36;
t14 = -106;
t12 = -94;
t51 = -130;
t31 = -76; 
t33 = 113;
thand = 130;
% 1 x 7 Matrix für die Verschiebungsparameter
tparam = [t15 t14 t12 t51 t31 t33 thand];

%Schwerpunkte der einzelnen Gelenke
s00 = -26;
s15 = -28;
s14 = -30;
s12 = -55;
s51 = -58; %stimmt noch nicht
s31 = 50;
s33 = 59;
% 1 x 7 Matrix für die Verschiebungsparameter
sparam = [s00 s15 s14 s12 s51 s31 s33];

%Gewichte der Segmente (benannt nach unterem Punkt)
g00 = 314;
g15 = 270.4;
g14 = 206.4;
g12 = 463.4;
g51 = 394.6;
g31 = 371.6;
g33 = 37.6;
% 1 x 7 Matrix für die Gewichte
gparam = [g00 g15 g14 g12 g51 g31 g33];


% Nullvektor = Fußpunkt des Roboters
m0 = [0; 0; 0; 1];

%Winkel importieren
winkeltabelle = importdata('MATLAB\winkel_st_2.csv','\t', 1);

for (k = 1 : 1 : 90)
    
    clf
    
    %Einrichten des Fensters
    grid on
    ylabel('y')
    zlabel('z')
    title ('Roboter')
    axis([0 1 -200 500 -550 100])
    set(gca,'zdir', 'reverse') %Richtung der z-Achse umdrehen
    set(gca,'ydir', 'reverse') %Richtung der z-Achse umdrehen
    view(-90,0)
    hold on

    % Winkel
    alpha15 = winkeltabelle.data(k, 5);
    alpha14 = winkeltabelle.data(k, 4);
    alpha12 = -winkeltabelle.data(k, 2);
    alpha51 = winkeltabelle.data(k, 19);
    alpha31 = winkeltabelle.data(k, 13);
    alpha33 = winkeltabelle.data(k, 15)-90;
    % 1 x 6 Matrix für die Winkel
    winkel = [alpha15 alpha14 alpha12 alpha51 alpha31 alpha33];
     
    %eigentliche Transformation und Simulation 
       
    weiter = true;
    schonVerbessert = false;
    mLast = m0;
    mi = m0;
    gesamtWinkel = 0;
    %Fuß
    line([0, 0], [-55, 105], [0, 0]);
    
    %Gelenkpunkte (Koordinaten) in z- und y-Richtung
    my = [0 0 0 0 0 0 0];
    mz = [0 0 0 0 0 0 0];
    
    %Schwerpunktkoordinaten in z- und y-Richtung
    sy = [0 0 0 0 0 0 0];
    sz = [0 0 0 0 0 0 0];
   
    
    i = 1;
    while(i <= 7)
        t = m0; %Koordinatenursprung setzen, ausgehen vom Nullpunkt
        t = transl(0, 0, tparam(i)) * t; %Verschiebung des Koordinatenursprungs t um den Verschiebungsparameter in z-Richtung
      
        if (i>=2) gesamtWinkel = gesamtWinkel + winkel(i-1); end %Das Fußgelenk wird nie gedreht, daher i>1
        t = trotx(gesamtWinkel, 'deg') * t; %Koordinatentransformation: Drehung um x-Achse um die Summe der einzelnen Winkel
        
        s = t/tparam(i) * sparam(i); %t als Einheitsvektor für Schwerpunkte
        si = [mi(1)+s(1) ; mi(2)+s(2) ; mi(3)+s(3); 1]; %Vektoraddition: transformierte Vektoren werden zum vorherigen Vektor mx addiert
        plot3(si(1), si(2), si(3), '.r') %Anzeige der Schwerpunkte
                
       %Abspeichern der Schwerpunktkoordinaten zur späteren Berechnung des
       %Ges.Schwerpunktes
        sy(i)= si(2);
        sz(i)= si(3);
               
        mi = [mi(1)+t(1) ; mi(2)+t(2) ; mi(3)+t(3); 1]; %Vektoraddition: transformierte Vektoren werden zum vorherigen Vektor mx addiert
        plot3(mi(1), mi(2), mi(3), '.') %Anzeige der Punkte
        line([0, 0], [mLast(2), mi(2)], [mLast(3), mi(3)]); %Linie zwischen dem letzten Punkt und mx
        mLast = mi;
        
        %Abspeichern der Gelenkpunkte
        my(i) = mi(2);
        mz(i) = mi(3);
        
        if (mi(3) > 0 && i == 7 && schonVerbessert == true && weiter == true) %falls der Winkel nach der Korrektur immer noch nicht gut ist
            weiter = false;
            schonVerbessert = false;
        end
        if (mi(3) > 0 && i == 7 && schonVerbessert == false) %Abfrage, ob Winkel korrigiert werden muss
            schonVerbessert = true;
            %Berechnung des Verbesserten Winkels mit Kosinussatz
             a=sqrt((mz(7)-mz(1))^2+(my(7)-my(1))^2);
             b=sqrt((mz(1))^2+(my(7)-my(1))^2);
             alpha_strich = acos((a^2+b^2-(mz(7))^2)/2/a/b)*180/pi;
            winkel(1) = winkel(1) - alpha_strich;%Korrektur des Winkel
            winkeltabelle.data(k, 5) = winkel(1); % Korrektur des Winkels in der Winkeltablle
            if (winkel(1) > 85) 
                disp('Achtung')
            end
            i=0;
           %zurücksetzen aller Anfangswerte
            mLast = m0;
            mi = m0;
            gesamtWinkel = 0;
            %Fuß
            line([0, 0], [-55, 105], [0, 0]);

            %Gelenkpunkte (Koordinaten) in z- und y-Richtung
            my = [0 0 0 0 0 0 0];
            mz = [0 0 0 0 0 0 0];

            %Schwerpunktkoordinaten in z- und y-Richtung
            sy = [0 0 0 0 0 0 0];
            sz = [0 0 0 0 0 0 0];
            
           clf
            
             %Einrichten des Fensters
             grid on
             ylabel('y')
             zlabel('z')
             title ('Roboter')
             axis([0 1 -200 500 -550 100])
             set(gca,'zdir', 'reverse') %Richtung der z-Achse umdrehen
             set(gca,'ydir', 'reverse') %Richtung der z-Achse umdrehen
             view(-90,0)
             hold on
   
        end
        
         i = i + 1;
        
    end
    %Gesamtschwerpunkt berechnen mit Schwerpunktgleichung
    gesamtsy = 0;
    gesamtsz = 0;
    gesamtmasse = 0;
    for (i = 1 : 1 : 7)
       gesamtsy = gesamtsy + sy(i) * gparam(i); 
       gesamtsz = gesamtsz + sz(i) * gparam(i);
       gesamtmasse = gesamtmasse + gparam(i);
    end
    
    gesamtsy = gesamtsy / gesamtmasse;
    gesamtsz = gesamtsz / gesamtmasse;
     %Überprüfung, ob über dem Fuß
    if (gesamtsy < -55 || gesamtsy > 105)
        plot3(0, gesamtsy, gesamtsz, '*r') %Anzeige des Punktes
        plot3(0, gesamtsy, gesamtsz, 'or') %Anzeige des Punktes
        plot3([0,0], [gesamtsy, gesamtsy], [-500,30], '--r')%Linie zur vertikalen Projektion des Gesschwerpunktes
    else
        plot3(0, gesamtsy, gesamtsz, '*g') %Anzeige des Punktes
        plot3(0, gesamtsy, gesamtsz, 'og') %Anzeige des Punktes
        plot3([0,0], [gesamtsy, gesamtsy], [-500,30], '--g')%Linie zur vertikalen Projektion des Gesschwerpunktes
    end
        
    if(weiter == false)    
       % disp('Break')
       % disp(i)
        
      % break;
       % disp('Break2')
    end
    
   
    
    %Matrix für Simulation
    M(i) = getframe;
    
end

% ABspeichern der verbesserten Winkeltablle
csvwrite('winkeltablle_neu.csv', winkeltabelle.data);

%movie(M, 1, 5)
%save('movie1' , 'M');
%type('movie1.mat')
