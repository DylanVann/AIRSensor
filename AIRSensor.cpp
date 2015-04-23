#include "Arduino.h"
#include "AIRSensor.h"

void AIRSensor::Init(int pinIR, AIRSensorModel model) {
    _pinIR = pinIR;

    _samplesCount = MAX_SENSOR_SAMPLES_COUNT;
    _samplesPerUpdate = MAX_SENSOR_SAMPLES_COUNT;

    _sensorModel = model;
    pinMode(pinIR, INPUT);

    for (int i = 0 ; i < MAX_SENSOR_SAMPLES_COUNT ; i++) {
        _samples[i] = 0;
    }
}

int AIRSensor::rawValueIns() {return analogRead(_pinIR);}
float AIRSensor::distanceIns() {return rawValueToDistance(rawValueIns());}

int   AIRSensor::rawValue() {return _rawValueAvg;}
float AIRSensor::distance() {return _distanceAvg;}

float AIRSensor::rawValueToDistance(float rawValue) {
    return _sensorModel.scale * pow(rawValue, _sensorModel.power);
}

void AIRSensor::Update() {
    for (int i = 0 ; i < _samplesPerUpdate ; i++) {
        _samples[_samplesIndex++] = rawValueIns();
        _samplesIndex = (_samplesIndex + 1) % _samplesCount;
    }
    _rawSum = 0;
    _rawAvg = 0;
    for (int i = 0 ; i < _samplesCount ; i++) {
        _rawSum += _samples[i];
    }
    _rawAvg = (float)_rawSum / (float)_samplesCount;
    _rawValueAvg = _rawAvg;
    _distanceAvg = rawValueToDistance(_rawAvg);
}

int  AIRSensor::samplesCount() {return _samplesCount;}
void AIRSensor::setSamplesCount(int samplesCount) {
    _samplesCount = samplesCount;
}

int AIRSensor::samplesPerUpdate() {return _samplesPerUpdate;}
void AIRSensor::setSamplesPerUpdate(int samplesPerUpdate) {
    _samplesPerUpdate = samplesPerUpdate;
}