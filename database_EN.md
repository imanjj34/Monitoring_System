# 🏢 Smart Attendance & Boarding System (ESP32 + Cloudflare)

## 📌 Overview

This project is a **smart attendance and residential management system** designed for environments such as:

- Dormitories (Panison / Boarding houses)
- Offices
- Workshops
- Educational centers

It is built using:

- ESP32 (RFID / hardware device)
- Cloudflare Workers (Backend API)
- Cloudflare D1 (Database)
- REST API Architecture

---

# 🧠 System Architecture


ESP32 Device
↓
Cloudflare Worker API
↓
Authentication (API Key)
↓
Business Logic (User / Device / Event Processing)
↓
Cloudflare D1 Database
↓
Response to Device / Client


---

# 🗄️ Database Schema

---

## 👤 USERS (System Users)

### Purpose:
Represents real people in the system (students, residents, employees)

| Field | Type | Description | Values |
|------|------|-------------|--------|
| id | INTEGER | Unique identifier | Auto Increment |
| full_name | TEXT | Full name | "Ali Ahmadi" |
| employee_id | TEXT | User code | "EMP001", "S12345" |
| status | INTEGER | Active status | 1 = active / 0 = inactive |
| created_at | TEXT | Creation timestamp | datetime |

---

## 🔑 DEVICES (ESP32 / Gate Systems)

### Purpose:
Hardware devices that send data to the system

| Field | Type | Description | Values |
|------|------|-------------|--------|
| id | INTEGER | Device ID | Auto |
| device_name | TEXT | Device name | "Gate A" |
| api_key | TEXT | Authentication key | "abc123xyz" |
| location | TEXT | Physical location | "Entrance / Room A" |
| active | INTEGER | Device status | 1 / 0 |
| created_at | TEXT | Creation time | datetime |

---

## 🪪 CARDS (RFID / UID Mapping)

### Purpose:
Links RFID cards to users

| Field | Type | Description | Values |
|------|------|-------------|--------|
| id | INTEGER | Card ID | Auto |
| user_id | INTEGER | Related user | FK → users |
| uid | TEXT | RFID UID | "A1B2C3D4" |
| active | INTEGER | Status | 1 / 0 |
| created_at | TEXT | Creation time | datetime |

---

## 📊 ATTENDANCE (Core System Table)

### Purpose:
Stores all movement events of users

| Field | Type | Description | Values |
|------|------|-------------|--------|
| id | INTEGER | Record ID | Auto |
| user_id | INTEGER | Related user | FK → users |
| device_id | INTEGER | Device used | FK → devices |
| uid | TEXT | Raw card UID | "A1B2C3D4" |
| event | TEXT | Event type | see below |
| created_at | TEXT | Timestamp | datetime |

---

### 📌 Event Types

#### 🟢 Entry / Exit

check_in
check_out


#### 🟡 Break Management

break_start
break_end


#### 🏠 Boarding / Room Tracking

room_in
room_out
temporary_leave
return


---

## 🪵 LOGS (System Monitoring)

### Purpose:
Tracks system events, errors, and debugging info

| Field | Type | Description | Values |
|------|------|-------------|--------|
| id | INTEGER | Log ID | Auto |
| device_id | INTEGER | Device reference | FK |
| message | TEXT | Log message | "invalid api key" |
| level | TEXT | Severity | info / warn / error |
| created_at | TEXT | Timestamp | datetime |

---

# 🔗 Relationships


USERS
├── CARDS (1 → many)
└── ATTENDANCE (1 → many)

DEVICES
└── ATTENDANCE (1 → many)

LOGS
└── DEVICES


---

# ⚙️ System Logic Flow

ESP32 sends request
Worker validates API key
Device is identified
UID is received
User is resolved via cards
Event is recorded in attendance
Response returned

---

# 🏢 System Capabilities

✔ Real-time attendance tracking  
✔ RFID-based identification  
✔ Multi-device support  
✔ Break / leave tracking  
✔ Boarding-style movement tracking  
✔ Secure API authentication  
✔ Cloud-based scalable backend  

---

# 🚀 Future Improvements

- Admin dashboard (web panel)
- Real-time user status (inside/outside)
- Attendance analytics (daily/monthly reports)
- Work-time calculation engine
- ESP32 hardware integration (RFID reader)
- Mobile app support

---

# 🧠 Summary

This system is not just a simple attendance tracker.

It is a **full smart movement tracking system** designed for real-world environments like dormitories and residential buildings.
