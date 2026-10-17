% ===== Configurações do Canal =====
channelID = id; 
readAPIKey = 'SUA_READ_API_KEY'; % substitua pela sua chave de leitura

% ===== Ler os últimos 100 pontos =====
[data, time] = thingSpeakRead(channelID, ...
    'NumPoints', 100, ...
    'ReadKey', readAPIKey);

% ===== Separar os campos =====
latitude  = data(:,1);   % Field 1
longitude = data(:,2);   % Field 2
accelX    = data(:,3);   % Field 3
accelY    = data(:,4);   % Field 4
accelZ    = data(:,5);   % Field 5

% ===== Gráficos das acelerações =====
figure;
subplot(3,1,1);
plot(time, accelX, 'r'); title('Aceleração X'); ylabel('m/s^2');

subplot(3,1,2);
plot(time, accelY, 'g'); title('Aceleração Y'); ylabel('m/s^2');

subplot(3,1,3);
plot(time, accelZ, 'b'); title('Aceleração Z'); ylabel('m/s^2');
xlabel('Tempo');

% ===== Estatísticas simples =====
stdX = std(accelX);
stdY = std(accelY);
stdZ = std(accelZ);

fprintf('Desvio padrão X: %.2f\n', stdX);
fprintf('Desvio padrão Y: %.2f\n', stdY);
fprintf('Desvio padrão Z: %.2f\n', stdZ);

% ===== Mapa de São Carlos com vibração =====
figure;
geoscatter(latitude, longitude, 50, accelZ, 'filled');
title('Mapa de São Carlos - Vibração no Pavimento');
colorbar;
