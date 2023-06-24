#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <WiFi.h>
#include <WebServer.h>
#include <OneWire.h> //Soil Temperature
#include <DallasTemperature.h> //Soil Temperature

// Temp of soil
#define SENSOR_PIN  A4 // ESP32 pin GIOP17 connected to DS18B20 sensor's DATA pin

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float temp_soil; // temperature in Celsius
// End temp of soil

Adafruit_SHT31 sht31 = Adafruit_SHT31();

const int RELAY_PIN4 = A4; // Fans
const int RELAY_PIN3 = A3; // Irrigation
const int RELAY_PIN2 = A2;
const int RELAY_PIN1 = A1;

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
    /* CSS Styles for the HTML page */
    /* ... */
  </style>
  <script>
    /* JavaScript code for updating data */
    /* ... */
  </script>
</head>
<body>
  <h1>Welcome to ESP32 Control Panel</h1>
  <div class="button-container">
    <div>
      <button class="button" onclick="cuttingsButton()">CUTTINGS</button>
      <p class="button-description">Propagation of cuttings</p>
    </div>
    <div>
      <button class="button" onclick="emergenceButton()">EMERGENCE</button>
      <p class="button-description">Emergence of seeds</p>
    </div>
  </div>
  <h2 id="environmental">Environmental</h2>
  <h2>Temperature: <span id="temperature"></span> °C</h2>
  <h2>Humidity: <span id="humidity"></span> %</h2>
  
  <script>
    /* JavaScript code for handling button clicks */
    /* ... */
  </script>
</body>
</html>
)html";

void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleCuttings() {
  executeCuttingsCode = true;
  executeEmergenceCode = false;
  server.send(200, "text/html", "<h1>CUTTINGS button pressed!</h1>");
}

void handleEmergence() {
  executeEmergenceCode = true;
  executeCuttingsCode = false;
  server.send(200, "text/html", "<h1>EMERGENCE button pressed!</h1>");
}

void handleData() {
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  String json = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}";
  server.send(200, "application/json", json);
}

void setup() {
  pinMode(RELAY_PIN4, OUTPUT);

  DS18B20.begin(); // Initialize the DS18B20 sensor for soil temperature

  Serial.begin(115200);

  WiFi.softAP(ssid, password); // Create a Wi-Fi access point with the specified SSID and password

  IPAddress ip = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(ip);

  // Set up the web server routes
  server.on("/", handleRoot);
  server.on("/cuttings", handleCuttings);
  server.on("/emergence", handleEmergence);
  server.on("/data", handleData);

  server.begin();
  Serial.println("HTTP server started");

  // Initialize the SHT31 sensor
  if (!sht31.begin(0x44)) {
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
}

void loop() {
  // Handle incoming client requests
  server.handleClient();

  // Read the temperature of the soil
  DS18B20.requestTemperatures();
  temp_soil = DS18B20.getTempCByIndex(0);

  Serial.print("Temp of soil: ");
  Serial.print(temp_soil);
  Serial.println("°C");

  // Read the temperature and humidity of the environment
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  if (!isnan(t)) {
    if (t < 25) {
      if (executeCuttingsCode) {
        // Code to execute when "Cuttings" button is pressed and the temperature is below 25°C
        digitalWrite(RELAY_PIN4, LOW); // Turn on the fan
      }
    }
    if (t < 27) {
      if (executeEmergenceCode) {
        // Code to execute when "Emergence" button is pressed and the temperature is below 27°C
        digitalWrite(RELAY_PIN4, LOW); // Turn off the fan
      }
    }
    if (t > 25) {
      Serial.println("Temp is too high");
      if (executeCuttingsCode) {
        // Code to execute when "Cuttings" button is pressed and the temperature is above 25°C
        digitalWrite(RELAY_PIN4, HIGH); // Turn on the fan
      }
    }
    if (t > 27) {
      Serial.println("Temp is too high");
      if (executeEmergenceCode) {
        // Code to execute when "Emergence" button is pressed and the temperature is above 27°C
        digitalWrite(RELAY_PIN4, HIGH); // Turn on the fan
      }
    }
    Serial.print("Temp of environment = ");
    Serial.println(t);
  } else {
    Serial.println("Failed to read temperature");
  }

  if (!isnan(h)) {
    if (h < 80) {
      Serial.println("Humidity is too low");
    }
    if (h > 80) {
      Serial.println("Humidity is too high");
    }
    Serial.print("Humidity % = ");
    Serial.println(h);
  } else {
    Serial.println("Failed to read humidity");
  }

  Serial.println();
  delay(1000);
}
