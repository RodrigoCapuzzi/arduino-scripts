#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, use an unused pin
#define SS_2_PIN        8          // Configurable, use an unused pin

#define NR_OF_READERS   2
#define GREEN_PIN       6          // LED verde para o leitor 0
#define BLUE_PIN        7          // LED azul para o leitor 1
#define RED_PIN         5          // LED vermelho para leitura sequencial

byte ssPins[] = {SS_1_PIN, SS_2_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Cria uma instância para cada leitor

byte lastUID[4] = {0};            // Armazena o último UID lido
bool lastReader = -1;             // Armazena o último leitor que leu o cartão

void setup() {
  Serial.begin(9600);
  while (!Serial);

  SPI.begin(); 

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }

  // Configuração dos pinos dos LEDs
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
}

void loop() {
  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      Serial.print(F(": Card UID: "));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

      // Verifica se o cartão foi lido sequencialmente pelo mesmo leitor
      if (memcmp(lastUID, mfrc522[reader].uid.uidByte, 4) == 0 && lastReader == reader) {
        // Pisca o LED vermelho
        digitalWrite(RED_PIN, HIGH);
        delay(500);
        digitalWrite(RED_PIN, LOW);
      } else {
        if (reader == 0) {
          // Pisca o LED verde para o leitor 0
          digitalWrite(GREEN_PIN, HIGH);
          delay(500);
          digitalWrite(GREEN_PIN, LOW);
        } else if (reader == 1) {
          // Pisca o LED azul para o leitor 1
          digitalWrite(BLUE_PIN, HIGH);
          delay(500);
          digitalWrite(BLUE_PIN, LOW);
        }

        // Atualiza o último UID e o leitor ativo
        memcpy(lastUID, mfrc522[reader].uid.uidByte, 4);
        lastReader = reader;
      }

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    }
  }
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
