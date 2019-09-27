# -*- coding: utf-8 -*-
"""
Created on Thu Sep 26 01:59:30 2019

@author: VAI
"""
import json
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

try:  
    open_file=open("datain.txt",'r')
    file_lines=open_file.readlines()
    file = file_lines[0].strip()  # First Line
    loc_file = file_lines[1].strip()  # Second Line
    var=file_lines[1].strip()+file_lines[2].strip()+file_lines[3].strip()+file_lines[4].strip()+file_lines[5].strip()+file_lines[6].strip()
    var = json.loads(var)
    var = var["event"]["payload"]
    print(var)
except IndexError:  
        print ("Index Error" )
else:  
    # The callback for when the client receives a CONNACK response from the server.    
    client = mqtt.Client()
    client.on_connect = on_connect
    
    client.username_pw_set("USER", "PASSWORD")
    
    client.connect("SERVER", PORT)
    
    client.publish("/Azure", var)
    
