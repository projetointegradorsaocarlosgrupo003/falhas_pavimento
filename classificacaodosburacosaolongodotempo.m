readAPIKey = 'id';
channelID = id;

[intensidade,timeStamp] = thingSpeakRead(channelID,'Fields',1,'NumPoints',60,'ReadKey',readAPIKey);

class = zeros(size(intensidade));
class(intensidade >= 11 & intensidade < 14) = 1;
class(intensidade >= 14 & intensidade < 18) = 2;
class(intensidade >= 18) = 3;

maskBuracos = class > 0;
plot(timeStamp(maskBuracos),class(maskBuracos),'s-','LineWidth',1.5);
yticks([1 2 3]);
yticklabels({'Pequeno','Medio','Grande'});
xlabel('Tempo');
ylabel('Classificação');
title('Classificação dos buracos ao longo do tempo');
grid on;
