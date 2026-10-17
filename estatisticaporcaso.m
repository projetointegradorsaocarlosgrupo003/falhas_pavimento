readAPIKey = 'ID';
channelID = ID;

[intensidade,timeStamp] = thingSpeakRead(channelID,'Fields',1,'NumPoints',60,'ReadKey',readAPIKey);

% Classificação
class = zeros(size(intensidade));
class(intensidade >= 11 & intensidade < 14) = 1; % Pequeno
class(intensidade >= 14 & intensidade < 18) = 2; % Medio
class(intensidade >= 18) = 3;                   % Grande

% Filtrar buracos
maskBuracos = class > 0;
intBuracos = intensidade(maskBuracos);
classBuracos = class(maskBuracos);

% Estatísticas
categorias = {'Pequeno','Medio','Grande'};
totalBuracos = length(classBuracos);

disp('--- Estatísticas por categoria (buracos) ---');
for c = 1:3
    if any(classBuracos==c)
        qtd = sum(classBuracos==c);
        perc = (qtd/totalBuracos)*100;
        fprintf('%s -> Média: %.2f | Min: %.2f | Max: %.2f | Qtde: %d | Percentual: %.1f%%\n', ...
            categorias{c}, mean(intBuracos(classBuracos==c)), ...
            min(intBuracos(classBuracos==c)), max(intBuracos(classBuracos==c)), qtd, perc);
    else
        fprintf('%s -> Nenhum evento registrado\n',categorias{c});
    end
end
