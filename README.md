# Firebase ESP32 Sensor Data Logger

This project demonstrates how to use an ESP32 to send and retrieve sensor data from Firebase Realtime Database.

## Overview

The project connects an ESP32 to a Wi-Fi network and communicates with Firebase to log and retrieve sensor data. The example uses a Light Dependent Resistor (LDR) as a sensor to send data to Firebase every second and retrieve the latest data from Firebase every 5 seconds.

## Hardware Requirements

- ESP32
- LDR (Light Dependent Resistor)
- Resistor (e.g., 10k ohm)
- Breadboard and jumper wires

## Software Requirements

- Arduino IDE
- [Firebase ESP Client Library for Arduino](https://github.com/mobizt/Firebase-ESP-Client)
- Wi-Fi network

## Circuit Diagram

Connect the LDR to the ESP32 as shown below:

