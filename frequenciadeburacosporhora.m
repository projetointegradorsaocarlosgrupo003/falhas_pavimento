readAPIKey = 'id';
channelID = id;

[intensidade,timeStamp] = thingSpeakRead(channelID,'Fields',1,'NumPoints',60,'ReadKey',readAPIKey);

% Classificação
class = zeros(size(intensidade));
class(intensidade >= 11 & intensidade < 14) = 1;
class(intensidade >= 14 & intensidade < 18) = 2;
class(intensidade >= 18) = 3;

% Filtrar buracos
maskBuracos = class > 0;
timeBuracos = timeStamp(maskBuracos);

% Frequência por hora
horas = hour(timeBuracos);
uniqueHoras = unique(horas);

disp('--- Frequência de buracos por hora ---');
for h = uniqueHoras'
    fprintf('Hora %02d -> %d buracos\n', h, sum(horas==h));
end
