// fecha_fun.h

#ifndef FECHA_FUN_H
#define FECHA_FUN_H
#include "../lectura/sensor_data.h"
class FechaFunciones {
public:
    static int suma(int a, int b);
    static int resta(int a, int b);
    static SensorData getHorafecha();
};

#endif // FECHA_FUN_H
