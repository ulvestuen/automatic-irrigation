#ifndef PumpController_h
#define PumpController_h

#include <Arduino.h>

class PumpController
{

private:
    boolean isActive = false;
    int pumpSpeedSetpoint;
    uint8_t pumpOutputPin;
    double pumpDutyCycle = 0.0;
    const double PUMP_MAX_ACTIVE_TIME = 10000.0;
    long pumpActivationTime = 0;
    long pumpNextActivationTime = pumpActivationTime + PUMP_MAX_ACTIVE_TIME;

public:
    PumpController();
    PumpController(uint8_t pin);
    void setIsActive(boolean active);
    boolean getIsActive();
    void setPumpSpeedSetpoint(int speed);
    int getPumpSpeedSetpoint();
    void controlPumpSpeed();
};

#endif
