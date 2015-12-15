
% fig1=figure(1);
% winsize(1:2) = [0 0]; % Test für Movie
% A=moviein(135,fig1,winsize);
% set(fig1,'NextPlot','replacechildren')*/

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

% Winkel importieren
winkeltabelle = importdata('MATLAB\winkel_st_3.csv','\t', 1);

% Spalten der Motoren
spalten1 = [5 4 2 19 13 15];

% flüssigeres Hinsetzen
anfangszeile1 = 19;
endzeile1 = 24;

% 
anfangszeile2 = 25;
endzeile2 = 40;

% 
anfangszeile3 = 41;
endzeile3 = 49;


% 
anfangszeile4 = 50;
endzeile4 = 59;

% 
anfangszeile7 = 60;
endzeile7 = 71;

% 
anfangszeile8 = 72;
endzeile8 = 95;

% flüssigeres Aufrichten ganz zum Schluss
anfangszeile9 = 98;
endzeile9 = 137;


dif1 = [0 0 0 0 0 0 0];
dif2 = [0 0 0 0 0 0 0];
dif3 = [0 0 0 0 0 0 0];
dif4 = [0 0 0 0 0 0 0];
dif7 = [0 0 0 0 0 0 0];
dif8 = [0 0 0 0 0 0 0];
dif9 = [0 0 0 0 0 0 0];
   
% Schrittweite zur Glättung/ flüssige Bewegung, Schleife für einzelne Spalte
for(i = 1 : 1 : 6)
	dif1(i) = (winkeltabelle.data(endzeile1, spalten1(i)) - winkeltabelle.data(anfangszeile1, spalten1(i))) / (endzeile1 - anfangszeile1);
	dif2(i) = (winkeltabelle.data(endzeile2, spalten1(i)) - winkeltabelle.data(anfangszeile2, spalten1(i))) / (endzeile2 - anfangszeile2);
	dif3(i) = (winkeltabelle.data(endzeile3, spalten1(i)) - winkeltabelle.data(anfangszeile3, spalten1(i))) / (endzeile3 - anfangszeile3);
	dif4(i) = (winkeltabelle.data(endzeile4, spalten1(i)) - winkeltabelle.data(anfangszeile4, spalten1(i))) / (endzeile4 - anfangszeile4);
	dif7(i) = (winkeltabelle.data(endzeile7, spalten1(i)) - winkeltabelle.data(anfangszeile7, spalten1(i))) / (endzeile7 - anfangszeile7);
	dif8(i) = (winkeltabelle.data(endzeile8, spalten1(i)) - winkeltabelle.data(anfangszeile8, spalten1(i))) / (endzeile8 - anfangszeile8);
	dif9(i) = (winkeltabelle.data(endzeile9, spalten1(i)) - winkeltabelle.data(anfangszeile9, spalten1(i))) / (endzeile9 - anfangszeile9);
end

 
    
for (k = 1 : 1 : 138)


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

    %flüssigeres Aufrichten am Ende (schrittweise ändern der Winkel)

     if (k > anfangszeile1 && k <= endzeile1)

	% verbesserte Winkel für flüssiges Aufstehen in Tabelle schreiben
	for(i = 1 : 1 : 6)
	        winkeltabelle.data(k, spalten1(i)) = winkeltabelle.data(k-1, spalten1(i)) + dif1(i);		
	end

     end

     if (k > anfangszeile2 && k <= endzeile2)

	% verbesserte Winkel für flüssiges Aufstehen in Tabelle schreiben
	for(i = 1 : 1 : 6)
	        winkeltabelle.data(k, spalten1(i)) = winkeltabelle.data(k-1, spalten1(i)) + dif2(i);	
	end

     end

     if (k > anfangszeile3 && k <= endzeile3)

	% verbesserte Winkel für flüssiges Aufstehen in Tabelle schreiben
	for(i = 1 : 1 : 6)
	        winkeltabelle.data(k, spalten1(i)) = winkeltabelle.data(k-1, spalten1(i)) + dif3(i);		
	end
         
     end

     if (k > anfangszeile4 && k <= endzeile4)

	% verbesserte Winkel für flüssiges Aufstehen in Tabelle schreiben
	for(i = 1 : 1 : 6)
	        winkeltabelle.data(k, spalten1(i)) = winkeltabelle.data(k-1, spalten1(i)) + dif4(i);		
	end

     end

     if (k > anfangszeile7 && k <= endzeile7)

	% verbesserte Winkel für flüssiges Aufstehen in Tabelle schreiben
	for(i = 1 : 1 : 6)
	        winkeltabelle.data(k, spalten1(i)) = winkeltabelle.data(k-1, spalten1(i)) + dif7(i);		
	end
         
     end

     if (k > anfangszeile8 && k <= endzeile8)

	% verbesserte Winkel für flüssiges Aufstehen in Tabelle schreiben
	for(i = 1 : 1 : 6)
	        winkeltabelle.data(k, spalten1(i)) = winkeltabelle.data(k-1, spalten1(i)) + dif8(i);		
	end
         
     end

     if (k > anfangszeile9 && k <= endzeile9)

	% verbesserte Winkel für flüssiges Aufstehen in Tabelle schreiben
	for(i = 1 : 1 : 6)
	        winkeltabelle.data(k, spalten1(i)) = winkeltabelle.data(k-1, spalten1(i)) + dif9(i);		
	end
         
     end

     % entsprechende Winkel am anderen Bein
     winkeltabelle.data(k, 11) = - winkeltabelle.data(k, 5);
     winkeltabelle.data(k, 10) = - winkeltabelle.data(k, 4);
     winkeltabelle.data(k, 8) = winkeltabelle.data(k, 2);
     winkeltabelle.data(k, 16) = - winkeltabelle.data(k, 13);
     winkeltabelle.data(k, 18) = - winkeltabelle.data(k, 15);
    

    
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
                
       %Abspeichern der Schwerpunktkoordinaten zur späteren Berechnung des
       %Ges.Schwerpunktes
        sy(i)= si(2);
        sz(i)= si(3);
               
        mi = [mi(1)+t(1) ; mi(2)+t(2) ; mi(3)+t(3); 1]; %Vektoraddition: transformierte Vektoren werden zum vorherigen Vektor mx addiert
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
            winkeltabelle.data(k, 5) = winkel(1); % Korrektur der Winkel in der Winkeltablle
            winkeltabelle.data(k, 11) = -winkel(1);
            if (winkel(1) > 85) 
                disp('Achtung')
            end
            i=0;
            
             
           %zurücksetzen aller Anfangswerte
            mLast = m0;
            mi = m0;
            gesamtWinkel = 0;

            %Gelenkpunkte (Koordinaten) in z- und y-Richtung
            my = [0 0 0 0 0 0 0];
            mz = [0 0 0 0 0 0 0];

            %Schwerpunktkoordinaten in z- und y-Richtung
            sy = [0 0 0 0 0 0 0];
            sz = [0 0 0 0 0 0 0];
   
        end
               
         i = i + 1;
        
    end
   

    % Gesamtschwerpunkt berechnen mit Schwerpunktgleichung
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
	% Schwerpunkt nicht über den Füßen
    if (gesamtsy < -55 || gesamtsy > 105)
        plot3(0, gesamtsy, gesamtsz, '*r') %Anzeige des Punktes
        plot3(0, gesamtsy, gesamtsz, 'or') %Anzeige des Punktes
        plot3([0,0], [gesamtsy, gesamtsy], [-500,30], '--r')%Linie zur vertikalen Projektion des Gesschwerpunkte
	% Schwerpunkt über den Füßen
    else
        plot3(0, gesamtsy, gesamtsz, '*g') % Anzeige des Punktes
        plot3(0, gesamtsy, gesamtsz, 'og') % Anzeige des Punktes
        plot3([0,0], [gesamtsy, gesamtsy], [-500,30], '--g') % Linie zur vertikalen Projektion des Gesschwerpunktes
    end

	% Überprüfung, ob Hände auf dem Boden sind, wenn möglich, auf den Boden setzen; Anfang ausgenommen
	if (mz(7) < 0 && k > 11)
		disp('z-Koordinate 6 & 7: ')
		if(-mz(6)/thand <= 1) 
			winkel(6) = acos(-mz(6)/thand) * 180 / pi;
			winkeltabelle.data(k, 15) = winkel(6) + 90;
			winkeltabelle.data(k, 18) = -winkeltabelle.data(k, 15);

            		% Berechnung der neuen Koordinate für die Hand
			my(7) = my(6) + sqrt(thand * thand - mz(6) * mz(6));
			
			mz(6)
			mz(7)

		% wenn Hände nicht mehr bis auf denBoden kommen, Hände ausstrecken; letzte Position ausgenommen
		else 
			if(k < 138)
				winkel(6) = 0;
				winkeltabelle.data(k, 15) = winkel(6) + 90;
				winkeltabelle.data(k, 18) = -winkeltabelle.data(k, 15);		
			end
			
			mz(6)
			mz(7)
		end

		% Berechnung des Schwerpunnktes für die Hand
		sy(7) = my(6) + sin(winkel(6) * pi / 180) * sparam(7);
		sz(7) = mz(6) + cos(winkel(6) * pi / 180) * sparam(7);
		
	end


	% Plotten
	for(i = 1 : 1 : 7) 
		% Anzeige der Schwerpunkte
		plot3(0, sy(i), sz(i), '.r');
		% Anzeigen der Gelenkpunkte
		plot3(0, my(i), mz(i), '.');
		% Linie zwischen den Gelenkpunkten
		if(i == 1)
			% Linie vom Ursprung zu, Fußgelenk 
			line([0, 0], [0, my(1)], [0, mz(1)]);
		else 
			% Linie zwischen den Gelenken
			line([0, 0], [my(i - 1), my(i)], [mz(i - 1), mz(i)]);
		end
		% Fuß
            	line([0, 0], [-55, 105], [0, 0]);
	end
        
    if(weiter == false)    
       % disp('Break')
       % disp(i)
        
      % break;
       % disp('Break2')
    end
    
   
    
    %Matrix für Simulation
    M(i) = getframe;
   % A(:,i)=getframe(fig1,winsize); 
   
    if(k == 59) 
        % winkeltabelle.data(k, 15)
        % break; 
    end
end



% movie(M,1,5)
 %save('movie1' , 'M');
 %type('movie1.mat')
 %mpgwrite(M,jet,'movie1.mpg');

% ABspeichern der verbesserten Winkeltablle
csvwrite('winkeltabelle_verbessert_1.csv', winkeltabelle.data);
