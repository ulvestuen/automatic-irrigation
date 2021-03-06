#ifndef IrrigationSystemStatus_h
#define IrrigationSystemStatus_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <model/PumpController.h>
#include <service/TimeService.h>

class IrrigationSystemStatus
{

private:
    DynamicJsonDocument *jsonStatus;
    std::vector<PumpController *> pumpControllerList;
    TimeService *timeService;

public:
    IrrigationSystemStatus(std::vector<PumpController *> pControllerList, TimeService *tService);
    String getPumpStatuses();
    String getPumpSpeeds();
    boolean isHealthy();
};

#endif
