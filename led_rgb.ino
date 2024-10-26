// Pinos do LED RGB (PWM)
int redPin = 5;
int greenPin = 6;
int bluePin = 3;

void setup() {
  Serial.begin(9600);

  // Inicializa os pinos do LED RGB como saídas
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.println(F("Iniciando teste do LED RGB..."));
}

void loop() {
  Serial.println("LED: Vermelho");
  setColor(255, 0, 0);  // Vermelho
  delay(1000);

  Serial.println("LED: Verde");
  setColor(0, 255, 0);  // Verde
  delay(1000);

  Serial.println("LED: Azul");
  setColor(0, 0, 255);  // Azul
  delay(1000);

  Serial.println("LED: Desligado");
  turnOffLed();
  delay(1000);
}

// Função para definir a cor do LED RGB
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

// Função para desligar o LED RGB
void turnOffLed() {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}
