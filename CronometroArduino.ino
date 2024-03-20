#include <LiquidCrystal.h>

#define button1 2 // Botón para iniciar/pausar el cronómetro
#define button2 3 // Botón para resetear el cronómetro

// Define los pines de los LEDs
#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 1

int timerMode = 0; // 0 = Detenido, 1 = Corriendo
long lastTime = 0; // Almacena el último tiempo registrado cuando se pausa
long startTime = 0; // Tiempo de inicio después de pausas o al comenzar

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup(){
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  
  // Inicializa los pines de los LEDs como salida
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);
  
  lcd.print("CRONOMETRO KARTING");
}

void semaforo() {
  // Enciende cada LED con un intervalo de 1 segundo
  digitalWrite(LED1, HIGH);
  delay(1000);

  digitalWrite(LED2, HIGH);
  delay(1000);
 
  digitalWrite(LED3, HIGH);
  delay(1000);
  digitalWrite(LED4, HIGH);

  delay(2000);
    digitalWrite(LED4, LOW);
      digitalWrite(LED3, LOW);
        digitalWrite(LED2, LOW);
          digitalWrite(LED1, LOW);
}

void loop(){
  // Iniciar/pausar el cronómetro con button1
  static bool lastButton1State = HIGH;
  bool currentButton1State = digitalRead(button1);
  if (currentButton1State == LOW && lastButton1State == HIGH) {
    if (timerMode == 0) {
      // Activa el semáforo antes de iniciar
      semaforo();
      // Iniciar o reanudar
      startTime = millis();
      timerMode = 1; // Corriendo
    } else {
      // Pausar
      lastTime = millis() - startTime;
      timerMode = 0; // Detenido
    }
    delay(200); // Anti-rebote
  }
  lastButton1State = currentButton1State;

  // Resetear el cronómetro con button2
  static bool lastButton2State = HIGH;
  bool currentButton2State = digitalRead(button2);
  if (currentButton2State == LOW && lastButton2State == HIGH) {
    timerMode = 0; // Detiene el cronómetro
    lastTime = 0; // Resetea el tiempo acumulado
    lcd.clear();
    lcd.print("CRONOMETRO KART");
    lcd.setCursor(0, 1);
    lcd.print("0.00"); // Muestra 0 en pantalla después de resetear
    delay(200); // Debounce
  }
  lastButton2State = currentButton2State;

  // Mostrar tiempo
  if (timerMode == 1) {
    long currentTime = millis() - startTime;
    lcd.setCursor(0, 1);
    lcd.print(currentTime / 1000.0, 2);
  }
}
