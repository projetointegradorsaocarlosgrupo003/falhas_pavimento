#include "FS.h"
#include "SD.h"
#include "SPI.h"

void setup() {
  Serial.begin(115200);
  
  // Inicializa o cartão SD usando o barramento SPI padrão
  if(!SD.begin()){
    Serial.println("Falha na montagem do Cartão SD!");
    return;
  }
  
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    Serial.println("Nenhum cartão SD inserido.");
    return;
  }

  Serial.print("Tipo de Cartão SD: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("DESCONHECIDO");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("Tamanho do Cartão: %llu MB\n", cardSize);
  
  Serial.println("Teste do micro SD concluído com sucesso!");
}

void loop() {
  // Nada por enquanto
}
