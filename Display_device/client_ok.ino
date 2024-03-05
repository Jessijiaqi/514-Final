#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
// Client Code
#include "BLEDevice.h"
//#include "BLEScan.h"
#include <ESP32Servo.h>
#include <Stepper.h>


// 添加一个全局变量来记录上次开门的时间
unsigned long lastOpenTime = 0;
const unsigned long ignoreInterval = 12000; // 忽略时间间隔设置为12000毫秒（12秒）
// TODO: change the service UUID to the one you are using on the server side.
// The remote service we wish to connect to.
static BLEUUID serviceUUID("c655edda-4a85-4431-9707-e291f5dc715b");
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("8665bc3f-3bb3-49e9-aa00-6512a4668769");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;


// Button setup
const int buttonPin = 7; // Button pin
int buttonState = 0; // Variable for reading the button status


Servo myservo;
int servoPin = 5; // Servo control pin

// Stepper setup
const int stepsPerRevolution = 200; // Steps per revolution for stepper motor
Stepper myStepper(stepsPerRevolution, 1, 2, 3, 4); // Pins for stepper motor


void openTheDoor() {
    Serial.println("Opening the door...");

    // Rotate stepper motor one revolution clockwise
    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    myservo.write(90);
    delay(10000);

    // Rotate servo motor to 180 degree

    myservo.write(0); // Tell servo to go back to 0 degrees
    myStepper.step(-stepsPerRevolution);

    // Here you can add code to close the door if needed

    Serial.println("The door is now open.");
}

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)pData[i]);
    }
    Serial.println();

    // Check if the data is "open the door"
    String dataReceived = "";
    for (int i = 0; i < length; i++) {
        dataReceived += (char)pData[i];
    }
    if (dataReceived == "open the door") {
        // 获取当前时间
        unsigned long currentTime = millis();
        // 检查是否已经超过了忽略时间间隔
        if (currentTime - lastOpenTime >= ignoreInterval) {
            openTheDoor(); // 调用开门函数
            lastOpenTime = currentTime; // 更新上次开门的时间
        } else {
            Serial.println("Open door request ignored.");
        }
    }
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

bool connectToServer() {
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());

    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");
    pClient->setMTU(517); //set client to request maximum MTU from server (default is 23 otherwise)

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    if(pRemoteCharacteristic->canRead()) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);

    connected = true;
    return true;
}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

void setup() {
  
  myStepper.setSpeed(60); // Set stepper speed
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 5 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

   // Servo setup
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50); // Standard 50Hz servo
  myservo.attach(servoPin, 500, 2400); // Attach the servo on servoPin to the servo object

  // 设置按钮引脚为输入
  pinMode(buttonPin, INPUT);

} // End of setup.

// This is the Arduino main loop function.
void loop() {
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;

      Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    // Rotate servo motor to 180 degrees
    myservo.write(90); // Tell servo to go to 180 degrees
    delay(10000); // Waits 10 seconds at 180 degrees

    // Rotate servo motor back to 0 degrees
    myservo.write(0); // Tell servo to go back to 0 degree

    // Optional: Rotate stepper motor back to starting position
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
  }
      // 读取按钮状态
  

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    String newValue = "Time since boot: " + String(millis()/1000);
    Serial.println("Setting new characteristic value to \"" + newValue  + "\"");

    // Set the characteristic's value to be the array of bytes that is actually a string.
    pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
  }else if(doScan){
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }

  delay(1000); // Delay a second between loops.
} // End of loops
