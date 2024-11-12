#include "PowerManager.h"
#include "Config.h"
#include <UI.h>

extern UI GUI;

void PowerManager::enterDeepSleep() {
    GUI.TurnOffScreen();
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_35, 0);
    digitalWrite(TFT_BL, LOW);
    delay(200);
    esp_deep_sleep_start();
}

void PowerManager::espDelay(int ms) {
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);
    esp_light_sleep_start();
}
