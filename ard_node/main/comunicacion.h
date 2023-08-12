#include <SPI.h>
#include <mcp2515.h>


// CAN
struct can_frame canMsg;
MCP2515 mcp2515(PIN_CAN_INT); // el pin en que está conectado 

void inicio_CAN ()
{
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}


void enviar_mensaje (uint16_t ID, int playload) 
{
  Serial.println("-");
  Serial.print("Tx: ");
  Serial.print(ID);
  Serial.print(" - ");
  Serial.println(playload);
  // enviar acá CAN en bufer [0]?
}