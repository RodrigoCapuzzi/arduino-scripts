#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define RED_PIN 5
#define GREEN_PIN 6

MFRC522 rfid(SS_PIN, RST_PIN); // Instância da classe

// Array para armazenar novo NUID 
byte nuidPICC[4];

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Inicia o barramento SPI
  rfid.PCD_Init(); // Inicia o MFRC522

  // Configuração dos pinos do LED
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  Serial.println(F("This code scans the MIFARE Classic NUID."));
}
 
void loop() {
  // Reseta o loop se nenhum novo cartão estiver presente no leitor.
  if (!rfid.PICC_IsNewCardPresent()) return;

  // Verifica se o NUID foi lido
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Verifica se o PICC é do tipo MIFARE Classic
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
      rfid.uid.uidByte[1] != nuidPICC[1] || 
      rfid.uid.uidByte[2] != nuidPICC[2] || 
      rfid.uid.uidByte[3] != nuidPICC[3] ) {

    Serial.println(F("A new card has been detected."));
    
    // Pisca o LED verde
    digitalWrite(GREEN_PIN, HIGH);
    delay(500); // LED aceso por 500 ms
    digitalWrite(GREEN_PIN, LOW);

    // Armazena o NUID no array nuidPICC
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else {
    Serial.println(F("Card read previously."));

    // Pisca o LED vermelho
    digitalWrite(RED_PIN, HIGH);
    delay(500); // LED aceso por 500 ms
    digitalWrite(RED_PIN, LOW);
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Função auxiliar para imprimir um array de bytes em valores hexadecimais no Serial.
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Função auxiliar para imprimir um array de bytes em valores decimais no Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(' ');
    Serial.print(buffer[i], DEC);
  }
}
