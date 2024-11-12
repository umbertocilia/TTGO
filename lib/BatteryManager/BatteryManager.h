#ifndef BATTERYMANAGER_H
#define BATTERYMANAGER_H

#define SAMPLE_COUNT 10 
#define ADC_PIN 34 


#include <Arduino.h>
#include "esp_adc_cal.h"


class BatteryManager {
public:
    BatteryManager();
    void sampleVoltage();
    float getVoltage();
    float calculateAverageVoltage();
    float batteryPercentage(float voltage);
    void checkBatteryHealth();

private:
    float voltage_samples[SAMPLE_COUNT];
    int sample_index = 0;
    esp_adc_cal_characteristics_t *adc_chars;
};

#endif // BATTERYMANAGER_H
