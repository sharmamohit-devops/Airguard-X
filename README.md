# 🔥 AIRGUARD-X — Smart Indoor Air Safety & Alert System

🔗 **Live Simulation (Wokwi)**  
👉 Try the working prototype directly in your browser:  
https://wokwi.com/projects/452734940595574785

---

AIRGUARD-X is an **Arduino-based real-time indoor air safety monitoring and alert system**, developed as a **hackathon project for IIT Jodhpur**.  
The project focuses on **human safety, embedded system design, and practical engineering**, rather than just displaying air quality numbers.

It continuously monitors **hazardous gases and environmental conditions** and provides **clear, immediate alerts** using an LCD, buzzer, LEDs, and serial console logging — all **without requiring internet connectivity**.

---

## 🏫 Hackathon Context — IIT Jodhpur

This project was **designed and implemented specifically for a hackathon environment**, where the emphasis is on:

- Real-world problem relevance  
- Clear system logic  
- Reliability over complexity  
- Safety-first design philosophy  

AIRGUARD-X aligns with **IIT Jodhpur’s focus on applied sensing, embedded intelligence, and system-level engineering thinking**.

---

## ❓ Why This Problem Matters

Indoor air hazards are often **silent and underestimated**, especially in:

- Closed rooms
- Hostels & PGs
- Kitchens
- Laboratories
- Small industrial spaces

Common real-world issues include:
- Carbon Monoxide poisoning during winters
- LPG leakage accidents
- Poor ventilation leading to toxic gas accumulation
- High temperature & humidity stressing occupants and equipment

Most low-cost AQI monitors:
- Only show numbers
- Do not explain *what is dangerous*
- Do not provide strong alerts during emergencies

---

## 🎯 Problem Statement

> **How can we design a low-cost, offline, and reliable system that continuously monitors indoor air and environmental conditions and gives immediate, understandable alerts during hazardous situations?**

AIRGUARD-X addresses this by combining **multiple sensors**, **event-driven logic**, and **clear annunciation**, similar to industrial safety panels.

---

## 🧠 Why AIRGUARD-X is Helpful

### 🔴 Immediate Life-Saving Alerts
- Loud buzzer can wake occupants during sleep
- LCD clearly shows *why* the alert occurred  



### 🟡 Multi-Hazard Detection
- Detects **multiple gases at the same time**
- Does not hide secondary dangers

### 🟢 Dynamic & Honest Monitoring
- If air becomes safe again → system shows **SAFE**
- No ghost or stale alarms

### 🔌 Offline Reliability
- Works without Wi-Fi or internet
- Suitable for power/network failure scenarios

### 🎓 Educational & Scalable
- Ideal for hackathons, labs, and embedded learning
- Easy to extend to IoT, GSM, or cloud systems

---

## 🛠️ Hardware Components

| Component | Purpose |
|--------|-------|
| Arduino Uno | Main controller |
| MQ-7 Sensor | Carbon Monoxide (CO) |
| MQ-2 Sensor | LPG / Smoke |
| MQ-135 Sensor | NH₃ / NOx / Toxic gases |
| DHT22 Sensor | Temperature & Humidity |
| 16×2 I2C LCD | Status & alert display |
| Buzzer | Audible alarm |
| Red LED | Danger indication |
| Green LED | Safe indication |

---

## ⚙️ How the System Works

### 1️⃣ Sensor Monitoring
- Gas sensors provide analog values (0–1023)
- Values are mapped to **approximate ppm** for stable demo and simulation
- DHT22 provides temperature & humidity

### 2️⃣ Independent Evaluation
- Each sensor is checked independently
- Multiple hazards can be detected simultaneously

### 3️⃣ Alert Logic
- If **any parameter crosses a safe limit**, system enters **DANGER state**
- If **all parameters return to safe**, system switches back to **SAFE state**

### 4️⃣ Output & Logging
- LCD shows clear alert reason
- Buzzer and LEDs provide immediate feedback
- Serial console logs data and state changes

---

## 🚨 Alert Thresholds (Demo-Oriented)

| Parameter | Alert Condition |
|--------|----------------|
| CO | ≥ 20 ppm |
| LPG / Smoke | ≥ 20 ppm |
| NH₃ / NOx | ≥ 20 ppm |
| Temperature | ≥ 45 °C |
| Humidity | ≥ 85 % |

*(Thresholds are configurable and can be calibrated for real deployment.)*

---

## 📟 System States

### 🟢 SAFE
- Air quality normal
- Green LED ON
- LCD shows:
AIR SAFE
ENV NORMAL


### 🔴 DANGER
- One or more hazards detected
- Red LED + Buzzer ON
- LCD shows exact cause:


DANGER DUE TO CO + LPG


---

## 🧪 Example Serial Output

```text
CO:12 LPG:8 NH3:5 TEMP:28 HUM:45
AIR SAFE

CO:12 LPG:35 NH3:5 TEMP:28 HUM:45
DANGER DUE TO: LPG

CO:12 LPG:5 NH3:5 TEMP:28 HUM:45
AIR SAFE

🧠 Engineering Design Decisions

Dynamic monitoring instead of alarm latching

Alerts clear automatically when conditions improve

No internet dependency

Works reliably in offline environments

State-based LCD updates

Prevents flickering and unnecessary screen refresh

Event-based serial logging

Logs only when values or state changes

These decisions follow principles used in industrial safety panels and embedded monitoring systems.

🔮 Future Scope

ESP32 + cloud dashboard

GSM-based SMS alerts

Mobile app notifications

Data logging to SD card

Battery + solar backup

Industrial-grade sensor calibration

👨‍💻 Project & Contribution

This project was implemented with a focus on:

Correctness

Safety

Explainability

Practical system behavior

Rather than adding unnecessary features, the goal was to build a clean, reliable, and demonstrable safety system, suitable for hackathons and future research work.

📜 License

This project is open-source and free to use for educational and non-commercial purposes.

⭐ Built for IIT Jodhpur Hackathon
🔧 Designed with real-world indoor safety in mind

---

## 🎯 FINAL TIP (VERY IMPORTANT)

If a judge or recruiter opens your GitHub:

1️⃣ They see **Live Demo link first**  
2️⃣ They understand **why the problem matters**  
3️⃣ They see **clear engineering thinking**  
4️⃣ They trust the system behavior  

This README already does that job for you.

---

Agar chaho next:
- Hackathon **2-minute pitch script**
- **Resume bullet points**
- **Poster / PPT slide content**
- **Block diagram explanation**

Bas bolo — **next kya prepare karein?** 🚀
