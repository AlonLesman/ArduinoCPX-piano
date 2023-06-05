/*
  Blynk App - The lazy parent
  The app is designed mostly for parents who want to monitor their kids from far and 
  wake them up with with a nice song in the morning. 
  The parent has a collection of 2 wake up call songs - "take on me" and "the lion sleeps tonight".
  They also have access to data about the room in which their child is sleeping in - light level, temperature and sound level for monitoring their child.
  This data is displayed in the app and is constantly being updated. 
  Moreover to wake up their child they can light up their room using the cpx by
  displaying a rainbow of colors on the board. This is a feature that many kids like and see it as a morning surprise. 


  Here is a link for a video demonstration of our app: 
  
 
*/

#include <Adafruit_CircuitPlayground.h>
#include "Lights.h"
#include "soft_song.h"
#include "A_Weema_Weh.h"


// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL6KT_I6iPX"
#define BLYNK_TEMPLATE_NAME "LazyParent"
#define BLYNK_AUTH_TOKEN "RKYfci9GfZCVvQI1ouJ1LYdp7oqBEI32"


// Comment this out to disable prints and save space
#define BLYNK_PRINT SerialUSB
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lesman";
char pass[] = "0528994250";

// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1


// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void setup()
{
  CircuitPlayground.begin();
  CircuitPlayground.strip.clear();
  // Debug console
  SerialUSB.begin(115200);
  // CircuitPlayground.begin();

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
}

unsigned long lastSent;
int i =0;

void loop()
{
  Blynk.run();
  if(millis() - lastSent > 1000){


    //Gets the temperature and send it to virtual pin V1(reducing bias)
    float temperature = CircuitPlayground.temperature() - 10;
    Blynk.virtualWrite(V0, temperature);

    //Gets the light level and send it to virtual pin V0
    int lightLevel = CircuitPlayground.lightSensor();
    Blynk.virtualWrite(V1, lightLevel);

    //Gets the sound level and send it to virtual pin V2(reducing bias)
    int soundLevel = CircuitPlayground.mic.soundPressureLevel(20);
    Blynk.virtualWrite(V2, soundLevel-55);
    lastSent = millis();
  }
}



BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable

  if(pinValue == 1)
  {
    rainbow();
  }
}


BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // Assigning incoming value from pin V4 to a variable

  if(pinValue == 1)
  {
    TakeOnMe();
  }
  
}

BLYNK_WRITE(V5)
{
  int pinValue = param.asInt(); // Assigning incoming value from pin V5 to a variable
  if(pinValue == 1)
  {
    LionsSong();
  }
}





