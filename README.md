# bluetooth-controlled-robot
Bluetooth controlled robot using Arduino Nano, HC-05, TB6612FNG and N20 gear motors.
# 🤖 Bluetooth Controlled Robot

A two-wheel Bluetooth-controlled robot built using **Arduino Nano, HC-05 Bluetooth module, TB6612FNG motor driver, and two N20 gear motors**.

## 📌 Project Overview

This project is a compact wireless robot controlled using an Android smartphone through Bluetooth.

The HC-05 receives commands from the mobile application and sends them to the Arduino Nano. The Arduino processes the commands and controls the two N20 motors through the TB6612FNG motor driver.

The robot supports:

* Forward movement
* Backward movement
* Left rotation
* Right rotation
* Stop
* Variable speed control
* Smooth acceleration

## 🧰 Components Used

| Component              | Quantity |
| ---------------------- | -------: |
| Arduino Nano           |        1 |
| HC-05 Bluetooth Module |        1 |
| TB6612FNG Motor Driver |        1 |
| N20 Gear Motor         |        2 |
| 2S Li-ion Battery      |        1 |
| Robot Chassis          |        1 |
| Wheels                 |        2 |

## 🔌 Pin Connections

### HC-05 → Arduino Nano

| HC-05 | Arduino Nano |
| ----- | ------------ |
| TXD   | D2           |
| RXD   | D3           |
| VCC   | 5V           |
| GND   | GND          |

> The HC-05 RXD connection uses a voltage divider to reduce the Nano's TX voltage.

### Arduino Nano → TB6612FNG

| Arduino Nano | TB6612FNG |
| ------------ | --------- |
| D5           | PWMA      |
| D7           | AIN1      |
| D6           | AIN2      |
| D8           | BIN1      |
| D9           | BIN2      |
| D10          | PWMB      |
| 5V           | VCC       |
| 5V           | STBY      |
| GND          | GND       |

### Motors

```text
Left N20 Motor  → A01 / A02
Right N20 Motor → B01 / B02
```

## 📱 Bluetooth Commands

| Command | Function      |
| ------- | ------------- |
| F       | Forward       |
| B       | Backward      |
| L       | Left          |
| R       | Right         |
| S       | Stop          |
| 1–9     | Speed control |
| Q       | Full speed    |

## ⚙️ Features

### Smooth Acceleration

The robot gradually increases motor PWM instead of immediately applying full power.

Example:

```text
0 → 20 → 40 → 60 → 80 → 100 → 120 → 140
```

This reduces sudden jerks during startup.

## 💻 Software

* Arduino IDE
* Embedded C/C++
* SoftwareSerial library
* Android Bluetooth Controller application

## 📂 Repository Structure

```text
bluetooth-controlled-robot/
│
├── Arduino_Code/
├── Circuit_Diagram/
├── CAD_Design/
├── Images/
└── README.md
```

## 🚀 Future Improvements

* Ultrasonic obstacle avoidance
* Line-following mode
* ESP32 upgrade
* Autonomous navigation
* Encoder-based speed control
* Wireless telemetry
* Mobile application with custom UI

## 👨‍💻 Author

**Deepak Kumar Dora**

Electrical Engineering
Odisha University of Technology and Research

---

⭐ If you find this project useful, feel free to explore the repository and build your own version.
