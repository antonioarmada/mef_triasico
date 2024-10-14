

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


int calcular_intesidad (int distancia, const int DISTS[4], int DIST_lenght, const int INTS[4], int velococidad)
{
  static int intensidad_temporal;
  int intensidad_target = 0;

  // uso est tipo de estructura en vez de un simple map porque no es lineal y prefiero
  // un control fácil de los parámetros
  // calculo la intensidad objetivo a la que quiero llegar, pero luego lo hago paulatinamete
  for(int i = 0; i < DIST_lenght; i++) 
  {
    if(distancia <= DISTS[i]) 
    {
      intensidad_target = INTS[i];
      break; 
    }
  }

  // ajusto la intenidad temporal para alcanzar de a poco la intensidad target
  if (intensidad_temporal < intensidad_target)
  {
    intensidad_temporal += velococidad;
  }
  else if (intensidad_temporal > intensidad_target && intensidad_temporal > 0)
  {
    intensidad_temporal -= velococidad;
  }

  return intensidad_temporal;
}



void setup()
{
  declaracion_pines();
  
  Serial.begin(115200);
  // espero un tiempo correspondiente con el nro de nodo
  // para informar que se inició correctamente, es un apaño
  // para que todos los nodos no hablen al mismo tiempo
  delay(ID_NODO * 10); // Dar tiempo al Serial para inicializarse  
  Serial.println("Iniciando dispositivo..."); 
  Serial.print("Soy el nodo: ");
  Serial.println(ID_NODO);

  // Intentar inicializar CAN - se bloqueará aquí si falla
  while (!inicio_CAN()) {
        Serial.println("Fallo en la inicialización CAN. El dispositivo no puede continuar.");
        delay(5000); // Esperar 5 segundos antes de reintentar
  }
    
  enviar_mensaje(ID_NODO + SUB_INICIADO, 0x01 );

  inicio_sensor_distancia();
 
}


void loop()
{
  static unsigned long ultima_activacion = 0;

  int distancia = medir_distancia(DISTANCIAS);
  int intensidad = calcular_intesidad(distancia, DISTANCIAS, TAMANO, INTENSIDADES, VELOCIDAD_LUCES);
  analogWrite(PIN_LUCES, intensidad);

  // aca hacer tambien que tengas que tener "presionado" un tiempo tambien, para filtrar un error
  // que aparece cada tanto (i2c cable largo?)
  if (distancia <= DISTANCIAS[0] && millis()-ultima_activacion > BOUNCING_TIME)
  {
    Serial.println ("******* ACTIVADO ******");
    enviar_mensaje(ID_NODO + SUB_ACTIVADO, 0x01 );
    ultima_activacion = millis();

  }

  delay(10);
}
