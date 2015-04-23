# AIRSensor

An improved Arduino IR sensor library.

# Features

- Adjusts raw sensor value to cm.
- Different sensor models can be added.
- Uses a ring buffer to average readings.
- Number of readings averaged and number taken per update can be changed.

## Example

~~~c++
#include <AIRSensor.h>

AIRSensor mySensor;

void setup(){

  Serial.begin(9600);

  int pinIRSensor = 0;
  mySensor.Init(pinIRSensor, kAIRSensor_36);

}

void loop() {

  mySensor.Update();
  Serial.println(mySensor.distance());

  delay(1000);
  
}
~~~
