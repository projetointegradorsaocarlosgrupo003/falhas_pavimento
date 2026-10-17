#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

// ===== CONFIGURAÇÕES DO WIFI =====
const char* ssid = "SUA_REDE_WIFI";       // <-- coloque aqui o nome da sua rede
const char* password = "SUA_SENHA_WIFI";  // <-- coloque aqui a senha da sua rede

// ===== CONFIGURAÇÕES DO THINGSPEAK =====
String apiKey = "PFCIINLH1FNHND1F";   // Write API Key
String server = "http://api.thingspeak.com/update";
int channelID = 3339979;              // ID do canal

// ===== SENSORES =====
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
TinyGPSPlus gps;
HardwareSerial SerialGPS(2); // UART2: RX2=D16, TX2=D17

void setup() {
  Serial.begin(115200);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  // Inicializa sensores
  Wire.begin(21, 22); // I2C para ADXL345
  if (!accel.begin()) {
    Serial.println("Erro ao iniciar ADXL345!");
    while (1);
  }
  Serial.println("ADXL345 pronto!");

  SerialGPS.begin(9600, SERIAL_8N1, 16, 17); // GPS
}

void loop() {
  // ===== LEITURA DO ACELERÔMETRO =====
  sensors_event_t event;
  accel.getEvent(&event);
  float ax = event.acceleration.x;
  float ay = event.acceleration.y;
  float az = event.acceleration.z;

  // ===== LEITURA DO GPS =====
  double lat = 0.0, lon = 0.0;
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
    if (gps.location.isUpdated()) {
      lat = gps.location.lat();
      lon = gps.location.lng();
    }
  }

  // ===== ENVIO PARA THINGSPEAK =====
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = server + "?api_key=" + apiKey +
                 "&field1=" + String(lat, 6) +
                 "&field2=" + String(lon, 6) +
                 "&field3=" + String(ax, 2) +
                 "&field4=" + String(ay, 2) +
                 "&field5=" + String(az, 2);

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Dados enviados ao ThingSpeak!");
    } else {
      Serial.println("Falha ao enviar dados.");
    }
    http.end();
  }

  delay(20000); // ThingSpeak aceita 1 envio a cada 15 segundos (20s é seguro)
}
