#ifndef IrrigationSystemStatus_h
#define IrrigationSystemStatus_h

#include <Arduino.h>
#include <model/PumpController.h>

class IrrigationSystemStatus
{

private:
    std::vector<PumpController *> pumpControllerList;

public:
    IrrigationSystemStatus(std::vector<PumpController *> pumpControllerList);
    String getPumpActiveStatuses();
    String getPumpSpeeds();
};

#endif
