# 🗑️ Smart Dustbin IoT (ESP32 + Telegram Notification)

## 📌 Overview

Smart Dustbin IoT adalah sistem tempat sampah pintar berbasis ESP32 yang mampu membuka tutup otomatis, mendeteksi tingkat kepenuhan sampah, serta mengirim notifikasi Telegram secara real-time ketika sampah penuh.

Project ini merupakan implementasi sistem tertanam (Embedded System) yang mengintegrasikan sensor, aktuator, LCD display, WiFi, dan notifikasi berbasis internet.

---

## 🚀 Features

- ✅ Automatic lid opening using ultrasonic sensor
- ✅ Waste level monitoring
- ✅ Real-time Telegram notification
- ✅ LCD I2C status display
- ✅ NTP time synchronization (WIB / GMT+7)
- ✅ WiFi connectivity (Secure HTTPS)

---

## 🛠️ Hardware Components

- ESP32
- 2x Ultrasonic Sensor (HC-SR04)
- Servo Motor
- LCD I2C 20x2
- Jumper Wires
---

## 💻 Software & Libraries

**IDE:**
- Arduino IDE

**ESP32 Board Package**

**Libraries Used:**
- WiFi.h
- WiFiClientSecure.h
- UniversalTelegramBot.h
- ArduinoJson.h
- NTPClient.h
- WiFiUdp.h
- ESP32Servo.h
- LiquidCrystal_I2C.h

---

## ⚙️ System Architecture

Ultrasonic Sensor (Lid)  →  ESP32  →  Servo Motor  
Ultrasonic Sensor (Level) → ESP32 → LCD Display  
ESP32 → WiFi → Telegram Bot API  
ESP32 → NTP Server (Time Sync)  

---

## 📊 How It Works

### 1️⃣ Automatic Lid Opening
Jika tangan terdeteksi dengan jarak < 40 cm:
- Servo membuka tutup tempat sampah secara otomatis.

### 2️⃣ Waste Level Detection
Jika tinggi sampah < 10 cm:
- LCD menampilkan "Sampah Penuh"
- ESP32 mengambil waktu dari NTP server
- Mengirim notifikasi Telegram ke user

### Example Telegram Message:

```
Sampah Penuh !!!
Tanggal : 12 / Januari / 2026
Pukul : 14:32 WIB
```

---

## 🌐 Networking Implementation

Project ini menggunakan:

- WiFi Mode: Station (WIFI_STA)
- Secure HTTPS communication (Telegram API)
- NTP Time Synchronization (GMT +7)
- Multi Chat ID Notification support

Project ini menunjukkan implementasi dasar IoT berbasis internet dan real-time monitoring system.

---

## 🔐 Security Note

Untuk keamanan, jangan pernah mengupload:

- SSID asli
- Password WiFi
- Telegram Bot Token

Gunakan placeholder seperti:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
#define BOTtoken "YOUR_BOT_TOKEN";
```

---

## 📂 Project Structure

```
Smart-Dustbin-ESP32/
│
├── SmartDustbin.ino
├── README.md
└── docs/
    └── Laporan_UAS_Sistem_Tertanam.pdf
    ├── rangkaian.jpg
    ├── alat.jpg
```

---

## 👨‍💻 My Role

- Embedded system programming (ESP32)
- Sensor integration
- Telegram API integration
- Network configuration
- NTP implementation
- System logic & debugging

---

## 🎯 Skills Demonstrated

- IoT Development
- Embedded Systems
- Sensor & Actuator Integration
- Secure API Communication
- Networking Configuration
- Real-time Monitoring System
- Microcontroller Programming

