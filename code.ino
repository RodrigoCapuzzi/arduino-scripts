#define BUTTON_ADD_PIN 10  // Pino do botão para adicionar bicicletas
#define BUTTON_REMOVE_PIN 11  // Pino do botão para remover bicicletas
#define LED_PIN 9  // Pino do LED
#define MAX_ESTOQUE 20 // Limite máximo de bicicletas no estoque

int estoque = 10;  // Quantidade inicial de bicicletas no estoque

void setup() {
  // Inicializa o serial monitor (opcional)
  Serial.begin(9600);
  
  // Configura os pinos
  pinMode(BUTTON_ADD_PIN, INPUT_PULLUP);
  pinMode(BUTTON_REMOVE_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Verifica se o botão de adicionar foi pressionado
  if (digitalRead(BUTTON_ADD_PIN) == LOW) {
    if (estoque < MAX_ESTOQUE) {
      estoque++;
      Serial.print("Bicicleta adicionada. Estoque atual: ");
      Serial.println(estoque);
      digitalWrite(LED_PIN, HIGH);  // Liga o LED para indicar sucesso
      delay(500);
      digitalWrite(LED_PIN, LOW);
    } else {
      Serial.println("Estoque cheio! Não é possível adicionar mais bicicletas.");
    }
    delay(300); // Pequeno delay para evitar múltiplas leituras
  }

  // Verifica se o botão de remover foi pressionado
  if (digitalRead(BUTTON_REMOVE_PIN) == LOW) {
    if (estoque > 0) {
      estoque--;
      Serial.print("Bicicleta removida. Estoque atual: ");
      Serial.println(estoque);
      digitalWrite(LED_PIN, HIGH);  // Liga o LED para indicar sucesso
      delay(500);
      digitalWrite(LED_PIN, LOW);
    } else {
      Serial.println("Estoque vazio! Não é possível remover bicicletas.");
    }
    delay(300); // Pequeno delay para evitar múltiplas leituras
  }
}
