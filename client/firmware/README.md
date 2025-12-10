# 🚗 Vehicle Telematics Firmware (ESP32)

This folder contains the **client-side firmware** that runs inside the vehicle’s telematics device.

## ✔ Responsibilities
- Reads/simulates all major automotive sensor domains:
  - Engine & Powertrain
  - Brake System
  - Battery & Electrical System
  - Tire & Wheel
  - Fuel & Emission
  - Safety (Airbag, Lane Events)
  - GPS (Latitude & Longitude)
- Constructs JSON telemetry every 5 seconds
- Sends data to backend/dashboard through HTTP POST
- Also prints to Serial Monitor for debugging

## ✔ How to Run
1. Open Arduino IDE  
2. Select **ESP32 DevKit V1**  
3. Open `vehicle_telematics_firmware.ino`  
4. Update:
WIFI_SSID
WIFI_PASSWORD
SERVER_URL

5. Flash to ESP32  
6. Open Serial Monitor → Watch JSON output  

## ✔ Notes
This firmware simulates realistic vehicle behaviour for demo.
Real sensors can be plugged in directly later (ADC/CAN/GPIO).
