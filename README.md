# 514-Final
[CatFit Feeder.pdf](https://github.com/Jessijiaqi/514-Final/files/13948150/CatFit.Feeder.pdf)
## PawsPassage System

![未命名作品 16](https://github.com/Jessijiaqi/514-Final/assets/148395825/1e02a7ce-a87e-466c-bbb4-d5e3d76fbdb6)
It's a smart pet door system designed to assist free-roaming kittens in entering their home. The sensor device, positioned near the door, detects animals approaching and identifies whether the creature at the doorstep is a household pet. If recognized, the door automatically opens, and the pet’s basic information, such as duration outside, is displayed on an indoor screen. Conversely, if an unrecognized animal approaches, the system emits a warning signal.

### Sensor Device
![未命名作品 22](https://github.com/Jessijiaqi/514-Final/assets/148395825/aee8a842-0252-4b9b-8ab1-46326fba32f0)
- Microchip Scanner **DX-B (ISO 11784/11785 compliant)**: The core sensor for identifying pets. It reads the microchip implanted in the pet to determine if it's a registered household animal.
  OR BLE system:ESP32 as the receiver .
- Motion Sensor:**HC-SR501 or AM312** detect when an animal is approaching the door. Technologies like PIR (Passive Infrared) are common for such applications.
- **Camera Raspberry Pi Camera Module V2**: Optionally, a camera can be used for additional security and to visually confirm the identity of the animal.
- MCU:**ESP32**

### Display Device
![未命名作品 19](https://github.com/Jessijiaqi/514-Final/assets/148395825/32567d52-5377-4285-849c-46ae5611d3d1)
- **RGB LED**：LEDs can be used for status indicators (e.g.low battery, pet inside/outside)
- Tactile push button：A simple button for user interaction, such as resetting counters, changing modes, or silencing alarms. 
- Servo Motor: **MG996R** For precise control of the door's movement.
  https://dronebotworkshop.com/esp32-servo/
  https://esp32io.com/tutorials/esp32-mg996r
- Stepper Motor Model: **28BYJ-48** (with ULN2003 Driver Board)This is a small, affordable stepper motor that is sufficient for moving a gauge needle. It can indicate various statuses, like battery level or the number of times the pet has used the door.
- MCU:**ESP32**

### Device Connection
![image](https://github.com/Jessijiaqi/514-Final/assets/148395825/f755df34-5b50-4df1-a686-822f433406dc)
<img width="915" alt="截屏2024-01-16 21 36 53" src="https://github.com/Jessijiaqi/514-Final/assets/148395825/2ae873f1-7000-4eee-8e0a-28c4033c0fcb">


