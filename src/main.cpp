#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "./lectura/sensor_data.h"
#include "./fechas/fecha_fun.h"
#include "./servicio/crud_online.h"
//#include <HTTPClient.h>
#include <WiFi.h>
#include <TimeLib.h>
#include <stdint.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


// ******** PINS ********
#define RELAY_PIN 19
#define MOSTURE_SENSOR_PIN A0
#define DHTPIN 26


// ******** DEFINES ********
#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#define DHTTYPE DHT11
//#define LED 2

// ******** CONSTRUCTORES ********
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
DHT dht(DHTPIN, DHT11);
WiFiUDP udp;
AsyncWebServer server(80);


// ******** CONST ********
int humedad = 0; 
const char* ssid = "Redmi Note 10S";
const char* password = "kevimwifi";
const char* PARAM_MESSAGE = "message";
//const char* ssid = "Galaxy A52s 5GBD9D";
//const char* password = "eqnz0344";
//const char* ssid = "AIPSA_DIRECTORES";
//const char* password = "";
const char* ntpServer = "pool.ntp.org";
const String serverURL = "https://luna-covid-efwqev.firebaseio.com/resultados.json";
const long  gmtOffset_sec = -5 * 3600;
const int   daylightOffset_sec = 0;
unsigned int localPort = 8888;
char formattedDate[32];
char user[6] = "kevin";

SensorData leerDatos();
bool iniciarSensores();
bool pinsDefinition();
void enableRelay(float valor,float puntoCorte);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
  WiFi.mode(WIFI_STA);
  iniciarSensores();
  pinsDefinition();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello, world");
    });
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
        String message;
        if (request->hasParam(PARAM_MESSAGE)) {
            message = request->getParam(PARAM_MESSAGE)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, GET: " + message);
    });

    server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    //HTTPClient http;
    SensorData data = leerDatos();
    if(data.year>2020){
      String json = "{\"user\":\"" + String(user) + "\",\"mosture\":\"" + data.humedad + "\",\"temperatura\":" + String(data.temperatura) + ",\"fechahora\":\"" + String(data.fecha) + "\"}";
      Serial.println(json);

      //LINEA 0
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print("Temp:");
      lcd.print(data.temperatura);
      lcd.print("C");
      
      //LINEA 1
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("M:");
      lcd.print(data.humedad);
      lcd.print("%");
      lcd.print(" ");
      lcd.print("data.fecha");
      lcd.print("%");
      enableRelay(data.humedad,40.0);

      //CrudOnline::enviarPOST(serverURL,json);
    }
    
  } else {
    Serial.println("Error en la conexión WIFI");
    Serial.println(WiFi.status());
  }
  //delay(300000);
  delay(3000);
  //server.H
}


SensorData leerDatos() {
  SensorData data = FechaFunciones::getHorafecha();
  humedad = analogRead(MOSTURE_SENSOR_PIN);
  float humeda = dht.readHumidity();
  float tempe = dht.readTemperature();
  float porcentajeHumedad = ( 100 - ( (humedad/4095.0) * 100 ) );
  data.temperatura = 20.5;
  data.humedad = porcentajeHumedad;
  return data;
}

bool pinsDefinition(){
  pinMode(RELAY_PIN, OUTPUT);
  return true;
}

bool iniciarSensores(){
  Serial.begin(115200);//SERIAL UART
  Wire.begin();//I2C
  dht.begin();//DTH
  lcd.init();//LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Humedad del Suelo:");

  WiFi.begin(ssid, password);
  Serial.print("CONECTANDO...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
  udp.begin(localPort);

  String macAddress = WiFi.macAddress();
  Serial.print("Dirección MAC del ESP32: ");
  Serial.println(macAddress);
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);// Configura el servidor NTP
  
  return true;
}

void enableRelay(float valor,float puntoCorte){
  if(valor<puntoCorte){
    digitalWrite(RELAY_PIN, HIGH);
  }else{
    digitalWrite(RELAY_PIN, LOW);
  }
}