# 🧠 System Architecture – Agentic AI Aftersales Platform

This document explains the overall architecture of the system.

---

## 1️⃣ High-Level Overview

Vehicle → Telematics Firmware (ESP32) → Cloud AI → Dashboard → Service Centers → Manufacturing

---

## 2️⃣ Components

### ✔ Vehicle-Side (ESP32 Firmware)
- Reads sensors  
- Generates telemetry  
- Pushes JSON to cloud  

### ✔ Cloud-Side AI Agents (Simulated)
- Predictive Failure Agent  
- Remaining Useful Life (RUL) Agent  
- Autonomous Scheduling Agent  
- UEBA Security Agent  
- RCA/CAPA Insight Engine  

### ✔ Dashboard
- Displays real-time vehicle health  
- Prioritizes service needs  
- Triggers customer notification  
- Displays RCA & security events  

---

## 3️⃣ Data Flow

1. ESP32 sends telemetry as JSON  
2. Dashboard ingests values  
3. AI agents run on data  
4. Output → health scoring, alerts, schedule  
5. Results shown on dashboard  

---

## 4️⃣ Scalability

This architecture can be extended to:
- Azure IoT Hub  
- Azure Event Hub  
- SQL/NoSQL backend  
- ML pipelines (LSTM/RNN for RUL)  
- OEM enterprise integration  

---
