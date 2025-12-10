/*
  Vehicle Telematics Firmware (CLIENT SIDE)
  ----------------------------------------
  - Runs on ESP32 (Arduino core)
  - Reads / simulates:
      Engine & Powertrain sensors
      Brake system sensors
      Battery & electrical sensors
      Tire & wheel sensors
      Fuel & emission sensors
      Safety sensors
      GPS (latitude, longitude)
  - Packages data as JSON and sends to cloud via HTTP POST
  - Also prints JSON to Serial for demo

  For real hardware:
  - Replace the simulate*() functions / random values with real sensor reads
  - Keep the JSON keys the SAME so cloud / dashboard can consume directly
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>   // for GPS on Serial2

// ------------ WIFI + SERVER CONFIG ------------
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Example cloud endpoint (Flask / Node / Azure Function etc.)
const char* SERVER_URL    = "http://YOUR_SERVER_IP_OR_DOMAIN/api/telematics"; 

// ------------ GPS CONFIG (NEO-6M on UART2) ------------
// NEO-6M typical baud rate is 9600
HardwareSerial GPS_Serial(2);       // RX2/TX2 on ESP32
const int GPS_RX_PIN = 16;
const int GPS_TX_PIN = 17;

// For this demo we won't parse full NMEA, we’ll simulate GPS drift
double baseLat = 13.0827; // Chennai
double baseLon = 80.2707;

// ------------ VEHICLE STATE (for distance etc.) ------------
float odometer_km = 24000.0;   // starting distance
unsigned long lastOdoUpdate = 0;

// ------------ SIMULATION MODE ------------
#define SIMULATION_MODE 1
// If you connect real sensors, set SIMULATION_MODE to 0 and
// replace the simulate*() sections with analogRead/etc.

// ------------ HELPER: RANDOM FLOAT ------------
float randFloat(float minVal, float maxVal) {
  return minVal + (float)random(0, 10000) / 10000.0f * (maxVal - minVal);
}

// ------------ SENSOR SIMULATION ------------
void readEngineAndPowertrain(float &engineTemp, float &coolantTemp, float &vibration) {
#if SIMULATION_MODE
  engineTemp  = randFloat(80.0, 120.0);   // °C
  coolantTemp = randFloat(75.0, 110.0);   // °C
  vibration   = randFloat(0.2, 1.8);      // g
#else
  // Example:
  // int raw = analogRead(ENGINE_TEMP_PIN);
  // engineTemp = map(raw, 0, 4095, 20, 120);
  // ...
#endif
}

void readBatterySystem(float &batVolt, float &batCurrent, float &soc) {
#if SIMULATION_MODE
  batVolt    = randFloat(11.4, 13.5);   // V
  batCurrent = randFloat(-20.0, 60.0);  // A (negative = discharge)
  soc        = randFloat(40.0, 100.0);  // %
#else
  // Replace with real ADC reading & scaling
#endif
}

void readBrakeSystem(float &padLevel, float &fluidPressure, float &brakeTemp) {
#if SIMULATION_MODE
  padLevel      = randFloat(30.0, 100.0);   // %
  fluidPressure = randFloat(70.0, 120.0);   // bar
  brakeTemp     = randFloat(40.0, 180.0);   // °C
#else
  // Replace with real sensor reads
#endif
}

void readTireAndWheel(float &tirePressure, float &tireTemp, float &wheelVib) {
#if SIMULATION_MODE
  tirePressure = randFloat(26.0, 38.0);   // PSI
  tireTemp     = randFloat(25.0, 70.0);   // °C
  wheelVib     = randFloat(0.1, 1.0);     // g
#else
  // Replace with real sensor reads
#endif
}

void readFuelAndEmission(float &fuelLevel, float &fuelPressure, float &o2Level) {
#if SIMULATION_MODE
  fuelLevel    = randFloat(10.0, 100.0);   // %
  fuelPressure = randFloat(200.0, 350.0);  // bar
  o2Level      = randFloat(0.1, 0.9);      // normalized
#else
  // Replace with real sensor reads
#endif
}

void readSafety(int &laneEvents, String &airbagStatus) {
#if SIMULATION_MODE
  // random lane drift events sometimes
  if (randFloat(0, 1) < 0.2) {
    laneEvents = (int)randFloat(0, 3.9);
  } else {
    laneEvents = 0;
  }
  airbagStatus = "OK";  // or "FAULT"
#else
  // Read from CAN / digital pins etc.
#endif
}

// ------------ GPS (SIMULATED DRIFT) ------------
void readGps(float &lat, float &lon) {
#if SIMULATION_MODE
  // Small random drift around base location
  baseLat += randFloat(-0.0005, 0.0005);
  baseLon += randFloat(-0.0005, 0.0005);
  lat = (float)baseLat;
  lon = (float)baseLon;
#else
  // Read from real GPS via NMEA parsing (TinyGPS++ etc.)
  // For this fast prototype we keep it simulated.
#endif
}

// ------------ DISTANCE UPDATE ------------
void updateOdometer() {
  unsigned long now = millis();
  if (now - lastOdoUpdate > 5000) {  // every 5s, assume some small distance
    float deltaKm = randFloat(0.05, 0.3); // 50–300m
    odometer_km += deltaKm;
    lastOdoUpdate = now;
  }
}

// ------------ WIFI HELPERS ------------
void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: " + WiFi.localIP().toString());
}

// ------------ SEND JSON TO CLOUD ------------
void sendTelemetryToCloud(const String &jsonPayload) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WARN] WiFi not connected, skipping HTTP POST");
    return;
  }

  HTTPClient http;
  http.begin(SERVER_URL);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST(jsonPayload);
  if (httpCode > 0) {
    Serial.print("[HTTP] POST... code: ");
    Serial.println(httpCode);
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
      String response = http.getString();
      Serial.println("[HTTP] Response: " + response);
    }
  } else {
    Serial.print("[HTTP] POST failed: ");
    Serial.println(http.errorToString(httpCode));
  }
  http.end();
}

// ------------ SETUP + LOOP ------------
void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("\n=== Vehicle Telematics Firmware Starting ===");

  // GPS UART
  GPS_Serial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  // Random seed
  randomSeed(analogRead(34));

  connectWiFi();
}

void loop() {
  // Update distance (odometer)
  updateOdometer();

  // ---- Read all sensors (or simulate) ----
  float engineTemp, coolantTemp, vibration;
  float batVolt, batCurrent, soc;
  float padLevel, brakePress, brakeTemp;
  float tirePressure, tireTemp, wheelVib;
  float fuelLevel, fuelPress, o2Level;
  int laneEvents;
  String airbagStatus;
  float gpsLat, gpsLon;

  readEngineAndPowertrain(engineTemp, coolantTemp, vibration);
  readBatterySystem(batVolt, batCurrent, soc);
  readBrakeSystem(padLevel, brakePress, brakeTemp);
  readTireAndWheel(tirePressure, tireTemp, wheelVib);
  readFuelAndEmission(fuelLevel, fuelPress, o2Level);
  readSafety(laneEvents, airbagStatus);
  readGps(gpsLat, gpsLon);

  // ---- Build JSON payload (keys match your dashboard/server) ----
  String vehicleId = "TN10AB1234";     // or dynamic / flash-stored ID
  String region    = "Chennai Region"; // optional, can be derived at server

  String json = "{";
  json += "\"vehicle_id\":\"" + vehicleId + "\",";
  json += "\"region\":\"" + region + "\",";
  json += "\"gps_lat\":" + String(gpsLat, 6) + ",";
  json += "\"gps_lon\":" + String(gpsLon, 6) + ",";

  json += "\"engine_temp\":" + String(engineTemp, 2) + ",";
  json += "\"coolant_temp\":" + String(coolantTemp, 2) + ",";
  json += "\"vibration_level\":" + String(vibration, 3) + ",";
  json += "\"distance_travelled\":" + String(odometer_km, 1) + ",";

  json += "\"battery_voltage\":" + String(batVolt, 2) + ",";
  json += "\"battery_current\":" + String(batCurrent, 1) + ",";
  json += "\"soc\":" + String(soc, 1) + ",";

  json += "\"brake_pad_level\":" + String(padLevel, 1) + ",";
  json += "\"brake_fluid_pressure\":" + String(brakePress, 1) + ",";
  json += "\"brake_temp\":" + String(brakeTemp, 1) + ",";

  json += "\"tire_pressure\":" + String(tirePressure, 1) + ",";
  json += "\"tire_temp\":" + String(tireTemp, 1) + ",";
  json += "\"wheel_vibration\":" + String(wheelVib, 3) + ",";

  json += "\"fuel_level\":" + String(fuelLevel, 1) + ",";
  json += "\"fuel_pressure\":" + String(fuelPress, 1) + ",";
  json += "\"o2_level\":" + String(o2Level, 2) + ",";

  json += "\"lane_events\":" + String(laneEvents) + ",";
  json += "\"airbag_status\":\"" + airbagStatus + "\"";

  json += "}";

  // ---- Print to Serial (for demo / debugging) ----
  Serial.println("---- Telemetry JSON (Client → Cloud) ----");
  Serial.println(json);

  // ---- Send to Cloud via HTTP ----
  sendTelemetryToCloud(json);

  // Send every 5 seconds
  delay(5000);
}
