#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();


int DISTANCIA_MAX = 1800;

const int ledPin = 9;               // Pin del LED conectado a la salida PWM
int brilloActual = 0;              // Brillo actual del LED
int distancia = 0;                // Brillo actual del LED



long mapInverse(long x, long in_min, long in_max, long out_min, long out_max) {
  return (out_max - (x - in_min) * (out_max - out_min) / (in_max - in_min));
}



void setup() {

  pinMode(ledPin, OUTPUT);
    
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();
}

void loop() {
  if (lox.isRangeComplete()) {
    distancia = lox.readRange();
    brilloActual = mapInverse(distancia, 0, 1023, 0, 255);

    Serial.print("Distance in mm: ");
    Serial.print(distancia);
    Serial.print(" - PWM: ");
    Serial.println(brilloActual);

    // Escribimos el valor de brillo en el LED
    analogWrite(ledPin, brilloActual);

    // Pequeño retardo para estabilizar la actualización del brillo
    delay(10);

  }
}