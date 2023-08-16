// Valor inicial de ID de mensajes para este nodo
// hago esto, todos los mensjaes que que mande este
// van a estar en el rango de (ID_NODO,  ID_NODO+100)
// por lo que los nodos van a tener estos rangos de id
// para los mensajes: Nodo 1 (100,199), Nodo 2 (200,299)
// hay que cambiar este valor cada vez que se cargue 
// el código en un nodo nuevo
const uint16_t ID_NODO = 100;

// Configuraciones de uso
const int DIST_MAX = 1800;
const int DIST_MIN = 30;
const int PWM_MIN = 0;
const int PWM_MAX = 255;
const int VELOCIDAD = 3;
const uint16_t ID_ERROR = 1;

// Pines
const int PIN_LUCES = 9;  
const int LED = LED_BUILTIN; // 13 en casi todos los Arduinos
const int PIN_CAN_CS = 3; // donde está conectado el pin CS del modulo CAN
// 