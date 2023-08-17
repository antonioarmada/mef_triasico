#include "Adafruit_VL53L0X.h"

// Construyo lo necesario
Adafruit_VL53L0X lox = Adafruit_VL53L0X();


void inicio_sensor_distancia ()
{
  bool arranca = true;
    while (arranca)
    {
      digitalWrite(LED, LOW);
      if (!lox.begin())
      {
        Serial.println("Fallo al iniciar el VL53L0X");
        enviar_mensaje(ID_NODO+ID_ERROR, 1);
        digitalWrite(LED, HIGH);
        delay(2000);
      }
      else
      {
        arranca = false;
        lox.startRangeContinuous();
        Serial.println("VL53L0X iniciado correctamente");
      }
    }
}

int medir_distancia(const int DIST[4])  // mide la distancia, en out of range devuelve la distancia maxima definida en config.h
{
  VL53L0X_RangingMeasurementData_t measure;
  int distancia;
    
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) // phase failures have incorrect data
  {  
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    distancia = measure.RangeMilliMeter;
  } 
  else 
  {
    Serial.println(" out of range ");
    distancia = DIST[3];
  }
  return distancia;
}