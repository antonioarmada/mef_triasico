// Valor inicial de ID de mensajes para este nodo
// hago esto, todos los mensjaes que que mande este
// van a estar en el rango de (ID_NODO,  ID_NODO+100)
// por lo que los nodos van a tener estos rangos de id
// para los mensajes: Nodo 1 (100,199), Nodo 2 (200,299)
// hay que cambiar este valor cada vez que se cargue 
// el código en un nodo nuevo
const uint16_t ID_NODO = 200;

// Sub direcciones que se le suman al ID_NODO para identificar una funcion
// del mensaje (ID_NODO + SUB INICIADO) = 100 + 1 = 101 para mensaje de estado del nodo 100
const int SUB_INICIADO = 1;   // se envia al iniciar
const int SUB_ACTIVADO = 2;   // se envia al activarse
const int SUB_ERROR = 3;   // se envia al activarse

// Configuraciones de uso
const int TAMANO = 4;                                           // para asegurarme que tienen el mismo tamaño
int DISTANCIAS[TAMANO] =    {   30,    500,    1200,  1800 };   // [mm] valor 0, minimo de activación, valor 3 maximo apagado
int INTENSIDADES[TAMANO] =  {   255,   255,    100,   0    };   // [0-255] corresponde una INTENSIDAD a una DISTANCIA, same length
const int VELOCIDAD_LUCES = 1;
const long BOUNCING_TIME = 10 *1000; // millis que espera entre una activación y otra  

// Pines
const int PIN_LUCES = 9;  
const int LED = LED_BUILTIN;   // 13 en casi todos los Arduinos
const int PIN_CAN_CS = 3;      // donde está conectado el pin CS del modulo CAN
// INT a D2 

// Sensor
// SDA: A5
// SDL: A4