#ifndef IrrigationSystemService_h
#define IrrigationSystemService_h

#include <model/IrrigationSystemStatus.h>
#include <model/PumpController.h>

class IrrigationSystemService
{

private:
    IrrigationSystemStatus *systemStatus;
    std::vector<PumpController *> pumpControllerList;

public:
    IrrigationSystemService();
    IrrigationSystemService(IrrigationSystemStatus *status,
                            std::vector<PumpController *> pumpControllerList);
    void controlIrrigationSystem(IrrigationSystemStatus *status);
    void activatePump(int pumpId);
    void deactivatePump(int pumpId);
    void setPumpSpeedSetpoint(int pumpId, int speed);
};

#endif
