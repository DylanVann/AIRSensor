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