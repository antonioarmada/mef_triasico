#include <SPI.h>
#include <mcp2515.h>


// Construyo lo necesario
struct can_frame canMsg;
MCP2515 mcp2515(PIN_CAN_CS); // el pin en que está conectado 


bool inicio_CAN() {
    Serial.println("Iniciando configuración CAN...");
    
    // Paso 1: Reset
    if (mcp2515.reset() != MCP2515::ERROR_OK) {
        Serial.println("Error: Fallo al resetear el módulo MCP2515");
        return false;
    }
    Serial.println("Reset MCP2515 exitoso");
    
    // Paso 2: Configurar bitrate
    if (mcp2515.setBitrate(CAN_125KBPS) != MCP2515::ERROR_OK) {
        Serial.println("Error: Fallo al configurar el bitrate");
        return false;
    }
    Serial.println("Bitrate configurado correctamente");
    
    // Paso 3: Configurar modo normal
    if (mcp2515.setNormalMode() != MCP2515::ERROR_OK) {
        Serial.println("Error: Fallo al configurar modo normal");
        return false;
    }
    Serial.println("Modo normal configurado correctamente");
    
    Serial.println("Inicialización CAN completada con éxito");
    return true;
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