/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <dht.h>
#include "Timer.h"

#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;

float temp;
Timer t;
bool airconditioner = false;

IRsendRaw mySender;



void setup() {
  Serial.begin(9600);
  delay(2000); 
  while (!Serial); //delay for Leonardo
  Serial.println(F("DHT11 Humidity & temperature Sensor\n\n"));
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */
#define RAW_DATA_LEN 212
uint16_t rawDataOn[RAW_DATA_LEN]={
  3378, 3418, 406, 1302, 402, 482, 378, 1302, 
  402, 1302, 406, 478, 382, 478, 378, 1298, 
  406, 482, 378, 1302, 402, 478, 382, 1298, 
  406, 478, 382, 1302, 402, 1298, 406, 1302, 
  406, 478, 382, 478, 378, 1302, 402, 482, 
  378, 478, 382, 1298, 406, 1302, 402, 482, 
  378, 1298, 406, 482, 378, 1302, 402, 482, 
  378, 1298, 406, 478, 382, 478, 382, 478, 
  378, 1302, 406, 1298, 406, 1298, 406, 1302, 
  402, 1302, 406, 478, 378, 482, 378, 482, 
  378, 478, 378, 482, 378, 1302, 402, 1302, 
  406, 478, 378, 1302, 406, 478, 378, 478, 
  382, 478, 382, 1298, 406, 1298, 406, 1302, 
  402, 482, 378, 478, 382, 1298, 406, 478, 
  382, 478, 378, 482, 378, 478, 382, 478, 
  378, 482, 378, 482, 378, 478, 378, 482, 
  378, 478, 382, 478, 378, 482, 378, 478, 
  382, 478, 378, 482, 378, 478, 382, 478, 
  378, 482, 378, 478, 378, 482, 378, 482, 
  378, 478, 382, 478, 378, 478, 382, 478, 
  382, 478, 378, 478, 382, 478, 382, 478, 
  378, 482, 378, 478, 378, 482, 378, 478, 
  382, 478, 378, 482, 378, 478, 382, 478, 
  378, 1302, 406, 478, 378, 482, 378, 478, 
  382, 478, 382, 478, 378, 478, 382, 478, 
  378, 1302, 406, 1298, 406, 478, 382, 478, 
  378, 482, 378, 1000};


#define RAW_DATA_LEN 212
uint16_t rawDataOff[RAW_DATA_LEN]={
  3346, 3450, 398, 1306, 374, 486, 398, 1306, 
  402, 1302, 402, 458, 374, 482, 374, 1334, 
  370, 486, 374, 1334, 370, 486, 374, 1334, 
  386, 470, 374, 1334, 398, 1306, 374, 1330, 
  374, 486, 374, 482, 374, 1334, 374, 482, 
  402, 458, 374, 1330, 378, 1330, 374, 482, 
  374, 1334, 370, 486, 374, 1334, 398, 458, 
  374, 1330, 374, 486, 374, 486, 374, 482, 
  374, 1334, 398, 1306, 374, 1330, 374, 1330, 
  374, 1334, 374, 482, 374, 486, 374, 486, 
  374, 482, 374, 486, 374, 1330, 402, 1306, 
  374, 482, 374, 486, 374, 482, 374, 486, 
  402, 1302, 402, 1306, 374, 1330, 398, 462, 
  402, 454, 378, 482, 374, 1330, 374, 486, 
  374, 486, 374, 482, 402, 458, 374, 486, 
  374, 482, 374, 486, 374, 482, 402, 462, 
  370, 486, 374, 486, 370, 486, 374, 486, 
  374, 482, 378, 482, 402, 458, 374, 482, 
  402, 458, 374, 486, 370, 486, 374, 486, 
  402, 458, 374, 482, 374, 486, 374, 486, 
  374, 482, 374, 486, 374, 486, 374, 482, 
  402, 458, 374, 482, 374, 486, 402, 458, 
  374, 486, 398, 458, 374, 486, 370, 486, 
  378, 1330, 374, 482, 374, 486, 374, 486, 
  374, 482, 374, 1334, 398, 1306, 374, 486, 
  370, 1334, 402, 1302, 374, 486, 374, 482, 
  386, 474, 402, 1000};


#define RAW_DATA_LEN 212
uint16_t rawDataSpin[RAW_DATA_LEN]={
  3398, 3434, 406, 1270, 406, 434, 406, 1270, 
  402, 1274, 402, 434, 406, 458, 378, 1270, 
  406, 430, 406, 1270, 406, 434, 406, 1270, 
  402, 434, 406, 1270, 406, 1270, 406, 1270, 
  406, 434, 402, 434, 406, 1266, 406, 434, 
  406, 458, 378, 1270, 406, 1270, 406, 458, 
  378, 1274, 402, 434, 406, 1270, 406, 434, 
  406, 1266, 406, 434, 406, 434, 402, 434, 
  406, 1270, 406, 1270, 402, 1274, 406, 1270, 
  406, 1270, 406, 434, 402, 462, 378, 430, 
  406, 462, 378, 462, 378, 1270, 402, 1274, 
  406, 430, 406, 1270, 406, 434, 402, 434, 
  406, 458, 378, 1274, 402, 1274, 406, 1270, 
  406, 430, 406, 434, 406, 1270, 406, 438, 
  398, 434, 406, 458, 378, 458, 382, 434, 
  402, 434, 406, 434, 402, 434, 406, 430, 
  406, 458, 382, 430, 406, 434, 406, 434, 
  406, 430, 406, 458, 378, 434, 406, 462, 
  378, 430, 406, 434, 406, 430, 406, 434, 
  406, 430, 406, 430, 410, 430, 406, 434, 
  406, 430, 406, 434, 406, 430, 410, 430, 
  406, 430, 406, 434, 406, 430, 410, 430, 
  406, 434, 406, 430, 406, 430, 406, 434, 
  406, 430, 406, 430, 410, 1270, 406, 430, 
  410, 430, 406, 430, 406, 1270, 406, 434, 
  406, 430, 410, 1266, 410, 430, 406, 430, 
  410, 430, 406, 1000};

/*
 * Cut-and-paste into the area above.
 */
 
unsigned long start = millis();
unsigned long delaytime = 1800000;

void WriteToSerial(){
   if(temp > 29  and airconditioner == true){
      airconditioner = false;
      Serial.println(airconditioner);
    }
    else if(temp < 26 and airconditioner == false){
      airconditioner = true;
      Serial.println(airconditioner);
    }
}

void loop() {
  DHT.read11(dht_apin);
  temp = DHT.temperature;
  Serial.print("temperature = ");
  Serial.print(temp); 
  Serial.println(" C");

  t.every(600000,WriteToSerial);
  t.update();

  if (temp > 28 and airconditioner == false ) {
    mySender.send(rawDataOn,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequency
    airconditioner = true;
    Serial.println(airconditioner);
    Serial.println(F("AC Switched On"));
    delay(10000);
    mySender.send(rawDataSpin,RAW_DATA_LEN,36);
    Serial.println(F("AC is Spinning"));
  }
  else if (temp < 27 and airconditioner == true) {
    mySender.send(rawDataOff,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequency
    airconditioner = false;
    Serial.println(airconditioner);
    Serial.println(F("AC Switched Off"));
  }
  delay(5000);
}
