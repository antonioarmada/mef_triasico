
// es importante el orden en que se importan
// por ejmplo, distancia.h usa una func. de comunicacion.h
// por eso lo defino antes
#include "config.h"
#include "comunicacion.h"
#include "distancia.h"


void declaracion_pines()
{
  pinMode(PIN_LUCES, OUTPUT);
  pinMode(LED, OUTPUT);
}


int intendidad_luces () // ES CUALQUIER REESCRIBIR, ES UN EJEMPLO ANTERIOR
{
  /* // remapea la distancia a un valor entre 0 y 255 para comprarlo con el pwm
  distancia_rm = map(distance, DIST_MIN, DIST_MAX, PWM_MIN, PWM_MAX);

  // Calcular valor deseado de intensidad LED
  targetLedValue = 255 - distancia_rm;

  // Ajustar intensidad LED a velocidad constante
  if (ledValue < targetLedValue)
  {
    ledValue += VELOCIDAD;
  }
  else if (ledValue > targetLedValue && ledValue > 0)
  {
    ledValue -= VELOCIDAD;
  } */
  return 0;
}


void setup()
{
  Serial.begin(115200);

  declaracion_pines();
  inicio_sensor_distancia();
  inicio_CAN();

  Serial.print("Soy el nodo: ");
  Serial.println(ID_NODO);

  enviar_mensaje(ID_NODO+1, 0x01 );
}

void loop()
{
int distancia = medir_distancia();
Serial.println (distancia);
delay (1000);
enviar_mensaje(ID_NODO+1, 0x01 );
}



