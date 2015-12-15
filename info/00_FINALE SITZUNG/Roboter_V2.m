

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

for (i=1 : 1 : 90)
    
    clf
    
    %Einrichten des Fensters
    grid on
    ylabel('y')
    zlabel('z')
    title ('Roboter')
    axis([0 1 -200 500 -550 200])
    set(gca,'zdir', 'reverse') %Richtung der z-Achse umdrehen
    set(gca,'ydir', 'reverse') %Richtung der z-Achse umdrehen
    view(-90,0)
    hold on

    % Winkel
    alpha15 = winkeltabelle.data(i, 5);
    alpha14 = winkeltabelle.data(i, 4);
    alpha12 = -winkeltabelle.data(i, 2);
    alpha51 = winkeltabelle.data(i, 19);
    alpha31 = winkeltabelle.data(i, 13);
    alpha33 = winkeltabelle.data(i, 15)-90;
    % 1 x 6 Matrix für die Winkel
    winkel = [alpha15 alpha14 alpha12 alpha51 alpha31 alpha33];
     
    %eigentliche Transformation und Simulation - siehe simulation.m
    if(simulation(winkel, tparam, m0, sparam, gparam) == false) 
        disp('Break')
        disp(i)
       % disp('Break2')
    end
    
    
    %Matrix für Simulation
    M(i) = getframe;
    
end
%movie(M, 1, 5)
%save('movie1' , 'M');
%type('movie1.mat')
