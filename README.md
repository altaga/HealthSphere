# HealthSphere

Holter monitor with heart rate analysis, Azure cloud based and dashboard.

<img src="https://i.ibb.co/6yJQnM4/4-heartdisease.png" width="800">

Always use technology to improve the world, if you are a black hat or gray hat hacker please abstain at this point ......... or at least leave your star to make me feel less guilty XP.

# Table of contents

* [Introduction](#introduction)
* [Materials](#materials)
* [Connection Diagram](#connection-diagram)
* [Azure Sphere and Azure Cloud Setup](#azure-sphere-and-azure-cloud-setup)
* [Arduino ECG Simulator Setup](#arduino-ecg-simulator-setup)
* [CloudMQTT Setup](#cloudmqtt-setup)
* [Laptop Setup](#laptop-setup)
* [Arm Setup](#arm-setup)
* [The Final Product](#the-final-product)
* [Future Rollout](#future-rollout)
* [References](#references)

## Introduction:

Our heart beats 115200 times a day, it is such a fine machinery that does not stop during our lives, however, not many people have the advantage to have this machinery in good condition, many factors of daily life can permanently affect cardiac function .

Factors such as:

- Sedentary.
- Do not eat a balanced diet.
- Drink alcoholic drinks along with energy drinks.
- A long ETC ...

Too many people must undergo cardiac tests frequently in expensive hospitals with gigantic measuring devices.

That's why I decided through AzureSphere's amazing technology to create a real-time heart rate monitoring system and perform a dashboard deployment.

<img src="https://i.ibb.co/s68S6fw/image.png" width="600">

## Materials:

Hardware:

- AzureSphere                                      x1.

https://www.newark.com/avnet/aes-ms-mt3620-sk-g/ms-sphere-iot-starter-kit/dp/02AH9206

- Arduino Mini Pro                                 x1.

https://www.amazon.com/Arduino-Pro-Mini-328-16MHz/dp/B004G53J5I

- 1k Resistors                                     x3.

https://www.amazon.com/dp/B072BL2VX1/ref=cm_sw_em_r_mt_dp_U_rCuJDbT70DG1J

- Standed-Core Wire                                x1.

https://www.adafruit.com/product/2987

Software:
- Azure Cloud.
- Mouse Recorder Premium.
- Node-Red.
- Arduino IDE.
- Python.
- Cloud MQTT.

## Connection Diagram:

This is the connection diagram of the system, but if you have a Arduino Mini pro 3.3v version you dont need the resistors:

<img src="https://i.ibb.co/LR8R4Pk/Arduino5v-bb.png" width="380"><img src="https://i.ibb.co/NLFvmnM/Arduino3-3-bbb.png" width="360">

Services Connection Diagram:

<img src="https://i.ibb.co/Qm0FnMm/Health-Spehrre.png" width="800">

## Azure Sphere and Azure Cloud Setup:

The initial configuration of Azure Sphere is a bit long, however I totally recommend the official Microsoft documentation, because the instructions are very clear.

- https://docs.microsoft.com/en-us/azure-sphere/

Github Azure Samples (These samples are for the Azure Sphere from an earlier version, however the chip is the same, so most of the samples work on this Azure Sphere verison):

- https://github.com/Azure/azure-sphere-samples

Azure Devices Heat Map:

- Azure Heat Map: http://avnet.me/azsphere-kit-map

### Arduino ECG Simulator Setup:

Before starting, the ECG is composed of the following graph and we will call this segment PT.

<img src = "https://i.ibb.co/QKVHfw3/image.png" width = "500">

To perform the ECG simulator, it was first necessary to have real data from an ECG. As a biomedical engineer, i had my ECG data on my computer, so i did the following:

<img src = "https://i.ibb.co/T2xTSJh/image.png" width = "800">

From my ECG I only took a PT section that looked good.

<img src = "https://i.ibb.co/qYw5RVq/image.png" width = "800">

After you need process the data in a way that could be interpreted as integer numbers, through rounding and amplification, the following graph remains.

<img src = "https://i.ibb.co/1XBqMY7/image.png" width = "800">

We can note that the numbers are already integers, now in some simple way we should be able to pass them to an Arduino array, this was achieved easily by saving the data horizontally and as a CSV, so that we will have the following.

<img src = "https://i.ibb.co/ZhHytxX/image.png" width = "300">

These comma separated values it can be easily passed to arduino as an array.

    unsigned int ECG [100] = {156,161,158,157, ...... 163,166,160};

The complete code is in the "Arduino Code" folder, open in Arduino IDE and flash on your Arduino board, open the plotter monitor and you will see my ECG simulated by the Arduino.

<img src = "https://i.ibb.co/xqTR742/image.png" width = "1000">

The simulator will send the heart rate data every 10 seconds to the Azure Sphere, , in the simulation you will also notice that the frequency changes.
- The Azure Sphere will send the HR to Azure IoT Hub each time the Arduino sends the serial HR data to 115200.
(We are considering that the device that would measure the heart rate in the patient is communicated by Serial)
- The simulator changes the frequency every 10 seconds, to be a little more realistic.

### Widget Configuration:

Press the button to create the widget.

<img src = "https://i.ibb.co/zZSCtkK/image.png" width = "500">

We assign the model to the device.

<img src = "https://i.ibb.co/wC98Vs3/image.png" width = "500">

We create a widget as shown in the image.

<img src = "https://i.ibb.co/tD5b4F3/image.png" width = "500">

We finish the widget.

<img src = "https://i.ibb.co/dkB1cJ0/image.png" width = "500">

We will get a result like the following.

<img src = "https://i.ibb.co/2shLmdn/image.png" width = "500">

### Obtaining Credentials.

Save External access token and User ID.

<img src = "https://i.ibb.co/DCcdzCP/image.png" width = "500">

## CloudMQTT Setup:

Create an account in Cloud MQTT.

https://www.cloudmqtt.com/

Copy the credentials of "Server", "User", "Password" and "Port".

<img src = "https://i.ibb.co/s9wR395/image.png" width = "1000">

## Laptop Setup:

Install Python Anaconda so that you can easily manipulate the MQTT broker, this had to be done because the Arduino library ESP32 for MQTT does not accept connectivity such as Websocket.

https://www.anaconda.com/distribution/

Then install this library:

    pip install paho-mqtt

Download the file Python Files, open "MQTTRehab.py" and put your credentials.

## Arm Setup:

Follow this diagram without making a mistake, IF YOU DON'T CONNECT IT WELL YOU CAN DO A SHORT CIRCUIT:

<img src="https://hackster.imgix.net/uploads/attachments/942233/68747470733a2f2f692e6962622e636f2f4832344451384e2f41524d2d62622e706e67.png" width="800">

After connecting all program the ESP32 with the code in the "Arduino Files" folder.

<img src="https://www.e-ika.com/images/thumbs/0005376_placa-esp32-wifi-bluetooth_600.jpeg" width="800">

Open the "ESP32ARMRehab.ino" file and enter the CloudMQTT credentials.

    const char* ssid = "YOURSSID";
    const char* password =  "YOURPASS";
    const char* mqttServer = "m12.cloudmqtt.com";
    const int mqttPort = 12345;
    const char* mqttUser = "YOURCLOUDMQTTUSER";
    const char* mqttPassword = "YOURCLOUDMQTTPASS";

## The Final Product:

Robotic Arm:

<img src="https://i.ibb.co/X3JNNLB/DSC00056-2.jpg" width="800">
<img src="https://i.ibb.co/HHM2DQ1/DSC00059-2.jpg" width="800">

ESP32 Arm Driver:

<img src="https://i.ibb.co/mJ73KNs/DSC00068.jpg" width="800">

Brainium Module:

<img src="https://i.ibb.co/cFZrYdJ/DSC00061-2.jpg" width="800">
<img src="https://i.ibb.co/kgds0Xn/DSC00062-2.jpg" width="800">
<img src="https://i.ibb.co/xFm1f0T/DSC00063-2.jpg" width="800">

Complete system:

<img src="https://i.ibb.co/dMb7c6V/DSC00066-2.jpg" width="800">

### Our Epic DEMO:

Video: Click on the image
[![Rehab](https://i.ibb.co/Bjg48mh/Brainium-Rehab.png)](https://youtu.be/GYoLvldvk-s)

Sorry github does not allow embed videos.

## Future Rollout:

 inventa algo

## References:

Links 

