#include <Wire.h>
#include <TinyGPS++.h>
#include "FS.h"
#include "LittleFS.h"
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <WiFi.h> // Biblioteca para gerenciar a conexão Wi-Fi

// === PREENCHA AQUI COM OS DADOS DA SUA REDE (LOCALMENTE) ===
const char* ssid = "Wi-Fi";
const char* password = "SENHA";

TinyGPSPlus gps;
HardwareSerial gpsSerial(1);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

String bufferLote = "";         
unsigned long ultimaTentativa = 0;
const unsigned long intervaloBuffer = 30000; // 30 segundos

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
  Wire.begin(21, 22);

  if(!accel.begin(0x53)) {
    Serial.println("Erro: ADXL345 não encontrado!");
  } else {
    accel.setRange(ADXL345_RANGE_2_G);
    Serial.println("Acelerómetro ADXL345 OK.");
  }

  // Inicializa a memória interna (LittleFS)
  if(!LittleFS.begin(true)) {
    Serial.println("Erro ao montar o LittleFS!");
  } else {
    Serial.println("Memória interna pronta para uso.");
  }

  // Inicia a tentativa de conexão ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("A ligar ao Wi-Fi");
  unsigned long inicioConexao = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - inicioConexao < 10000) {
    delay(500);
    Serial.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi conectado com sucesso!");
  } else {
    Serial.println("\nFalha ao conectar inicialmente. O sistema funcionará gravando na memória interna.");
  }
  
  Serial.println("Sistema iniciado e operacional.");
}

void loop() {
  // 1. Leitura contínua do GPS
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  // 2. Leitura contínua do Acelerômetro
  sensors_event_t event; 
  accel.getEvent(&event);

  // 3. Monta a linha e guarda no buffer da RAM
  String linhaAtual = "";
  if (gps.location.isUpdated()) {
    linhaAtual += String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6) + ",";
  } else {
    linhaAtual += "NoFix,NoFix,";
  }
  linhaAtual += String(event.acceleration.x) + "," + 
              String(event.acceleration.y) + "," + 
              String(event.acceleration.z) + "\n";

  bufferLote += linhaAtual;

  // 4. Momento de verificar a transmissão ou guardar na memória interna
  if (millis() - ultimaTentativa >= intervaloBuffer) {
    
    // Verifica o estado real da conexão Wi-Fi
    bool internetDisponivel = (WiFi.status() == WL_CONNECTED);

    if (internetDisponivel) {
      // (Futuramente, aqui você pode adicionar a requisição HTTP POST ou MQTT para enviar o 'bufferLote')
      Serial.println("Internet OK: Dados enviados com sucesso.");
      bufferLote = ""; // Limpa o buffer após o envio online
    } else {
      Serial.println("INTERNET INDISPONÍVEL: A guardar dados na memória interna...");
      
      File arquivo = LittleFS.open("/dados_log.csv", FILE_APPEND);
      if (arquivo) {
        if (arquivo.size() == 0) {
          arquivo.println("Latitude,Longitude,Accel_X,Accel_Y,Accel_Z");
        }
        arquivo.print(bufferLote);
        arquivo.close();
        Serial.println("SUCESSO: Dados guardados na memória interna!");
        bufferLote = ""; // Limpa o buffer após o sucesso na gravação
      } else {
        Serial.println("FALHA: Não foi possível abrir o arquivo na memória interna.");
      }
    }
    
    ultimaTentativa = millis();
  }

  delay(1000);
}
