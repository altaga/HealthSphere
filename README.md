# HealthSphere

Holter monitor with heart rate analysis, Azure cloud based and dashboard.

<img src="https://i.ibb.co/6yJQnM4/4-heartdisease.png" width="800">

Always use technology to improve the world, if you are a black hat or gray hat hacker please abstain at this point ......... or at least leave your star to make me feel less guilty XP.

# Table of contents

* [Introduction](#introduction)
* [Materials](#materials)
* [Connection Diagram](#connection-diagram)
* [Azure Sphere and Azure Cloud Setup](#azure-sphere-and-azure-cloud-setup)
* [Arduino Holter Monitor](#arduino-holter-monitor)
* [Azure CLI Setup](#azure-cli-setup)
* [Recieve Data and Save](#recieve-data-and-save)
* [Setup Python Code](#setup-python-code)
* [Node-Red Setup](#node-red-setup)
* [Automate all](#automate-all)
* [The Final Product](#the-final-product)
* [Our Epic DEMO](#our-epic-demo)
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
- Visual Studio
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

You need to save the following data for later.

- Hubname.

<img src="https://i.ibb.co/nCdM4ZD/Capture.png" width="800">

- Device id.

<img src="https://i.ibb.co/DLCsknw/Untitled-1.png" width="800">

- ID Scope

<img src="https://i.ibb.co/qmVG7HK/dvdsfsd.png" width="800">

- Auth Number (Azure Sphere CLI)

        azsphere tenant show-selected

<img src="https://i.ibb.co/3kNZ6HY/sdavxzc-Xc.png" width="800">

Remember to download the program for the Azure Sphere called "Health Sphere", once you download it, open it with VS and in the file "app_manifiest.json"

- Write ID Scope in  "CmdArgs": [ "xxxxxxxxxxxxx" ]
- Write Hubname in "AllowedConnections": [ "global.azure-devices-provisioning.net", "xxxxxxxxxxxxxx.azure-devices.net" ]
- Write Auth Number in "DeviceAuthentication": "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

        {
          "SchemaVersion": 1,
          "Name": "AvnetStarterKit-Hackster.io-V1.0",
          "ComponentId": "685f13af-25a5-40b2-8dd8-8cbc253ecbd8",
          "EntryPoint": "/bin/app",
          "CmdArgs": [ "xxxxxxxxxxxxx" ],
          "Capabilities": {
            "AllowedConnections": [ "global.azure-devices-provisioning.net", "xxxxxxxx.azure-devices.net" ],
            "AllowedTcpServerPorts": [],
            "AllowedUdpServerPorts": [],
            "Gpio": [ 0, 4, 5, 8, 9, 10, 12, 13, 34 ],
            "Uart": [ "ISU0" ],
            "I2cMaster": [ "ISU2" ],
            "SpiMaster": [],
            "WifiConfig": true,
            "NetworkConfig": false,
            "SystemTime": false,
            "DeviceAuthentication": "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
          }
        }

Github Azure Samples (These samples are for the Azure Sphere from an earlier version, however the chip is the same, so most of the samples work on this Azure Sphere verison):

- https://github.com/Azure/azure-sphere-samples

Azure Devices Heat Map:

- Azure Heat Map: http://avnet.me/azsphere-kit-map

## Arduino Holter Monitor:

Before starting, the EKG is composed of the following graph and we will call this segment PT.

<img src = "https://i.ibb.co/QKVHfw3/image.png" width = "500">

La frecuencia cardiaca, se obtiene primordialmente de obtener la distancia entre los picos de la grafica, a esto se le llama segmento RR.

<img src = "https://ccenf.pt/portals/0/Images/ecgs/ekg.png" width = "800">

En este caso la frecuencia la obtendremos mediante un algoritmo implementado en arduino.

- Primero obtenemos los rangos en los cuales esta trabajando nuestro modulo AD8232.



## Azure CLI Setup:

To install the Azure CLI you need to follow the following tutorial according to your OS.

- https://docs.microsoft.com/en-us/cli/azure/install-azure-cli?view=azure-cli-latest

Enter the following command to get the Azure IoT extension

     az extension add --name azure-cli-iot-ext

After that log in to your azure account.

    az login

Once this is finished we can check that the data is being sent well to Azure IoT Hub. Run the following command replacing HUBNAME and DEVICEID with your data.

    az iot hub monitor-events --hub-name HUBNAME --device-id DEVICEID
        
We are receiving in the payload the heart rate every 10 seconds as we set it in the Arduino code.

<img src = "https://i.ibb.co/Sv34gxF/Console.png" width = "600">

## Recieve Data and Save.

To send the data, what I did was a process of saving, processing and sending the data "Manually", however, in the end I will show how everything can be automated through a MACRO.

- The first step is to execute the following command, this command will save all the information received by Azure CLI in a file.

       az iot hub monitor-events --hub-name HUBNAME --device-id DEVICEID> datain.txt

- Since we are receiving the data every 10 seconds, we will only have to wait 10 seconds to execute the command before stopping it with CTRL + C, inside the datain.txt file, we can find the received data.

<img src = "https://i.ibb.co/QXw9M5h/image.png" width = "600">

## Setup Python Code.

For the subsequent processing of the data we must configure the CloudMQTT credentials that we will use to send the data received from the CLI.

- Create an account in Cloud MQTT.

https://www.cloudmqtt.com/

- Copy the credentials of "Server", "User", "Password" and "Port".

<img src = "https://i.ibb.co/s9wR395/image.png" width = "1000">

Within the python code we will change the following parameters for our credentials.

     client.username_pw_set ("USER", "PASSWORD")
     client.connect ("SERVER", PORT)

Once we have the data there, we must execute the Exe.py program in the "Python Code" folder, this will process the data and send it to the CloudMQTT with the topic "/ Azure"

## Node-Red Setup:

Node Red is a tool for NodeJS where we can integrate services easily, without code and, of course, create excellent dashboards.

NodeJS installation guide: https://www.guru99.com/download-install-node-js.html

NodeRED installation guide: https://nodered.org/docs/getting-started/windows

NodeRED installation guide: https://flows.nodered.org/node/node-red-dashboard

The file "flows.json" in the folder "Node-RED Flow", has all the information to import the flow into your NodeRED.

<img src = "https://i.ibb.co/c11ZJT8/image.png" width = "600">
<img src = "https://i.ibb.co/nBL3M23/image.png" width = "600">

Once that is done we will edit the MQTT node to enter our credentials.

<img src = "https://i.ibb.co/GQdDKtk/image.png" width = "600">

Set Server and Port.

<img src = "https://i.ibb.co/wdzbztp/image.png" width = "600">

Set User and Password.

<img src = "https://i.ibb.co/cDjySLr/image.png" width = "600">

If everything works fine press the "Deploy" button and enter the following URL to check the Dashboard.

http://localhost:1880/ui

If we execute the Exe.py file, we will see how the data appears on the Dashboard.

<img src = "https://i.ibb.co/1fqQnfw/image.png" width = "800">

## Automate all:

To Automate everything, create a macro with a program called "Mouse Recorder Premium", the macro of that program is in the "Macro File" folder.

In this part of the macro we must change for our values, so that it works.

<img src = "https://i.ibb.co/fqx8Bfm/image.png" width = "800">

## The Final Product:

The interface:

<img src = "https://i.ibb.co/XxfSjhh/image.png" width = "800">

The device:

<img src = "https://i.ibb.co/0YfCDSg/20190927-025530.jpg" height = "300"><img src = "https://i.ibb.co/xSq4k24/20190927-025450.jpg" height = "300">

## Our Epic DEMO:

Video: Click on the image
[![Rehab](https://i.ibb.co/6yJQnM4/4-heartdisease.png)](https://youtu.be/da5jXiNS5is)

Sorry github does not allow embed videos.

## Future Rollout:

 inventa algo

## References:

Links
