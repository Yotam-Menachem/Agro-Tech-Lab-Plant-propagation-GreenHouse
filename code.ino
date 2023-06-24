#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h> //Soil Temperature
#include <DallasTemperature.h> //Soil Temperature

//Temp of soil
#define SENSOR_PIN  A4 // ESP32 pin A0 connected to DS18B20 sensor's DATA pin

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float temp_soil; // temperature in Celsius
//end temp of soil

Adafruit_SHT31 sht31 = Adafruit_SHT31();
const int RELAY_PIN4 = A3; //fans
const int RELAY_PIN3 = D10; //irrigation
const int RELAY_PIN2 = D11;
const int RELAY_PIN1 = D10;

bool executeCuttingsCode = false;
bool executeEmergenceCode = false;

const char* ssid = "ESP32_AP";
const char* password = "password123";

WebServer server(80);

const char* htmlPage = R"html(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Control Panel</title>
  <style>
    /* CSS styles for the web page */
  </style>
  <script>
    /* JavaScript functions for updating data and handling button clicks */
  </script>
</head>
<body>
  <!-- HTML content for the web page -->
</body>
</html>
)html";

// Function to handle the root URL request
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

// Function to handle the "CUTTINGS" button click
void handleCuttings() {
  executeCuttingsCode = true;
  executeEmergenceCode = false;
  server.send(200, "text/html", "<h1>CUTTINGS button pressed!</h1>");
}

// Function to handle the "EMERGENCE" button click
void handleEmergence() {
  executeEmergenceCode = true;
  executeCuttingsCode = false;
  server.send(200, "text/html", "<h1>EMERGENCE button pressed!</h1>");
}

// Function to handle the data request
void handleData() {
  // Read temperature and humidity from the SHT31 sensor
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  // Construct a JSON string with temperature and humidity data
  String json = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";
  server.send(200, "application/json", json);
}

void setup() {
  // Initialize pin modes for relays and DS18B20 sensor
  pinMode(RELAY_PIN4, OUTPUT); //fans
  pinMode(RELAY_PIN3, OUTPUT);
  pinMode(RELAY_PIN2, OUTPUT);
  pinMode(RELAY_PIN1, OUTPUT);
  DS18B20.begin();    // initialize the DS18B20 sensor soil temp

  Serial.begin(115200);

  // Set up Wi-Fi access point with specified SSID and password
  WiFi.softAP(ssid, password);

  IPAddress ip = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(ip);

  // Register request handlers for different URLs
  server.on("/", handleRoot);
  server.on("/cuttings", handleCuttings);
  server.on("/emergence", handleEmergence);
  server.on("/data", handleData);

  server.begin();
  Serial
