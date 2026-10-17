readChannelID = id;
readAPIKey = 'id';

dataClass = thingSpeakRead(readChannelID,'Field',4,'NumPoints',60,'ReadKey',readAPIKey);

counts = [sum(dataClass==1), sum(dataClass==2), sum(dataClass==3)];

bar(counts,'FaceColor','flat');
set(gca,'XTickLabel',{'Pequenos','Médios','Grandes'});
title('Proporção acumulada de buracos');
ylabel('Quantidade acumulada');

% Aplicar paleta
colormap([0.2 0.6 0.8; 0.9 0.6 0.2; 0.6 0.2 0.8]);
