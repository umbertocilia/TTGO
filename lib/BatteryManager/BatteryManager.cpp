#include "BatteryManager.h"

BatteryManager::BatteryManager() {
    adc_chars = new esp_adc_cal_characteristics_t;
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, adc_chars);

    if (val_type != ESP_ADC_CAL_VAL_EFUSE_VREF) {
        adc_chars->vref = 1100;
    }
}

void BatteryManager::sampleVoltage() {
    uint16_t v = analogRead(ADC_PIN);
    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (adc_chars->vref / 1000.0);
    voltage_samples[sample_index] = battery_voltage;
    sample_index = (sample_index + 1) % SAMPLE_COUNT;
}

float BatteryManager::getVoltage() {
    uint16_t v = analogRead(ADC_PIN);
    return ((float)v / 4095.0) * 2.0 * 3.3 * (adc_chars->vref / 1000.0);
}

float BatteryManager::calculateAverageVoltage() {
    float total = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        total += voltage_samples[i];
    }
    return total / SAMPLE_COUNT;
}

float BatteryManager::batteryPercentage(float voltage) {
    const float maxVoltage = 4.2;
    const float minVoltage = 3.0;
    return voltage >= maxVoltage ? 100.0 : (voltage <= minVoltage ? 0.0 : (voltage - minVoltage) / (maxVoltage - minVoltage) * 100.0);
}

void BatteryManager::checkBatteryHealth() {
    float avg_voltage = calculateAverageVoltage();
    float current_voltage = voltage_samples[(sample_index - 1 + SAMPLE_COUNT) % SAMPLE_COUNT];

    if (current_voltage < avg_voltage * 0.9) {
        Serial.println("Warning: Rapid voltage drop detected!");
    }
}
