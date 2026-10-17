% Mapa de calor de buracos por hora

readChannelID = id;
readAPIKey = 'id';

[dataClass,timeStamps] = thingSpeakRead(readChannelID,'Field',4,'NumPoints',60,'ReadKey',readAPIKey);

hours = hour(timeStamps);
heatData = zeros(24,3);

for h=0:23
    heatData(h+1,1) = sum(dataClass(hours==h)==1);
    heatData(h+1,2) = sum(dataClass(hours==h)==2);
    heatData(h+1,3) = sum(dataClass(hours==h)==3);
end

imagesc(heatData);
colormap(jet);
colorbar;
xlabel('Categoria (1=Pequeno, 2=Médio, 3=Grande)');
ylabel('Hora do dia');
title('Mapa de calor de buracos por hora');
