# ESP32 LoRa Gateway & Node

**P2P LoRa (SX1278 433 MHz) with HTTPS Cloud Forwarding**

![Platform](https://img.shields.io/badge/Platform-ESP32%20%7C%20ESP32--S3-blue)
![LoRa](https://img.shields.io/badge/LoRa-SX1278%20433MHz-orange)
![Protocol](https://img.shields.io/badge/Protocol-LoRa%20P2P-brightgreen)
![Payload](https://img.shields.io/badge/Payload-JSON-yellow)
![Cloud](https://img.shields.io/badge/Cloud-HTTPS-blueviolet)
![Status](https://img.shields.io/badge/Status-Production--Ready-success)

## Overview

This project implements a **Point-to-Point (P2P) LoRa communication
system** using **ESP32 / ESP32-S3** and **SX1278 (433 MHz)** modules.

-   A **LoRa Node** sends sensor data as a JSON payload
-   A **LoRa Gateway** receives the packet and forwards it to a **cloud
    server using HTTPS POST**

The system is suitable for **IoT deployments**, including agriculture,
industrial monitoring, and remote telemetry.

## System Architecture

\[ LoRa Node \] → JSON over LoRa (433 MHz) → \[ ESP32-S3 Gateway \] →
HTTPS POST → \[ Cloud Server / API \]

## Hardware Requirements

### Gateway

-   ESP32-S3
-   SX1278 LoRa Module (433 MHz)
-   WiFi connection

### Node

-   ESP32 / ESP8266
-   SX1278 LoRa Module (433 MHz)

## LoRa Configuration

Frequency: 433 MHz\
Sync Word: 0xA5\
Mode: P2P\
TX Power: 17 dBm\
Payload: JSON

## Example Payload

{ "nodeId": "test-node", "moisture": 123 }

## License

MIT License

## Maintained By

ThingsLinker\
Custom IoT Solutions \| Embedded Systems \| LoRa & Cloud Integration
