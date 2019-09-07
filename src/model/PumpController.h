#ifndef PumpController_h
#define PumpController_h

#include <Arduino.h>
#include <TimeLib.h>
#include <service/TimeService.h>

class PumpController
{

private:
    boolean isActive = false;
    uint8_t pumpOutputPin;
    double pumpDutyCycle = 0.0;
    const double PUMP_MAX_ACTIVE_TIME = 10.0;
    time_t pumpActivationTime;
    time_t pumpNextActivationTime;
    TimeService *timeService;

public:
    PumpController(TimeService *timeService);
    PumpController(uint8_t pin, TimeService *tService);
    void setIsActive(boolean active);
    boolean getIsActive();
    void setPumpSpeedSetpoint(int speed);
    int getPumpSpeedSetpoint();
    void controlPumpSpeed();
};

#endif
