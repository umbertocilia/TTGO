#include <Arduino.h>
#include <UI.h>
#include "esp_adc_cal.h"

#define BLACK_SPOT

// Switch position and size
#define FRAME_X 0
#define FRAME_Y 0
#define FRAME_W 220
#define FRAME_H 110

// Red zone size
#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W/2)
#define REDBUTTON_H FRAME_H

// Green zone size
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W/2)
#define GREENBUTTON_H FRAME_H

#define ADC_PIN 34
int vref = 1100;

UI GUI;

#define SAMPLE_COUNT 10  // Numero di campioni per l'analisi della salute

// Dichiarazione delle caratteristiche ADC
esp_adc_cal_characteristics_t *adc_chars = new esp_adc_cal_characteristics_t;
const adc_atten_t atten = ADC_ATTEN_DB_11;     // Attenuazione per misurare fino a ~3.3V
const adc_unit_t unit = ADC_UNIT_1;

// Array per campionare la tensione
float voltage_samples[SAMPLE_COUNT];
int sample_index = 0;


float
batteryPercentage(float voltage) {
    const float maxVoltage = 4.2;
    const float minVoltage = 3.0;

    if (voltage >= maxVoltage) {
        return 100.0;  
    } else if (voltage <= minVoltage) {
        return 0.0;   
    }

    float percentage = (voltage - minVoltage) / (maxVoltage - minVoltage) * 100.0;
    return percentage;
}

float 
getVoltage()
{
    uint16_t v = analogRead(ADC_PIN);
    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (adc_chars->vref / 1000.0);
    return battery_voltage;
}

void 
sampleVoltage()
{
    uint16_t v = analogRead(ADC_PIN);
    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (adc_chars->vref / 1000.0);
    voltage_samples[sample_index] = battery_voltage;
    sample_index = (sample_index + 1) % SAMPLE_COUNT;  // Aggiorna l'indice in modo circolare
}

float 
calculateAverageVoltage()
{
    float total = 0;
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        total += voltage_samples[i];
    }
    return total / SAMPLE_COUNT;
}

void checkBatteryHealth()
{
    float avg_voltage = calculateAverageVoltage();
    float current_voltage = voltage_samples[(sample_index - 1 + SAMPLE_COUNT) % SAMPLE_COUNT];

    Serial.print("Media della tensione: ");
    Serial.print(avg_voltage);
    Serial.print(" V, Tensione attuale: ");
    Serial.print(current_voltage);
    Serial.println(" V");

    // Controllo della salute della batteria
    if (current_voltage < avg_voltage * 0.9) {  // Condizione per rilevare calo rapido del 10%
        Serial.println("Avviso: calo rapido della tensione, possibile batteria scarica o in cattivo stato!");
        GUI.ShowText(0,0,"Bad Battery");
    }
    else
    {
        GUI.ShowText(0,0,"               ");
    }

}

void setup()
{
    Serial.begin(115200);

    // Calibrazione del riferimento ADC
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, 1100, adc_chars);
    
    // Controllo del tipo di calibrazione
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        Serial.printf("eFuse Vref:%u mV\n", adc_chars->vref);
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\n", adc_chars->coeff_a, adc_chars->coeff_b);
    } else {
        Serial.println("Default Vref: 1100mV");
        adc_chars->vref = 1100;  // Imposta il valore di default
    }

    Serial.println("Setup completato. Inizio monitoraggio della batteria...");
}

void loop()
{
    sampleVoltage();  
    checkBatteryHealth();
    GUI.ShowText(0,25,String(getVoltage()) + "  " + String(batteryPercentage(getVoltage())) + " %");
    GUI.DrawBatteryIcon(140, 10, (int)batteryPercentage(getVoltage()), 24, 10); 

    delay(1000);  
}



