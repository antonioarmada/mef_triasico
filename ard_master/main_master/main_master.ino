/* 
 * Ejemplo Receptor CAN
*/

#include <SPI.h>
#include <mcp2515.h>

#define led 13
struct can_frame canMsg;
MCP2515 mcp2515(3);

void setup() {
  Serial.begin(115200);
  //Serial.println("Hola CAN Rx");
  Serial.println("001");

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  pinMode(led, OUTPUT); 
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    //Serial.print("ID Recibido: ");
    Serial.println(canMsg.can_id); // Imprime el ID
    
    //Serial.print("recibo: ");
    //Serial.println(canMsg.data[0]);
    
    if(canMsg.data[0]){
      digitalWrite(led,HIGH);
    } else{
       digitalWrite(led,LOW); 
    }
  }
}