# Dormitory Attendance and Rest Monitoring System

## 📝 System Overview
The system monitors student attendance, temporary exits, and rest room usage in a dormitory. Student identification is performed using secure RFID cards. The system records events locally when needed and synchronizes them with a cloud database.

---

## 🎯 Objectives
* Record student attendance.
* Record temporary exits.
* Record rest room usage.
* Calculate daily rest duration.
* Provide real-time status information.
* Minimize hardware complexity.
* Operate reliably with intermittent Internet connectivity.
* Keep SMS notifications disabled by default, with support for end-of-day reporting only.

---

## 🛠️ Hardware Components
* **ESP32** microcontroller
* Secure **RFID reader**
* Secure **RFID cards**
* **Push button** for Rest Mode
* **SIM800 GSM** module (optional for future use)
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
    * The next RFID card scan ends rest.
    * The system records `Rest End`.
4.  **Temporary Exit**
    * After rest ends, the next RFID scan can record `Dorm Out`.
5.  **Re-entry**
    * The following RFID scan is recorded as `Dorm In`.

> *Students may skip rest mode and go directly from `Dorm In` to `Dorm Out` if needed. It's also possible to end rest and then exit the dormitory.*

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
* The system attempts cloud sync immediately and retries as often as possible.
* Duplicate scans are ignored if the same card is read again within a short delay.
* If the network remains unavailable after retries, the event is kept locally as a fallback so it is not lost.
* When connectivity is restored, the ESP32 retries sending all pending local events to the cloud after a short delay.

---

## 📋 Daily Report
Daily reporting is generated at the end of the day. The system also tracks the first dorm entry event separately for status monitoring.

---

## 💬 SMS Notification
* SMS notifications are disabled by default.
* Daily SMS summaries are only intended for the end-of-day report, not for repeated entries during the same day.
* The SIM800 module is available for future activation, but it is not required for current operation.

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
```