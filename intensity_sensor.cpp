#include "thingProperties.h"
#include <BH1750FVI.h>

// Create the Lightsensor instance
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  LightSensor.begin();

  pinMode(LED_BUILTIN, OUTPUT);

  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);


  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  light = LightSensor.GetLightIntensity();
  delay(1000);

}

/*
  Since LED is READ_WRITE variable, onLEDChange() is
  executed every time a new value is received from IoT Cloud.
*/

void onLEDChange()  {
  // Add your code here to act upon LED change
  DigitalWrite(LED_BUILTIN, LED);
}
