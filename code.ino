#include <Arduino.h> // Include the Arduino core library
#include <Wire.h> // Include the Wire library for I2C communication
#include "Adafruit_SHT31.h" // Include the Adafruit_SHT31 library for SHT31 temperature and humidity sensor
#include <WiFi.h> // Include the WiFi library for WiFi communication
#include <WebServer.h> // Include the WebServer library for creating a web server
#include <OneWire.h> // Include the OneWire library for 1-wire communication
#include <DallasTemperature.h> // Include the DallasTemperature library for temperature sensing

//Temp of soil
#define SENSOR_PIN  A4 // ESP32 pin A0 connected to DS18B20 sensor's DATA pin

OneWire oneWire(SENSOR_PIN); // Create a OneWire object named 'oneWire' using the pin defined as 'SENSOR_PIN'
DallasTemperature DS18B20(&oneWire); // Create a DallasTemperature object named 'DS18B20' and initialize it with a pointer to the 'oneWire' object


float temp_soil; // temperature in Celsius
//end temp of soil


Adafruit_SHT31 sht31 = Adafruit_SHT31();
const int RELAY_PIN4 = A3; //fans
const int RELAY_PIN3 = D10; //irrigation
const int RELAY_PIN2 = D11;
const int RELAY_PIN1 = D10;

bool executeCuttingsCode = false; // A boolean variable to indicate if the cuttings code should be executed or not
bool executeEmergenceCode = false; // A boolean variable to indicate if the emergence code should be executed or not

const char* ssid = "ESP32_AP"; // The SSID (network name) for the ESP32 access point mode
const char* password = "password123"; // The password for the ESP32 access point mode

WebServer server(80); // Create a WebServer object listening on port 80

// A multiline string containing the HTML code for the web page
const char* htmlPage = R"html(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Control Panel</title>
  <style>
    body {
      background-size: cover;
      background-position: center;
      font-family: Arial, sans-serif;
      text-align: center;
    }
    h1 {
      font-size: 48px;
      color: #333333;
      margin-top: 100px;
    }
    .button-container {
      display: flex;
      justify-content: center;
      margin-top: 50px;
    }
    .button {
      background-color: #4CAF50;
      color: #ffffff;
      border: none;
      padding: 16px 32px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 24px;
      margin: 10px;
      cursor: pointer;
    }
    .button-description {
      font-size: 18px;
      color: #666666;
    }
    #environmental {
      font-size: 24px;
      color: #666666;
      margin-top: 50px;
    }
    #temperature,
    #humidity {
      font-size: 36px;
      color: #333333;
    }
  </style>
  <script>
    function updateData() {
      fetch('/data')
        .then(response => response.json())
        .then(data => {
          document.getElementById('temperature').innerText = data.temperature;
          document.getElementById('humidity').innerText = data.humidity;
        });
    }
    setInterval(updateData, 1000); // Update data every 1 second
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
    function cuttingsButton() {
      alert("CUTTINGS button pressed!");
      window.location.href = "/cuttings";
    }
    function emergenceButton() {
      alert("EMERGENCE button pressed!");
      window.location.href = "/emergence";
    }
  </script>
</body>
</html>
)html";
//end of webpage

void handleRoot() {
  server.send(200, "text/html", htmlPage); // Send an HTTP response with status code 200, content type "text/html", and send the htmlPage as the response body
}

void handleCuttings() {
  executeCuttingsCode = true; // Set the executeCuttingsCode variable to true
  executeEmergenceCode = false; // Set the executeEmergenceCode variable to false
  server.send(200, "text/html", "<h1>CUTTINGS button pressed!</h1>"); // Send an HTTP response with status code 200, content type "text/html", and send the message "<h1>CUTTINGS button pressed!</h1>" as the response body
}

void handleEmergence() {
  executeEmergenceCode = true; // Set the executeEmergenceCode variable to true
  executeCuttingsCode = false; // Set the executeCuttingsCode variable to false
  server.send(200, "text/html", "<h1>EMERGENCE button pressed!</h1>"); // Send an HTTP response with status code 200, content type "text/html", and send the message "<h1>EMERGENCE button pressed!</h1>" as the response body
}

void handleData() {
  float t = sht31.readTemperature(); // Read the temperature value from the SHT31 sensor and store it in the variable t
  float h = sht31.readHumidity(); // Read the humidity value from the SHT31 sensor and store it in the variable h

  String json = "{\"temperature\":" + String(t) + ",\"humidity\":" + String(h) + "}"; // Create a JSON string containing the temperature and humidity values
  server.send(200, "application/json", json); // Send an HTTP response with status code 200, content type "application/json", and send the json string as the response body
}

void setup() {
  pinMode(RELAY_PIN4, OUTPUT); // Set RELAY_PIN4 as an output pin (for controlling fans)
  pinMode(RELAY_PIN3, OUTPUT); // Set RELAY_PIN3 as an output pin
  pinMode(RELAY_PIN2, OUTPUT); // Set RELAY_PIN2 as an output pin
  pinMode(RELAY_PIN1, OUTPUT); // Set RELAY_PIN1 as an output pin

  DS18B20.begin(); // Initialize the DS18B20 sensor for soil temperature

  Serial.begin(115200); // Initialize the serial communication at a baud rate of 115200

   WiFi.softAP(ssid, password); // Start the ESP32 in access point mode with the given SSID and password

  IPAddress ip = WiFi.softAPIP(); // Get the IP address of the access point
  Serial.print("AP IP address: ");
  Serial.println(ip);

  server.on("/", handleRoot);       // Handle requests to the root path ("/") with the handleRoot() function
  server.on("/cuttings", handleCuttings);   // Handle requests to the "/cuttings" path with the handleCuttings() function
  server.on("/emergence", handleEmergence); // Handle requests to the "/emergence" path with the handleEmergence() function
  server.on("/data", handleData);           // Handle requests to the "/data" path with the handleData() function

  server.begin(); // Start the HTTP server
  Serial.println("HTTP server started");

  if (!sht31.begin(0x44)) { // Initialize the SHT31 sensor with the I2C address 0x44
    Serial.println("Couldn't find SHT31"); // Print an error message if the sensor is not found
    while (1) delay(1); // Enter an infinite loop to halt the program
  }
}

void loop() {
  server.handleClient(); // Handle incoming client requests

  //temp of soil 
  
  DS18B20.requestTemperatures(); // Send a command to get the temperature of the soil
  temp_soil = DS18B20.getTempCByIndex(0); // Read the temperature in °C of the soil
  
  Serial.print("temp of soil: ");
  Serial.print(temp_soil); // Print the temperature of the soil in °C
  Serial.println("°C");
  
  // end temp of soil

  float t = sht31.readTemperature(); // Read the temperature value from the SHT31 sensor
  float h = sht31.readHumidity(); // Read the humidity value from the SHT31 sensor

  if (!isnan(t)) {
    if (t < 25) {
      //Serial.println("temp is too low");
      if (executeCuttingsCode) { // turn on the fan
        digitalWrite(RELAY_PIN4, LOW); // Turn off the fans
        digitalWrite(RELAY_PIN3, LOW); // Turn off the cooling system
      }
    }
    if (t < 27) {
      //Serial.println("temp is too low");
      if (executeEmergenceCode) { // turn off the fan
        digitalWrite(RELAY_PIN4, LOW); // Turn off the fans
        digitalWrite(RELAY_PIN3, LOW); // Turn off the cooling system
      }
    }
    if (t > 25) {
      Serial.println("temp is too high");
      if (executeCuttingsCode) {
        Serial.println("Cutting button was pressed");
        // Code to execute when "Cutting" button is pressed
        digitalWrite(RELAY_PIN4, HIGH); // Turn on the fans
        digitalWrite(RELAY_PIN3, HIGH); // Turn on the cooling system

      }
    }
    if (t > 27) {
      Serial.println("temp is too high");
      if (executeEmergenceCode) {
        Serial.println("Emergence button was pressed");
        // Code to execute when "EMERGENCE" button is pressed
        digitalWrite(RELAY_PIN4, HIGH); // Turn on the fans
        digitalWrite(RELAY_PIN3, HIGH); // Turn on the cooling system
      }
    }
    Serial.print("Temp of enviroment = ");
    Serial.println(t); // Print the temperature of the environment
  } else {
    Serial.println("Failed to read temperature");
  }

  if (!isnan(h)) {
        if (h > 80) {
      //Serial.println("Humidity is too high");
      if (executeCuttingsCode) {
        digitalWrite(RELAY_PIN2, LOW); // Turn off the sprinklers
        
      }
    }
    if (h > 50) {
      //Serial.println("Humidity is too high");
      if (executeEmergenceCode) { 
        digitalWrite(RELAY_PIN2, LOW); // Turn off the sprinklers
      }
    }
    if (h < 80) {
      //Serial.println("Humidity is too low");
      if (executeCuttingsCode) { 
        digitalWrite(RELAY_PIN2, HIGH); // Turn on the sprinklers
        
      }
    }
    if (h < 50) {
      //Serial.println("Humidity is too low");
      if (executeEmergenceCode) {
        digitalWrite(RELAY_PIN2, HIGH); // Turn on the sprinklers
      }
    }
    
    Serial.print("Hum. % = ");
    Serial.println(h);  // Print the humidity value
  } else {
    Serial.println("Failed to read humidity");
  }

  //humidity of soil
  //The FDR sensor was calibrated base on average of readings in 100% wet Perlite substrate. the value of moistue in maximum humidity is 460
  float h_s = analogRead(A2);    // Read soil moistur from the FDR sensor

  if (! isnan(h_s)) {              // Check if h is not NaN (not a number)
      if ((h_s/460)*100 > 80) {
      //Serial.println("soil moisture is too high");
      if (executeCuttingsCode) {
        digitalWrite(RELAY_PIN1, LOW); // Turn off the irrigation
        
      }
    }

    if ((h_s/460)*100 > 50) {
      //Serial.println("soil moisture is too high");
      if (executeEmergenceCode) { 
        digitalWrite(RELAY_PIN1, LOW); // Turn off the irrigation
      }
    }
    if ((h_s/460)*100 < 80) {
      //Serial.println("soil moisture is too low");
      if (executeCuttingsCode) { 
        digitalWrite(RELAY_PIN1, HIGH); // Turn on the irrigation
        
      }
    }
    if ((h_s/460)*100 < 50) {
      //Serial.println("soil moisture is too low");
      if (executeEmergenceCode) {
        digitalWrite(RELAY_PIN1, HIGH); // Turn on the irrigation
      }
    }
    Serial.print("Hum. % = ");  // Print humidity label
    Serial.println((h_s/460)*100);           // Print humidity value
  } 
  else {
    Serial.println("Failed to read humidity of soil");  // Print an error message if humidity reading fails
  }
  //end of humidity of soil

  Serial.println();
  delay(1000);
}
