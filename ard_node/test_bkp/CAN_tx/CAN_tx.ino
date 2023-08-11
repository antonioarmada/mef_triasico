/*
 * Ejemplo tranmisor CAN
*/
#include <SPI.h>
#include <mcp2515.h>
#define btn 3

struct can_frame canMsg1;

// aca cambie el pin 10 por 3, en todos los tutos
// está el 10, ojo con utilizar este codigo con otras conecxions
MCP2515 mcp2515(3);
bool state = 0;

void setup() {

  Serial.begin(115200);
  Serial.println("Hola CAN tx");

  canMsg1.can_id  = 0x01;
  canMsg1.can_dlc = 1;
  canMsg1.data[0] = 0x00;

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();

}

void loop() {
  
    //cambiar el estado
    state = !state;
    //modifica l frame  data[0] segun sea el estado
    if (state) {
    canMsg1.data[0] = 0x01;
    }
    else {
      canMsg1.data[0] = 0x00;
    }
    //Manda los datos
    mcp2515.sendMessage(&canMsg1);

    Serial.print("envío: ");
    Serial.println(canMsg1.data[0]);
  
    delay(1000);

}