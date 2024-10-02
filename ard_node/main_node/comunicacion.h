#include <SPI.h>
#include <mcp2515.h>


// Construyo lo necesario
struct can_frame canMsg;
MCP2515 mcp2515(PIN_CAN_CS); // el pin en que está conectado 

void inicio_CAN ()
{
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}


void enviar_mensaje (uint16_t ID, char playload) 
{
    // debug
    Serial.println("-");
    Serial.print("Tx: ");
    Serial.print(ID);
    Serial.print(" - ");
    Serial.println(playload);

    // configuro el mensaje
    struct can_frame canMsg1;
    canMsg1.can_id  = ID;
    canMsg1.can_dlc = 1;            // cuantos bytes va a tener el msg
    canMsg1.data[0] = playload;

    //Manda los datos
    mcp2515.sendMessage(&canMsg1);
}