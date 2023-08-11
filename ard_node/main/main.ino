#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Configuraciones
const int DIST_MAX = 1800;
const int DIST_MIN = 30;
const int PWM_MIN = 0;
const int PWM_MAX = 255;
const int VELOCIDAD = 3;

// Pines
const int PIN_LUCES = 9;  
const int ledPin = LED_BUILTIN; // 13 en casi todos los Arduinos

// Declaraciones
int ledValue = 0;
int targetLedValue = 0;
int distancia_rm = 0;

void setup() {

  Serial.begin(115200);

  if(!lox.begin()){
    Serial.println("Failed to boot sensor");
    while(1);
  }

  lox.startRangeContinuous();
  
  pinMode(PIN_LUCES, OUTPUT);
  pinMode(ledPin, OUTPUT);

}

void loop() {

  if (lox.isRangeComplete()) {
    
    int distance = lox.readRange();

    if (distance > DIST_MAX) {
      distance = DIST_MAX;
    }

    if (distance <= DIST_MIN) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    // remapea la distancia a un valor entre 0 y 255 para comprarlo con el pwm
    distancia_rm = map(distance, DIST_MIN , DIST_MAX , PWM_MIN, PWM_MAX );
    
    // Calcular valor deseado de intensidad LED
    targetLedValue = 255 - distancia_rm;
    
    // Ajustar intensidad LED a velocidad constante    
    if(ledValue < targetLedValue){
      ledValue += VELOCIDAD ;  
    } else if(ledValue > targetLedValue && ledValue > 0){
      ledValue -= VELOCIDAD; 
    } 

    Serial.print("d: ");
    Serial.print(distance);
    Serial.print(" drm: ");
    Serial.print(distancia_rm);
    Serial.print(" trg: ");
    Serial.print(targetLedValue);
    Serial.print(" pwm: ");
    Serial.println(ledValue);
    
    
    analogWrite(PIN_LUCES, ledValue);
  
  }
  
}