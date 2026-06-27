# Dormitory Attendance and Rest Monitoring System

## 📝 System Overview
The system is designed to monitor student attendance, temporary exits, and rest room usage in a dormitory. Student identification is performed using secure RFID cards. The system records all activities and stores them in a cloud database.

---

## 🎯 Objectives
* Record student attendance.
* Record temporary exits.
* Record rest room usage.
* Calculate daily rest duration.
* Provide real-time status information.
* Send daily SMS reports to parents.
* Minimize hardware complexity.
* Operate reliably with intermittent Internet connectivity.

---

## 🛠️ Hardware Components
* **ESP32** microcontroller
* Secure **RFID reader**
* Secure **RFID cards**
* **Push button** for Rest Mode
* **SIM800 GSM** module
* **Wi-Fi connection**
* **OLED display** (optional)
* **Buzzer** and **status LEDs**

---

## 💻 Software Components
* ESP32 firmware
* REST API
* Cloudflare Worker
* Cloudflare D1 Database

---

## 👥 User Roles

### Student
* Scan RFID card
* Start rest mode
* Enter or leave the dormitory

### Dormitory Supervisor
* Register students
* Issue RFID cards
* Revoke lost cards
* Register manual attendance
* View live status
* View reports

---

## 🗂️ Student Information
Each student record contains:
* Student ID
* Student name
* RFID card ID
* Parent phone number
* Current status

---

## 🔒 RFID Security
* Each student receives a unique secure RFID card.
* Only the encrypted card identifier is used.
* Personal information is stored only in the cloud database.
* Lost cards can be revoked immediately.
* New cards can be assigned without changing student information.

---

## 🔄 Attendance Workflow

1.  **Dormitory Entry**
    * The student scans the RFID card.
    * The system records `Dorm In`.
2.  **Rest Start**
    * The student presses the Rest button.
    * The student scans the RFID card.
    * The system records `Rest Start`.
3.  **Rest End**
    * The student scans the RFID card again.
    * The system records `Rest End`.
4.  **Temporary Exit**
    * The next RFID scan is recorded as `Dorm Out`.
5.  **Re-entry**
    * The following RFID scan is recorded as `Dorm In`.

> *The sequence continues throughout the day.*

---

## 📊 Event Types
* `Dorm In`
* `Dorm Out`
* `Rest Start`
* `Rest End`

---

## 💾 Event Storage
Every event contains:
* Student ID
* Event type
* Timestamp
* Device ID
* Event sequence number

---

## ☁️ Cloud Services

### Cloudflare Worker provides:
* REST API
* Authentication
* Event processing
* Report generation

### Cloudflare D1 stores:
* Students
* Parent phone numbers
* RFID information
* Attendance events
* Daily reports
* Device information

---

## 📡 Communication
* ESP32 communicates with Cloudflare Worker through **HTTPS**.
* All event synchronization uses **JSON** messages.
* If the Internet is unavailable, events are stored locally and synchronized automatically when the connection is restored.

---

## 📋 Daily Report
At a predefined time every day:
1.  ESP32 requests the daily report from Cloudflare Worker.
2.  Worker calculates daily statistics.
3.  Worker returns:
    * Student name
    * Parent phone number
    * Total rest duration
    * Number of dormitory entries
    * Number of temporary exits

---

## 💬 SMS Notification
* ESP32 receives the report from Cloudflare Worker.
* The SIM800 module sends an SMS directly to each student's parent.
* The SMS may contain:
    * Student name
    * Date
    * Total rest duration
    * Number of dormitory entries
    * Number of temporary exits

---

## 🔍 Real-Time Monitoring
The dormitory supervisor can request:
* Students currently inside the dormitory
* Students outside the dormitory
* Students in the rest room
* Daily attendance records
* Rest duration reports

---

## 🔌 Offline Operation
* The system continues operating without Internet access.
* Events are stored locally.
* All pending events are synchronized automatically after reconnection.

---

## 🛡️ Security Features
* Secure RFID authentication
* HTTPS communication
* Device authentication
* Encrypted API communication
* Centralized cloud database
* Card revocation support
* Event integrity verification

---

## 🚀 System Advantages
* Low hardware cost
* Simple architecture
* Cloud-based database
* Remote management
* Secure RFID authentication
* Automatic synchronization
* Automatic daily reporting
* Direct SMS notification
* Easy scalability
* Suitable for real-world deployment

---

## 📐 System Architecture

```text
                  Cloudflare Worker
                  REST API + D1 Database
                           ▲
                           │ HTTPS
                           │
                      Wi-Fi Network
                           │
                        ESP32
     ┌──────────┬──────────┬──────────┬──────────┐
     │          │          │          │
 RFID Reader  Button     SIM800     OLED/Buzzer
     │
 Secure RFID Cards
