# Agro-Tech-Lab-Plant-propagation-GreenHouse
Welcome to our final project in the Agro-Lab course 

# Plant Propagation Greenhouse

This project utilizes the ESP-32 microcontroller board to create an automated plant propagation greenhouse. The greenhouse provides optimal conditions for plant growth by controlling temperature, humidity, and soil moisture levels using various sensors and actuators.

## Features

1. **Temperature Control**: The system maintains the temperature inside the greenhouse by heating the perlite when the temperature drops below the desired threshold of 30°C. This ensures that the plants receive adequate warmth for healthy growth.

2. **Cooling Mechanism**: When the temperature inside the greenhouse exceeds 25°C, the system activates cooling fans to circulate air and lower the temperature. Additionally, a cooling pad and CoolNet foggers (https://www.growirrigation.com/collections/netafim-coolnet-foggers) are utilized to provide additional cooling if necessary.

3. **Humidity Regulation**: The greenhouse is designed to maintain a consistent humidity level of 80%. This is achieved by carefully monitoring the humidity using sensors and adjusting the operation of the foggers to achieve the desired humidity range.

4. **Soil Moisture Control**: The system ensures that the soil moisture remains at an optimal level of 100% by employing a drip irrigation system. The soil moisture is monitored using sensors, and water is supplied through the drip irrigation mechanism to maintain the desired moisture level.

5. **Greenhouse Covering**: The greenhouse is covered with polyethylene to create a controlled environment. Additionally, the presence of window mesh allows for adequate airflow, ensuring proper ventilation and gas exchange for the plants.

## Getting Started

To replicate this project, follow these steps:

1. **Hardware Setup**: Connect the ESP-32 microcontroller to the necessary sensors and actuators as per the circuit diagram provided.

2. **Arduino IDE**: Install the Arduino IDE (Integrated Development Environment) and ensure that the ESP-32 board is properly recognized.

3. **Libraries**: Install the required libraries for the sensors and actuators used in the project. Refer to the documentation provided by the respective manufacturers for instructions on installing the libraries.

4. **Code**: Upload the provided Arduino sketch (code) to the ESP-32 microcontroller board. The sketch contains the necessary logic to control the greenhouse environment based on the sensor readings.

5. **Calibration**: Perform calibration for the sensors used to ensure accurate readings. Adjust the temperature, humidity, and moisture thresholds in the code according to your specific requirements.

6. **Power On**: Power up the system and monitor the greenhouse conditions through the serial monitor in the Arduino IDE.

## Contributors

- [Orel Suliman](https://github.com/orelsoli77), [Yotam Menachem](https://github.com/Yotam-Menachem).


Feel free to customize this README.md file as per your project's requirements, add relevant images, and provide any additional details or instructions necessary for others to replicate your project successfully. Good luck with your plant propagation greenhouse!
