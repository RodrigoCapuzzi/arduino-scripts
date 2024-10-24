#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1 9
#define SDA_PIN_1 10
#define RST_PIN_2 7
#define SDA_PIN_2 8

MFRC522 rfid1(SDA_PIN_1, RST_PIN_1);
MFRC522 rfid2(SDA_PIN_2, RST_PIN_2);

// RGB LED Pins (PWM pins)
int redPin = 5;
int greenPin = 6;
int bluePin = 3;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  
  // Initialize RFID readers
  Serial.println(F("Iniciando RFID 1..."));
  rfid1.PCD_Init();
  if (!rfid1.PCD_PerformSelfTest()) {
    Serial.println(F("RFID 1 falhou no self-test!"));
  } else {
    Serial.println(F("RFID 1 iniciado com sucesso!"));
  }

  Serial.println(F("Iniciando RFID 2..."));
  rfid2.PCD_Init();
  if (!rfid2.PCD_PerformSelfTest()) {
    Serial.println(F("RFID 2 falhou no self-test!"));
  } else {
    Serial.println(F("RFID 2 iniciado com sucesso!"));
  }
  
  // Initialize RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Turn off LED at the start
  turnOffLed();
}

void loop() {
  // Adicionando delay de 2 segundos no loop
  delay(2000);
  Serial.println(F("Novo loop"));

  // Check RFID Reader 1
  if (rfid1.PICC_IsNewCardPresent() && rfid1.PICC_ReadCardSerial()) {
    Serial.println("RFID 1 Tag detected");
    setColor(255, 0, 0); // Set RGB LED to Red for RFID reader 1
    delay(1000);  // Keep LED on for 1 second
    turnOffLed();
    rfid1.PICC_HaltA();
  } else {
    Serial.println(F("Nenhuma tag detectada pelo RFID 1."));
  }

  // Check RFID Reader 2
  if (rfid2.PICC_IsNewCardPresent() && rfid2.PICC_ReadCardSerial()) {
    Serial.println("RFID 2 Tag detected");
    setColor(0, 255, 0); // Set RGB LED to Green for RFID reader 2
    delay(1000);  // Keep LED on for 1 second
    turnOffLed();
    rfid2.PICC_HaltA();
  } else {
    Serial.println(F("Nenhuma tag detectada pelo RFID 2."));
  }
}

// Function to set the RGB LED color
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

// Function to turn off the RGB LED
void turnOffLed() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}
