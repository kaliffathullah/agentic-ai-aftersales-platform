# 🔄 Data Flow – End-to-End System

## Step 1 — Sensor Data Collection
ESP32 collects:
- Engine temperature
- Battery voltage
- Brake pressure
- Tire pressure
- Fuel data
- Safety data
- GPS coordinates

## Step 2 — JSON Telemetry Packet
Firmware constructs JSON and sends every 5 seconds.

## Step 3 — AI Processing (Simulated)
Dashboard computes:
- Failure probability
- RUL
- Schedule priority
- Anomaly detection
- RCA/CAPA suggestions

## Step 4 — Dashboard Visualization
UI displays:
- Raw live telemetry
- Vehicle ranking
- Alerts
- Insights
- Service recommendations

## Step 5 — Action
- Customer is notified  
- Service slot is assigned  
- Manufacturer receives RCA/CAPA  
