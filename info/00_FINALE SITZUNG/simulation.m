function weiter = simulation(winkel, tparam, m0, sparam, gparam)
    weiter = true;
    mLast = m0;
    mi = m0;
    gesamtWinkel = 0;
    %Fuß
    line([0, 0], [-55, 105], [0, 0]);
    
    %Schwerpunktkoordinaten in z- und y-Richtung
    sy = [0 0 0 0 0 0 0];
    sz = [0 0 0 0 0 0 0];
    
    for(i = 1 : 1 : 7)
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
        
        if (mi(3) > 45) weiter = false; end
        
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
        %plot3(0, gesamtsy, gesamtsz, '*r') %Anzeige des Punktes
        %plot3(0, gesamtsy, gesamtsz, 'or') %Anzeige des Punktes
        %plot3([0,0], [gesamtsy, gesamtsy], [-500,30], '--r')%Linie zur vertikalen Projektion des Gesschwerpunktes
    else
        %plot3(0, gesamtsy, gesamtsz, '*g') %Anzeige des Punktes
        %plot3(0, gesamtsy, gesamtsz, 'og') %Anzeige des Punktes
        %plot3([0,0], [gesamtsy, gesamtsy], [-500,30], '--g')%Linie zur vertikalen Projektion des Gesschwerpunktes
    end
       
end