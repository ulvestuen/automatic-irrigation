#ifndef IrrigationSystemService_h
#define IrrigationSystemService_h

#include <model/IrrigationSystemStatus.h>
#include <model/PumpController.h>
#include <service/TimeService.h>

class IrrigationSystemService
{

private:
    IrrigationSystemStatus *systemStatus;
    std::vector<PumpController *> pumpControllerList;
    TimeService *timeService;

        public : IrrigationSystemService(TimeService *tService);
    IrrigationSystemService(IrrigationSystemStatus *status,
                            std::vector<PumpController *> pumpControllerList,
                            TimeService *tService);
    void controlIrrigationSystem(IrrigationSystemStatus *status);
    void activatePump(int pumpId);
    void deactivatePump(int pumpId);
    void setPumpSpeedSetpoint(int pumpId, int speed);
};

#endif
