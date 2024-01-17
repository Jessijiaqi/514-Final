# 514-Final
[CatFit Feeder.pdf](https://github.com/Jessijiaqi/514-Final/files/13948150/CatFit.Feeder.pdf)
## PawsPassage System

![未命名作品 16](https://github.com/Jessijiaqi/514-Final/assets/148395825/1e02a7ce-a87e-466c-bbb4-d5e3d76fbdb6)
It's a smart pet door system designed to assist free-roaming kittens in entering their home. The sensor device, positioned near the door, detects animals approaching and identifies whether the creature at the doorstep is a household pet. If recognized, the door automatically opens, and the pet’s basic information, such as duration outside, is displayed on an indoor screen. Conversely, if an unrecognized animal approaches, the system emits a warning signal.

### Sensor Device
![未命名作品 22](https://github.com/Jessijiaqi/514-Final/assets/148395825/aee8a842-0252-4b9b-8ab1-46326fba32f0)
- Microchip Scanner DX-B (ISO 11784/11785 compliant): The core sensor for identifying pets. It reads the microchip implanted in the pet to determine if it's a registered household animal.
- Motion Sensor: HC-SR501To detect when an animal is approaching the door. Technologies like PIR (Passive Infrared) are common for such applications.
- Camera Raspberry Pi Camera Module V2: Optionally, a camera can be used for additional security and to visually confirm the identity of the animal.
- MCU:ESP32
