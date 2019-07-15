#include <service/IrrigationSystemService.h>

IrrigationSystemService::IrrigationSystemService(TimeService *tService) {}

IrrigationSystemService::IrrigationSystemService(IrrigationSystemStatus *status,
                                                 std::vector<PumpController *> pCList,
                                                 TimeService *tService)
{
    systemStatus = status;
    pumpControllerList = pCList;
    timeService = tService;
}

void IrrigationSystemService::activatePump(int pumpId)
{
    (pumpControllerList[pumpId])->setIsActive(true);
}

void IrrigationSystemService::deactivatePump(int pumpId)
{
    (pumpControllerList[pumpId])->setIsActive(false);
}

void IrrigationSystemService::setPumpSpeedSetpoint(int pumpId, int speed)
{
    (pumpControllerList[pumpId])->setPumpSpeedSetpoint(speed);
}

void IrrigationSystemService::controlIrrigationSystem(IrrigationSystemStatus *status)
{
    std::for_each(pumpControllerList.begin(),
                  pumpControllerList.end(),
                  [](PumpController *pC) -> void {
                      pC->controlPumpSpeed();
                  });
}
