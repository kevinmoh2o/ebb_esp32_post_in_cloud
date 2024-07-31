// crud_online.h

#ifndef CRUD_ONLINE_H
#define CRUD_ONLINE_H

#include <Arduino.h>

class CrudOnline {
public:
    // Función para realizar una solicitud HTTP POST
    static void enviarPOST(String serverURL, String json);
};

#endif // CRUD_ONLINE_H
