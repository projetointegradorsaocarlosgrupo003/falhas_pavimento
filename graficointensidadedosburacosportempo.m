readAPIKey = 'id';
channelID = id;

[intensidade,timeStamp] = thingSpeakRead(channelID,'Fields',1,'NumPoints',60,'ReadKey',readAPIKey);

class = zeros(size(intensidade));
class(intensidade >= 11 & intensidade < 14) = 1;
class(intensidade >= 14 & intensidade < 18) = 2;
class(intensidade >= 18) = 3;

maskBuracos = class > 0;
plot(timeStamp(maskBuracos),intensidade(maskBuracos),'-o','LineWidth',1.5);
xlabel('Tempo');
ylabel('Intensidade (m/s²)');
title('Intensidade dos buracos ao longo do tempo');
grid on;
