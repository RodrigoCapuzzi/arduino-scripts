#include <SPI.h>
#include <MFRC522.h>
#include <ConfigurableFirmata.h> // Biblioteca ConfigurableFirmata para integração com o Node-RED

#define RST_PIN         9
#define SS_1_PIN        10
#define SS_2_PIN        8

#define NR_OF_READERS   2
#define GREEN_PIN       6
#define BLUE_PIN        7
#define RED_PIN         5

byte ssPins[] = {SS_1_PIN, SS_2_PIN};
MFRC522 mfrc522[NR_OF_READERS];

byte lastUID[4] = {0};
bool lastReader = -1;

void setup() {
  Serial.begin(9600); // Comunicação Serial com o Node-RED
  SPI.begin();
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
  }

  // Configuração dos LEDs
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      
      // Iniciar a mensagem JSON
      Serial.print("{");

      if (reader == 0) {
        Serial.print("\"tipo_leitura\": \"Entrada no estoque\"");
      } else if (reader == 1) {
        Serial.print("\"tipo_leitura\": \"Saída do estoque\"");
      }

      Serial.print(", \"bike_id\": \"");
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.print("\"");

      if (memcmp(lastUID, mfrc522[reader].uid.uidByte, 4) == 0 && lastReader == reader) {
        digitalWrite(RED_PIN, HIGH);
        delay(500);
        Serial.print(", \"status\": \"Erro de leitura\"");
        digitalWrite(RED_PIN, LOW);
      } else {
        digitalWrite(reader == 0 ? GREEN_PIN : BLUE_PIN, HIGH);
        delay(500);
        Serial.print(", \"status\": \"Sucesso na leitura\"");
        digitalWrite(reader == 0 ? GREEN_PIN : BLUE_PIN, LOW);

        memcpy(lastUID, mfrc522[reader].uid.uidByte, 4);
        lastReader = reader;
      }

      // Fechar a mensagem JSON
      Serial.println("}");

      mfrc522[reader].PICC_HaltA();
      mfrc522[reader].PCD_StopCrypto1();
    }
  }
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    if (buffer[i] < 0x10) Serial.print("0");
    Serial.print(buffer[i], HEX);
  }
}
