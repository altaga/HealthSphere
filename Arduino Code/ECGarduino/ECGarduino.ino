#include <SoftwareSerial.h>

unsigned int ECG[100]={156,161,158,157,158,157,157,150,150,147,148,142,141,136,142,141,145,139,141,148,172,200,210,209,240,268,268,249,234,207,178,161,127,121,112,109,108,108,102,108,101,53,244,564,814,979,673,90,0,6,52,111,112,118,118,124,129,128,132,133,136,138,144,139,148,151,157,158,174,180,185,193,209,220,233,249,272,287,288,274,258,233,210,189,177,170,160,154,149,156,151,154,154,157,157,163,163,163,166,160};
long Frec[20]={80,89,90,100,120,110,111,89,87,89,97,110,107,100,98,89,98,110,100,83};
long frec=80;
long dela = 600/frec;;
unsigned long time;
unsigned long times;
int j = 0;

SoftwareSerial mySerial(10, 12); // RX, TX

void setup() {
   Serial.begin(115200); 
     while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(115200);
  time=millis();
}

void loop() {  
  for(int i =0; i<100;i++)
  {  
  if (Serial.available()) {
    frec= Serial.readString().toInt();
    dela=600/frec;
  } 
    Serial.println(ECG[i]);
    delay(dela);
  if((millis()-time)>10000)
  {
  dela=600/Frec[j];
  frec=Frec[j];
  mySerial.print(String(frec));
  mySerial.print('\n');
  time=millis();  
  j++;
  if(j==20)
  {
    j=0;
  }
  }
  }
}
