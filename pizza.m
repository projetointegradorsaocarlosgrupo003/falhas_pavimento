readChannelID = id;
readAPIKey = 'id';

dataClass = thingSpeakRead(readChannelID,'Field',4,'NumPoints',60,'ReadKey',readAPIKey);

counts = [sum(dataClass==1), sum(dataClass==2), sum(dataClass==3)];

pie(counts, {'Pequenos','Médios','Grandes'});
title('Distribuição percentual dos buracos');

% Paleta consistente
colormap([0.2 0.6 0.8; 0.9 0.6 0.2; 0.6 0.2 0.8]);
