// crud_online.cpp
#include "crud_online.h"
#include <HTTPClient.h> // Asegúrate de incluir la biblioteca adecuada para realizar solicitudes HTTP en Arduino

void CrudOnline::enviarPOST(String serverURL, String json) {
    HTTPClient http;
    
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    int codigo_respuesta = http.POST(json);

    if (codigo_respuesta > 0) {
        Serial.println("Código HTTP ► " + String(codigo_respuesta));

        if (codigo_respuesta == 200) {
            String cuerpo_respuesta = http.getString();
            Serial.println("El servidor respondió ▼ ");
            Serial.println(cuerpo_respuesta);
        }
    } else {
        Serial.print("Error enviando POST, código: ");
        Serial.println(codigo_respuesta);
    }

    http.end();
}
