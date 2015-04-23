#ifndef AIRSensor_h
#define AIRSensor_h

#include "Arduino.h"

// Increase if you need more samples. Decrease if you need more memory.
#define MAX_SENSOR_SAMPLES_COUNT 10

struct AIRSensorModel {
    float scale;
    float power;
};

// You can find these for other sensor models by fitting a power curve to measured sensor data: analog_value v. distance_in_cm.
const AIRSensorModel kAIRSensor_36 = {3539.0,-1.08225};

class AIRSensor {
  public:
    AIRSensor(){};

    void Init(int pinIR, AIRSensorModel model);

    // Raw A2D value of sensor.
    int   rawValue();
    // Distance in cm. 
    // The calculation is based on calibration data for specific sensor model.
    float distance();

    // Update measurements.
    void Update();

    // Example 1
    // samplesCount = 1
    // samplesPerUpdate = 1
    // So you'd then just get instantaneous values of the sensor.
    // This value would probably be noisy and innacurate.

    // Example 2
    // samplesCount = 25
    // samplesPerUpdate = 25
    // You'd be taking 25 new samples on each update and you'd get the average.
    // This might make your update loop slow.

    // Example 3
    // samplesCount = 25
    // samplesPerUpdate = 1
    // Just get 1 sample per update, average the last 25 samples.
    // The value might lag the actual distance.

    // Number of samples to average.
    int  samplesCount();
    void setSamplesCount(int samplesCount);
    // Number of new samples to take each update.
    int  samplesPerUpdate();
    void setSamplesPerUpdate(int samplesPerUpdate);
    
  private:

    int rawValueIns();
    float distanceIns();
    float rawValueToDistance(float rawValue);

    int _samples[MAX_SENSOR_SAMPLES_COUNT];
    int _samplesIndex;
    int _pinIR;

    int _samplesCount;
    int _samplesPerUpdate;

    int _rawSum;
    int _rawAvg;

    int   _rawValueAvg;
    float _distanceAvg;

    AIRSensorModel _sensorModel;
};

#endif