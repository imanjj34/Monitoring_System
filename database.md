# 🧠 دیتابیس نهایی سیستم حضور و غیاب

---

## 1. 👤 USERS (کاربران)

### 🎯 هدف:
افراد واقعی (کارمندها / دانشجوها / پرسنل)

### 📊 ستون‌ها:

| ستون | نوع | توضیح | مقادیر |
|------|-----|--------|---------|
| id | INTEGER | شناسه یکتا | خودکار (Auto Increment) |
| full_name | TEXT | نام کامل کاربر | "Ali Ahmadi" |
| employee_id | TEXT | کد پرسنلی | "EMP001", "S12345" |
| status | INTEGER | وضعیت فعال بودن | 1 = فعال / 0 = غیرفعال |
| created_at | TEXT | زمان ثبت | datetime خودکار |

### ⚠️ نکته:
- employee_id باید UNIQUE باشد  
- status برای حذف نرم (Soft Delete)

---

## 2. 🔑 DEVICES (دستگاه‌ها - ESP32)

### 🎯 هدف:
دستگاه‌هایی که دیتا ارسال می‌کنند

### 📊 ستون‌ها:

| ستون | نوع | توضیح | مقادیر |
|------|-----|--------|---------|
| id | INTEGER | شناسه دستگاه | Auto Increment |
| device_name | TEXT | نام دستگاه | "Gate 1" |
| api_key | TEXT | کلید امنیتی دستگاه | "abc123xyz" |
| location | TEXT | محل نصب | "Entrance A" |
| active | INTEGER | فعال بودن دستگاه | 1 / 0 |
| created_at | TEXT | زمان ثبت | datetime |

### ⚠️ نکته مهم:
- api_key مهم‌ترین بخش امنیت سیستم است  
- اگر active = 0 → دستگاه اجازه ارسال ندارد

---

## 3. 🪪 CARDS (کارت RFID / UID)

### 🎯 هدف:
اتصال کارت به کاربر

### 📊 ستون‌ها:

| ستون | نوع | توضیح | مقادیر |
|------|-----|--------|---------|
| id | INTEGER | شناسه کارت | Auto |
| user_id | INTEGER | کاربر مرتبط | FK → users.id |
| uid | TEXT | کد RFID | "A1B2C3D4" |
| active | INTEGER | فعال بودن کارت | 1 / 0 |
| created_at | TEXT | زمان ثبت | datetime |

### ⚠️ نکته:
- یک کاربر می‌تواند چند کارت داشته باشد  
- uid باید UNIQUE باشد  

---

## 4. 📊 ATTENDANCE (ورود و خروج)

### 🎯 هدف:
ثبت هر حرکت ورود/خروج

### 📊 ستون‌ها:

| ستون | نوع | توضیح | مقادیر |
|------|-----|--------|---------|
| id | INTEGER | شناسه رکورد | Auto |
| user_id | INTEGER | کاربر شناسایی شده | FK → users |
| device_id | INTEGER | دستگاه ثبت کننده | FK → devices |
| uid | TEXT | UID خام کارت | "A1B2C3D4" |
| event | TEXT | نوع رویداد | "enter" / "exit" |
| created_at | TEXT | زمان ثبت | datetime |

### ⚠️ نکته مهم:
- این جدول “هسته سیستم” است  
- همه گزارش‌ها از اینجا ساخته می‌شوند  

---

## 5. 🪵 LOGS (لاگ سیستم)

### 🎯 هدف:
ردیابی خطاها و رفتار سیستم

### 📊 ستون‌ها:

| ستون | نوع | توضیح | مقادیر |
|------|-----|--------|---------|
| id | INTEGER | شناسه | Auto |
| device_id | INTEGER | دستگاه مرتبط | FK |
| message | TEXT | پیام | "invalid api key" |
| level | TEXT | سطح اهمیت | info / warn / error |
| created_at | TEXT | زمان | datetime |

---

# 🔗 ارتباط بین جدول‌ها
USERS
│
├── CARDS (1 به چند)
│
└── ATTENDANCE (1 به چند)

DEVICES
└── ATTENDANCE (1 به چند)

LOGS
└── DEVICES (اختیاری)


---

# 🧩 جریان واقعی سیستم


ESP32
↓ (api_key)
Worker
↓
Validate Device
↓
Read UID
↓
Find User (via cards)
↓
Insert Attendance
↓
Return Response


---

# ⚙️ نکات طراحی حرفه‌ای (خیلی مهم)

### 1. event فقط این‌ها باشد:
- enter  
- exit  

---

### 2. status فقط:
- 0 = inactive  
- 1 = active  

---

### 3. زمان:

datetime('now')
