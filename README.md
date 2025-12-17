# Smart Fire Risk Detection System Using ESP32-C3 and FreeRTOS (DHT11-Based)

This project implements a **real-time fire risk detection system** using the **Seeed Studio XIAO ESP32-C3** and **FreeRTOS**.  
Instead of gas sensors, the system detects **fire-prone conditions** by monitoring **temperature and humidity** using a **GRV-DHT11 sensor**.

Fire risk is identified when **high temperature** and **low humidity** occur simultaneously, which is a common early indicator of fire hazards in smart home environments.

---

## System Features

- Real-time **temperature and humidity monitoring**
- Fire-risk detection based on environmental conditions
- OLED display for live system status
- Audible and visual alerts (buzzer and LEDs)
- Interrupt-based hazard simulation using pushbuttons
- FreeRTOS multi-tasking architecture
- Event-driven emergency handling
- Modular and scalable firmware design

---

## System Architecture

![System Architecture](images/system_architecture.png)

---

## Hardware Components

| Component | Description |
|----------|-------------|
| ESP32-C3 (Seeed Studio XIAO) | Main MCU running FreeRTOS |
| GRV-DHT11 | Temperature & humidity sensor |
| OLED (SSD1306, I²C) | Displays system readings and alerts |
| Buzzer | Audible fire-risk alert |
| LEDs (Red, Green, Yellow) | System status indicators |
| Pushbuttons | ISR-based fire-risk simulation |
| Breadboard & Jumper Wires | Prototyping |

---

## GPIO Mapping

| Device | GPIO |
|------|------|
| DHT11 DATA | GPIO 8 |
| OLED SDA | GPIO 9 |
| OLED SCL | GPIO 10 |
| Buzzer | GPIO 5 |
| Red LED | GPIO 3 |
| Green LED | GPIO 4 |
| Yellow LED | GPIO 2 |
| Button 1 (High Temp Sim) | GPIO 0 |
| Button 2 (Low Humidity Sim) | GPIO 1 |

---

## Fire Risk Detection Logic

Fire risk is detected when:
- **Temperature > 35°C**
- **Humidity < 30% RH**

When both conditions are met:
- Red LED turns ON
- Buzzer is activated
- OLED displays **“FIRE RISK DETECTED”**

---

## FreeRTOS Task Overview

### **Task 1 — DHT11 Sensor Task**
- Reads temperature and humidity every 2 seconds
- Sends data via a **Message Buffer**

### **Task 2 — Fire Risk Monitor Task**
- Receives sensor data
- Evaluates fire-risk conditions
- Sets **Event Group flags**
- Notifies Emergency Task

### **Task 3 — Emergency Alert Task**
- Triggered using **Task Notifications**
- Controls buzzer and LEDs
- Displays warning messages on OLED
- Clears event flags after handling

### **Task 4 — Display Task**
- Continuously updates OLED with live readings
- Uses a **mutex** to protect OLED access

---

## Interrupt Handling

Two pushbuttons are used to simulate abnormal conditions:
- **Button 1:** Simulates high temperature
- **Button 2:** Simulates low humidity

Interrupt Service Routines (ISRs):
- Set event flags
- Notify Emergency Task
- Exit quickly to maintain RTOS stability

![ISR Flow](images/isr_flow.png)

---

## Task Interaction

![Task Interaction](images/task_interaction.png)

---

## Source Code Structure

# Smart Fire Risk Detection System Using ESP32-C3 and FreeRTOS (DHT11-Based)

This project implements a **real-time fire risk detection system** using the **Seeed Studio XIAO ESP32-C3** and **FreeRTOS**.  
Instead of gas sensors, the system detects **fire-prone conditions** by monitoring **temperature and humidity** using a **GRV-DHT11 sensor**.

Fire risk is identified when **high temperature** and **low humidity** occur simultaneously, which is a common early indicator of fire hazards in smart home environments.

---

## System Features

- Real-time **temperature and humidity monitoring**
- Fire-risk detection based on environmental conditions
- OLED display for live system status
- Audible and visual alerts (buzzer and LEDs)
- Interrupt-based hazard simulation using pushbuttons
- FreeRTOS multi-tasking architecture
- Event-driven emergency handling
- Modular and scalable firmware design

---

## System Architecture

![System Architecture](images/system_architecture.png)

---

## Hardware Components

| Component | Description |
|----------|-------------|
| ESP32-C3 (Seeed Studio XIAO) | Main MCU running FreeRTOS |
| GRV-DHT11 | Temperature & humidity sensor |
| OLED (SSD1306, I²C) | Displays system readings and alerts |
| Buzzer | Audible fire-risk alert |
| LEDs (Red, Green, Yellow) | System status indicators |
| Pushbuttons | ISR-based fire-risk simulation |
| Breadboard & Jumper Wires | Prototyping |

---

## GPIO Mapping

| Device | GPIO |
|------|------|
| DHT11 DATA | GPIO 8 |
| OLED SDA | GPIO 9 |
| OLED SCL | GPIO 10 |
| Buzzer | GPIO 5 |
| Red LED | GPIO 3 |
| Green LED | GPIO 4 |
| Yellow LED | GPIO 2 |
| Button 1 (High Temp Sim) | GPIO 0 |
| Button 2 (Low Humidity Sim) | GPIO 1 |

---

## Fire Risk Detection Logic

Fire risk is detected when:
- **Temperature > 35°C**
- **Humidity < 30% RH**

When both conditions are met:
- Red LED turns ON
- Buzzer is activated
- OLED displays **“FIRE RISK DETECTED”**

---

## FreeRTOS Task Overview

### **Task 1 — DHT11 Sensor Task**
- Reads temperature and humidity every 2 seconds
- Sends data via a **Message Buffer**

### **Task 2 — Fire Risk Monitor Task**
- Receives sensor data
- Evaluates fire-risk conditions
- Sets **Event Group flags**
- Notifies Emergency Task

### **Task 3 — Emergency Alert Task**
- Triggered using **Task Notifications**
- Controls buzzer and LEDs
- Displays warning messages on OLED
- Clears event flags after handling

### **Task 4 — Display Task**
- Continuously updates OLED with live readings
- Uses a **mutex** to protect OLED access

---

## Interrupt Handling

Two pushbuttons are used to simulate abnormal conditions:
- **Button 1:** Simulates high temperature
- **Button 2:** Simulates low humidity

Interrupt Service Routines (ISRs):
- Set event flags
- Notify Emergency Task
- Exit quickly to maintain RTOS stability

![ISR Flow](images/isr_flow.png)

---

## Task Interaction

![Task Interaction](images/task_interaction.png)

---

## Source Code Structure

src/
 ├── app_main.c
 ├── tasks_common.h
 ├── dht11_task.c
 ├── monitor_task.c
 ├── emergency_task.c
 ├── display_task.c
 ├── lcd1602_driver.h
 └── lcd1602_driver.c


---

## OLED Output Examples

Temp: 29°C
Humidity: 55%
Status: NORMAL

Temp: 38°C
Humidity: 25%
Status: FIRE RISK


---

## Video Demonstration

A video demonstration is embedded in the web-based report and shows:
- Live temperature and humidity readings
- Normal and fire-risk conditions
- LED and buzzer activation
- ISR-triggered fire-risk simulation
- FreeRTOS task behavior

---

## Web-Based Report

This repository is hosted using **GitHub Pages** as a web-based project report, including:
- System architecture diagrams
- Hardware and firmware explanation
- RTOS concepts and synchronization mechanisms
- Embedded video demonstration

---

## Academic Note

The GRV-DHT11 sensor was selected for its simplicity and suitability for RTOS-based educational projects. While it offers limited accuracy compared to industrial sensors, it is sufficient for demonstrating real-time monitoring, task scheduling, and event-driven fire-risk detection.

---

## License

This project is developed for academic and educational purposes.
