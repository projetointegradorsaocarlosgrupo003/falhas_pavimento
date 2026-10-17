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
intBuracos = intensidade(maskBuracos);
classBuracos = class(maskBuracos);

% Severidade acumulada
sevAcumulada = sum(intBuracos(classBuracos>=2));
fprintf('--- Severidade acumulada (médios+grandes): %.2f m/s² ---\n', sevAcumulada);

% Proporção médios+grandes
qtdMedioGrande = sum(classBuracos==2 | classBuracos==3);
percMedioGrande = (qtdMedioGrande/length(classBuracos))*100;
fprintf('--- Proporção de buracos médios+grandes: %.1f
