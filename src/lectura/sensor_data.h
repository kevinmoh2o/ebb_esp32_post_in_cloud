#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H
#include <Arduino.h> 
// Declaración de la estructura SensorData
struct Date {
    int year;
    int month;
    int day;
    int hour; 
    int minute; 
    int second;
};

struct SensorData {
  float temperatura;
  float humedad;
  int year;
  String fecha;
};

// Prototipo de la función leerDatos
//SensorData leerDatos();

#endif
