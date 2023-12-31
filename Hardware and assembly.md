# Agro-Tech-Lab-Plant-propagation-GreenHouse
Welcome to our final project in the Agro-Lab course 

# If you would like to make this project by yourself this is what you'll need:


1. 1 X [ESP32](https://he.aliexpress.com/item/1005003818247483.html?spm=a2g0o.productlist.0.0.755710d1jXgc9F&algo_pvid=285495db-7b43-4cc5-bc67-508cdd252f7d&algo_exp_id=285495db-7b43-4cc5-bc67-508cdd252f7d-15&pdp_ext_f=%7B%22sku_id%22%3A%2212000027263733305%22%7D&pdp_npi=2%40dis%21ILS%21%216.46%21%21%21%21%21%402100bddf16578052994232769e06b1%2112000027263733305%21sea&gatewayAdapt=glo2isr)
2. 1 X [Relay 5V - 4 Channels](https://he.aliexpress.com/item/1005004968030652.html?spm=a2g0o.productlist.main.47.57cfJ1L1J1L13s&algo_pvid=43924125-d89b-479f-b3fc-e9b64585046d&algo_exp_id=43924125-d89b-479f-b3fc-e9b64585046d-23&pdp_npi=3%40dis%21ILS%216.5%214.48%21%21%21%21%21%400b0a558a16865572273001677d0778%2112000031188054608%21sea%21IL%212183826556&curPageLogUid=JY4NeeivKjoX)
3. 1 X [BreadBoard](https://he.aliexpress.com/item/1005003640449308.html?spm=a2g0o.search0304.0.0.5fab692f1DqEZK&algo_pvid=a722cf1e-c2ba-4fde-b94f-ef8fe25a6ce9&algo_exp_id=a722cf1e-c2ba-4fde-b94f-ef8fe25a6ce9-14&pdp_ext_f=%7B%22sku_id%22%3A%2212000026608920636%22%7D&pdp_npi=2%40dis%21ILS%21%2117.36%21%21%214.23%21%21%400b0a187b16578059214857204e2875%2112000026608920636%21sea&gatewayAdapt=glo2isr)
4. 2 X [Brushless DC fans](https://he.aliexpress.com/item/1005003088728988.html?spm=a2g0o.productlist.main.23.b534nTcunTcuH1&algo_pvid=65dec40f-36d1-41ea-9da0-6c78977f734b&algo_exp_id=65dec40f-36d1-41ea-9da0-6c78977f734b-11&pdp_npi=3%40dis%21ILS%2114.28%218.3%21%21%21%21%21%402122457116865575297654972d0798%2112000024011812633%21sea%21IL%212183826556&curPageLogUid=QsCGaf42Lg3w)
5. 1 X [SHT31 - WaterProof](https://he.aliexpress.com/item/33008520683.html?spm=a2g0o.productlist.main.47.71aeQktEQktEDW&algo_pvid=c763fb13-31fd-4e84-9c06-aea11efe362a&algo_exp_id=c763fb13-31fd-4e84-9c06-aea11efe362a-23&pdp_npi=3%40dis%21ILS%2120.45%2118.4%21%21%21%21%21%40210219c216865576597604382d0777%2167086038424%21sea%21IL%212183826556&curPageLogUid=h15PFW0tVoad)
6. 1 X [FDR - Frequency-domain sensor](https://he.aliexpress.com/item/1005005117882147.html?spm=a2g0o.productlist.main.25.7f23Nil6Nil6hl&algo_pvid=c45dbcd0-d6c6-49b8-bd59-f40790fd82bf&algo_exp_id=c45dbcd0-d6c6-49b8-bd59-f40790fd82bf-12&pdp_npi=3%40dis%21ILS%21175.41%21175.41%21%21%21%21%21%40211beeec16865578754097004d081a%2112000031719776010%21sea%21IL%212183826556&curPageLogUid=W5LbNYmuKIYd)
7. 3 X [Solenoid valve - AC 220V DC 12V "1/2](https://he.aliexpress.com/item/1005005244510404.html?spm=a2g0o.productlist.main.11.40260oNn0oNnSW&algo_pvid=acd3bfec-322c-4e79-9431-6045fddcfeda&algo_exp_id=acd3bfec-322c-4e79-9431-6045fddcfeda-5&pdp_npi=3%40dis%21ILS%2143.25%2113.4%21%21%21%21%21%40211bf3f116865579903736896d080f%2112000032343782698%21sea%21IL%212183826556&curPageLogUid=JKWGlp0MsLCN)
9. [A lot of Jumpers](https://he.aliexpress.com/item/1005003252824475.html?spm=a2g0o.search0304.0.0.5fab692f1DqEZK&algo_pvid=a722cf1e-c2ba-4fde-b94f-ef8fe25a6ce9&algo_exp_id=a722cf1e-c2ba-4fde-b94f-ef8fe25a6ce9-13&pdp_ext_f=%7B%22sku_id%22%3A%2212000024867532507%22%7D&pdp_npi=2%40dis%21ILS%21%2114.17%21%21%211.38%21%21%400b0a187b16578059214857204e2875%2112000024867532507%21sea&gatewayAdapt=glo2isr)

# Project Components

To successfully complete this Arduino project using the ESP-32, you will need to gather the following components:

1. Relay: A relay module allows you to control high-power devices using a low-power signal from the ESP-32. This [tutorial](https://randomnerdtutorials.com/esp32-relay-module-ac-web-server/) provides information on how to connect and utilize a relay with the ESP-32.

2. Brushless DC Fans: These fans are commonly used for cooling purposes in various projects. This [tutorial](https://esp32io.com/tutorials/esp32-controls-fan) will guide you on how to control brushless DC fans with the ESP-32.

3. SHT31 - Waterproof Temperature and Humidity Sensor: The SHT31 sensor is capable of measuring temperature and humidity in harsh environments. You can learn more about this sensor and its connection to the ESP-32 in the [DFRobot Wiki](https://wiki.dfrobot.com/SHT31_Temperature_Humidity_Sensor_Weatherproof_SKU_SEN0385).

4. FDR - Frequency-Domain Sensor: The FDR sensor is commonly used for soil moisture measurements. This [tutorial](https://esp32io.com/tutorials/esp32-soil-moisture-sensor) will provide you with information on how to interface and utilize the FDR sensor with the ESP-32.

5. Solenoid Valve - AC 220V DC 12V "1/2": This solenoid valve allows you to control the flow of water or other liquids using the ESP-32. The [tutorial](https://esp32io.com/tutorials/esp32-water-liquid-valve) explains the connection and usage of this valve with the ESP-32.

Please refer to the provided links for further details on connecting and utilizing these components in your Arduino project.
