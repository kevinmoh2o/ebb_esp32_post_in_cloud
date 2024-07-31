// fecha_fun.cpp
#include "fecha_fun.h"


int FechaFunciones::suma(int a, int b) {
    return a + b;
}

int FechaFunciones::resta(int a, int b) {
    return a - b;
}

SensorData FechaFunciones::getHorafecha()
{   
    // Establecer la zona horaria a UTC-5 (hora estándar de Perú)
    setenv("TZ", "America/Lima", 1);

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);

    int year, month, day, hour, minute, second;
    SensorData _sensor;
    char dateHourFf[32];

    // Formatear manualmente la fecha y hora
    snprintf(dateHourFf, sizeof(dateHourFf), "%02d-%02d-%04dT%02d:%02d:%02d",
             timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
             timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    if (sscanf(dateHourFf, "%d-%d-%dT%d:%d:%d", &day, &month, &year, &hour, &minute, &second) != 6) {
        return _sensor;
    }

    _sensor.fecha = dateHourFf;
    _sensor.year = year;
    return _sensor; 
}




    
    //char dateString[11];
    //char timeString[9];
    //snprintf(dateString, sizeof(dateString), "%02d-%02d-%04d", day, month, year);
    //snprintf(timeString, sizeof(timeString), "%02d:%02d:%02d", hour, minute, second);
