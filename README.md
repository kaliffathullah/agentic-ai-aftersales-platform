# 🚗 Agentic AI Aftersales Platform  
### Predictive Maintenance • Autonomous Scheduling • AI Customer Engagement • RCA/CAPA • UEBA Security

This repository contains a complete working prototype of an **Agentic AI–powered aftersales management ecosystem** designed for automotive OEMs and service networks.  
The system provides **real-time vehicle telemetry**, **failure prediction**, **Remaining Useful Life (RUL)** estimation, **intelligent service scheduling**, and **customer engagement**, enabling a future-ready smart mobility ecosystem.

---

## 📌 1. Repository Structure

agentic-ai-aftersales-platform/
├── client/
│ └── firmware/
│ └── vehicle_telematics_firmware.ino
├── server/
│ └── dashboard/
│ └── index.html
├── docs/
│ ├── architecture.md
│ ├── data-flow.md
│ └── demo-script.md
└── README.md
---

## 📌 2. Project Overview

Modern vehicle service networks suffer from:

- Reactive maintenance instead of predictive  
- Manual communication with customers  
- No real-time service load balancing  
- No data-sharing between service centers & manufacturing teams  
- High cost of breakdowns and warranty failures  

This project introduces an **end-to-end Agentic AI Aftersales Platform**, consisting of:

### ✔ Vehicle-side ESP32 Firmware  
Simulates all major sensor domains and streams telemetry to the cloud.

### ✔ Cloud-side Agentic AI Dashboard  
Shows health scoring, predictions, scheduling, RCA/CAPA, and security events.

### ✔ AI Agents (Simulated)  
- Predictive Failure Agent  
- RUL Estimation Agent  
- Autonomous Scheduling Agent  
- Customer Engagement Agent  
- RCA/CAPA Insight Engine  
- UEBA Security Monitoring  

---

## 📌 3. Features

### 🚗 Vehicle Firmware Features
- Reads/simulates:
  - Engine & Powertrain sensors  
  - Brake System sensors  
  - Battery & Electrical System  
  - Tire & Wheel System  
  - Fuel & Emission System  
  - Safety signals + Lane event detection  
  - GPS coordinates  
- Generates structured JSON telemetry  
- Sends every 5 seconds  
- Works with or without hardware  

---

### 🖥️ Dashboard Features
- Live vehicle health visualization  
- Failure probability score  
- Remaining Useful Life (RUL)  
- Ranking of vehicles by urgency  
- Automatic service slot scheduling  
- RCA & CAPA generation  
- UEBA-based anomaly detection  
- Clean, professional UI  

---

## 📌 4. How to Run

### 1️⃣ Dashboard (Server)
Open:
server/dashboard/index.html


Runs fully offline.

### 2️⃣ Firmware (Client)
Flash using Arduino IDE:



client/firmware/vehicle_telematics_firmware.ino


Then open Serial Monitor to view telemetry.

---

## 📌 5. Demo Flow (Simplified)

1. Firmware sends vehicle telemetry →  
2. Dashboard displays real-time status →  
3. AI agents compute failure probability & RUL →  
4. Vehicle is ranked based on severity →  
5. Scheduling agent assigns nearest available service slot →  
6. Customer engagement agent generates notification →  
7. Manufacturing gets RCA/CAPA insights →  
8. UEBA monitors anomalies  

---

## 📌 6. Tech Stack

- ESP32 (Arduino)  
- HTML, CSS, JavaScript  
- JSON telemetry protocol  
- Agentic AI logic (simulated)  
- Cloud-ready architecture (Azure IoT compatible)

---

## 📌 7. About This Project

This prototype represents a **production-ready architecture** demonstrating how Indian OEMs can modernize aftersales operations using AI-driven automation.

---
