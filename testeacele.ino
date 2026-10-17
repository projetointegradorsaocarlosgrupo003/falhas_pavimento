/*
 * ============================================================================
 * PROJETO INTEGRADOR UNIVESP - FALHAS NO PAVIMENTO (SÃO CARLOS - SP)
 * Arquivo: teste_sensores.ino (pasta /firmware)
 * Descrição: Validação e calibração do acelerômetro triaxial ADXL345 via I2C.
 * Placa: ESP32 DevKit v1
 * ============================================================================
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Atribuição de ID único ao sensor */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    ; // Aguarda a inicialização da porta serial
  }

  Serial.println("==================================================");
  Serial.println("  UNIVESP - Teste de Bancada: Acelerometro ADXL345");
  Serial.println("==================================================");

  /* Inicializa o barramento I2C e o sensor ADXL345 */
  if (!accel.begin()) {
    Serial.println("[ERRO] ADXL345 nao detectado! Verifique as conexoes SDA/SCL.");
    while (1);
  }

  /* Ajusta a faixa de medição para +/- 16g (recomendado para impactos viários) */
  accel.setRange(ADXL345_RANGE_16_G);
  
  Serial.println("[OK] Sensor ADXL345 inicializado com sucesso.");
  Serial.println("Faixa configurada: +/- 16g");
  Serial.println("Iniciando leitura dos eixos (foco no Eixo Z)...");
  Serial.println("--------------------------------------------------");
}

void loop(void) {
  /* Obtém um novo evento do sensor */
  sensors_event_t event;
  accel.getEvent(&event);

  /* Leituras em m/s² */
  float accelX = event.acceleration.x;
  float accelY = event.acceleration.y;
  float accelZ = event.acceleration.z; // Eixo vertical de interesse principal

  /* Impressão dos dados no Monitor Serial */
  Serial.print("Eixo X: ");
  Serial.print(accelX, 2);
  Serial.print(" m/s² | ");

  Serial.print("Eixo Y: ");
  Serial.print(accelY, 2);
  Serial.print(" m/s² | ");

  Serial.print("Eixo Z (Impacto Vertical): ");
  Serial.print(accelZ, 2);
  Serial.println(" m/s²");

  /* Intervalo entre amostragens de bancada (100 ms = 10 Hz) */
  delay(100);
}
