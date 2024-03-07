# 514-Final

[.com/Jessijiaqi/514-Final/files/13948150/CatFit.Feeder.pdf)](https://docs.google.com/presentation/d/1FDsYHbtQ7m_ZgoqTDy0RWQkhZ9aAJe4xorWv4srN26U/edit?usp=sharing)
## PawsPassage System

![未命名作品 16](https://github.com/Jessijiaqi/514-Final/assets/148395825/1e02a7ce-a87e-466c-bbb4-d5e3d76fbdb6)
It's a smart pet door system designed to assist free-roaming kittens in entering their home. The sensor device, positioned near the door, detects animals approaching and identifies whether the creature at the doorstep is a household pet. If recognized, the door automatically opens, and the pet’s basic information, such as duration outside, is displayed on an indoor screen. Conversely, if an unrecognized animal approaches, the system emits a warning signal.

### Sensor Device
![未命名作品 22](https://github.com/Jessijiaqi/514-Final/assets/148395825/aee8a842-0252-4b9b-8ab1-46326fba32f0)
- MCU **ESP32**: For BLE system and manage ML and sensor data.
- Motion Sensor:**HC-SR501** detect when an animal is approaching the door. 
- **Camera attached to ESP32**: The camera can be used for identifying the household cat's face: serve as a "Cat Face ID".

### Display Device
![未命名作品 19](https://github.com/Jessijiaqi/514-Final/assets/148395825/32567d52-5377-4285-849c-46ae5611d3d1)
- **LED**：LEDs can show the circuit being connected.
- A switch：Control circuit energised
- Servo Motor: **SG90** Control the door’s mechanism.
- Stepper Motor Model: **X27.168** Indicate the door‘s state
- MCU:**ESP32**

### Device Connection
![image](https://github.com/Jessijiaqi/514-Final/assets/148395825/f755df34-5b50-4df1-a686-822f433406dc)
<img width="915" alt="截屏2024-01-16 21 36 53" src="https://github.com/Jessijiaqi/514-Final/assets/148395825/2ae873f1-7000-4eee-8e0a-28c4033c0fcb">


