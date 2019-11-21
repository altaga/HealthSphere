float frec = 0;                       // initialize frecuency variable.
unsigned long time1;                  // initialize first R time segment Reference.
unsigned long time2;                  // initialize second R time segment Reference.
int i=0;                              // initialize counter var.
void setup() 
{
  Serial1.begin(115200);              // Start Serial1.
  time1=millis();                     // First time reference.
}

void loop() 
{
  int lec = analogRead(A6);           // Taking the ADC value.
  if(lec > 650)                       // Set the 650 R value reference.
  {
    time2=millis();                   // Taking the second time reference.
    frec+=((60*1000)/(time2-time1));  // Get heart rate in beats per minute.
    time1=millis();                   // Taking the first time reference for the next segment. 
    i++;                              // Add 1 to counter.
    if(i>10)
    {
      frec/=11;                       // Getting the average of 11 frequency samples.
      Serial1.println((int)frec);     // Send the average to Azure Sphere (BT Serial Communication)
      i=0;                            // Restart counter
      frec = 0;                       // Restart frecuency value
    }
    delay(100);                       // Wait for the R wave to end, to prevent the algorithm from detecting the same R wave, the entire QRS segment lasts between 60 and 100 milliseconds, a delay of 100 milliseconds will work perfectly.
  }
}
