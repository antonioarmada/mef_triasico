const int ledPin = 9;               // Pin del LED conectado a la salida PWM
const int MAX_LATIDO_LUZ = 255;     // Valor máximo de brillo del LED
const int DURACION_CICLO = 8000;    // Duración total del ciclo en milisegundos (8 segundos)
const int DURACION_INHALACION = 2000; // Duración de la inhalación en milisegundos (2 segundos)
const int DURACION_PAUSA = 4000;    // Duración de la pausa en milisegundos (4 segundos)

unsigned long inicioCiclo;         // Tiempo de inicio del ciclo
int brilloActual = 0;              // Brillo actual del LED

void setup() {
  pinMode(ledPin, OUTPUT);
  inicioCiclo = millis();          // Inicializamos el tiempo de inicio del ciclo
}

void loop() {
  unsigned long tiempoActual = millis();  // Obtenemos el tiempo actual

  // Calculamos el tiempo transcurrido desde el inicio del ciclo
  unsigned long tiempoTranscurrido = tiempoActual - inicioCiclo;

  if (tiempoTranscurrido <= DURACION_INHALACION) {
    // En fase de inhalación, aumentamos el brillo suavemente
    brilloActual = map(tiempoTranscurrido, 0, DURACION_INHALACION, 0, MAX_LATIDO_LUZ);
  } else if (tiempoTranscurrido <= DURACION_INHALACION + DURACION_PAUSA) {
    // En fase de pausa (LED al máximo brillo)
    brilloActual = MAX_LATIDO_LUZ;
  } else if (tiempoTranscurrido <= DURACION_CICLO) {
    // En fase de exhalación, disminuimos el brillo suavemente
    brilloActual = map(tiempoTranscurrido, DURACION_INHALACION + DURACION_PAUSA, DURACION_CICLO, MAX_LATIDO_LUZ, 0);
  } else {
    // Reiniciamos el ciclo al final de un ciclo completo
    inicioCiclo = tiempoActual;
  }

  // Escribimos el valor de brillo en el LED
  analogWrite(ledPin, brilloActual);

  // Pequeño retardo para estabilizar la actualización del brillo
  delay(10);
}
