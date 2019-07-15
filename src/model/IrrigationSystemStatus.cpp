#include <model/IrrigationSystemStatus.h>

IrrigationSystemStatus::IrrigationSystemStatus(std::vector<PumpController *> pumpControllerList,
                                               TimeService *timeService)
{
}

String IrrigationSystemStatus::getPumpActiveStatuses()
{
    return "";
}

String IrrigationSystemStatus::getPumpSpeeds()
{
    return "";
}
