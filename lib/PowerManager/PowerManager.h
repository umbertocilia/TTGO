#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <Arduino.h>

class PowerManager {
public:
    void enterDeepSleep();
    void espDelay(int ms);
};

#endif // POWERMANAGER_H
