# Nerf Automatic Shooting Target with Arduino

## Overview
This project implements an **Interactive Shooting Target** using **Arduino Board Mega 2560**, **Servo Motor**, **LCD Display**, **Bluetooth Module HC-05** and **Analog Sensors**. The game allows the player to set the timer, hit the moving target, and see the score displayed on the LCD screen.

---

## Features
- Time-based target shooting game
- Servo motor-controlled target movement
- Real-time score display on **LCD I2C 16x2**
- Adjustable game time via **Serial Communication**
- Automatic target reset
- Countdown timer display
- Sensor-based hit detection

---

## How It Works
1. The player sets the desired time through **Bluetooth Serial Communication**.
2. The target moves automatically using the servo motor.
3. The player shoots at the target, and hits are detected via **Analog Sensors**.
4. The target automatically raises back up after being hit.
5. Each hit increases the player's score.
6. The remaining time and score are displayed on the **LCD**.
7. When the timer reaches zero, the game stops, and the final score is shown.
---

### Prerequisites
- Arduino IDE
- Required Libraries:
  - Servo
  - TimerOne
  - TimerThree
  - LiquidCrystal_I2C

## Wiring Diagram
1. Connect the **Servo Motor** to pin **8**.
2. Connect the **Analog Sensor** to pin **A0**.
3. Connect the **LCD I2C Display** to the I2C pins (**SDA** and **SCL**).
4. Connect the **Bluetooth HC-05 Module** to the Arduino board:
   - RX to **TX1**
   - TX to **RX1**
5. Power the setup using a **9V Battery**.

---

## How to Use
1. Upload the code to the **Arduino Mega 2560 Board**.
2. Pair the **Bluetooth Module HC-05** with your phone or computer.
3. Use a **Bluetooth Terminal App** or **Serial Monitor** to set the game time (0-180 seconds).
4. Start shooting at the moving target.
5. The LCD screen will display the time remaining and score in real time.
6. When the timer reaches zero, the game will automatically stop, and the final score will be displayed.

