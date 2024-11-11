#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pines para LEDs
const int ledVerde = 8;
const int ledAmarillo = 9;
const int ledRojo = 10;

void setup() {
  // Inicialización de la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("No se encuentra OLED"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Configuración de los LEDs
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  Serial.begin(9600); // Iniciar Serial para depuración
}

void loop() {
  // Leer nivel de ruido del micrófono
  int nivelRuido = analogRead(A0);

  // Mostrar nivel de ruido en la pantalla OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Nivel de Ruido:");
  display.setCursor(0, 20);
  display.print(nivelRuido);
  display.display();

  // Encender LEDs según el nivel de ruido
  if (nivelRuido < 300) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, LOW);
  } else if (nivelRuido < 600) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, HIGH);
    digitalWrite(ledRojo, LOW);
  } else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarillo, LOW);
    digitalWrite(ledRojo, HIGH);
  }

  delay(500);  // Actualizar cada medio segundo
}