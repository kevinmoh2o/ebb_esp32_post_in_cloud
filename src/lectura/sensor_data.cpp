#include "sensor_data.h" // Incluye el archivo de encabezado
//#include <DHT.h>

//DHT dht(26, DHT11);

// Implementación de la función leerDatos
/* SensorData leerDatos() {
  SensorData data;
  int humedad = analogRead(sensorPin); // Leer valor analógico de humedad (asegúrate de que sensorPin esté definido)
  float humeda = dht.readHumidity();   // Mapear el valor de humedad a un rango del 0% al 100%
  float tempe = dht.readTemperature(); // Leer temperatura ºC
  float porcentajeHumedad = (100.0 - ((humedad / 4095.0) * 100.0));

  // Asignar valores a la estructura SensorData
  data.temperatura = 20.5;
  data.humedad = porcentajeHumedad;
  data.fecha = "2023-08-05T10:15:00";

  return data;
} */
