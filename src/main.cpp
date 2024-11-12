#include <Arduino.h>
#include <Button2.h>
#include "Config.h"
#include "BatteryManager.h"
#include "PowerManager.h"
#include <UI.h>

UI GUI;
Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

BatteryManager batteryManager;
PowerManager powerManager;
int btnClick = false;

void button_init() {
    btn1.setLongClickHandler([](Button2 & b) {
        btnClick = false;
    });

    btn1.setPressedHandler([](Button2 & b) {
        btnClick = true;
    });

    btn2.setPressedHandler([](Button2 & b) {
        btnClick = false;
        powerManager.enterDeepSleep();
    });
}

void button_loop() {
    btn1.loop();
    btn2.loop();
}

void setup() {
    Serial.begin(115200);

    pinMode(ADC_EN, OUTPUT);
    digitalWrite(ADC_EN, HIGH);

    if (TFT_BL > 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
    }

    button_init();

    Serial.println("Setup completato. Inizio monitoraggio della batteria...");
}

void loop() {
   
    batteryManager.sampleVoltage();
    batteryManager.checkBatteryHealth();
    float voltage = batteryManager.getVoltage();
    GUI.ShowText(0, 25, String(voltage) + " " + String(batteryManager.batteryPercentage(voltage)) + " %");
    GUI.DrawBatteryIcon(200, 10, (int)batteryManager.batteryPercentage(voltage), 24, 10);
    delay(1000);


    button_loop();
}
