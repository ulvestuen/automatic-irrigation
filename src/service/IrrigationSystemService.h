#ifndef IrrigationSystemService_h
#define IrrigationSystemService_h

#include <model/IrrigationSystemStatus.h>
#include <model/PumpController.h>
#include <model/ControlMode.h>
#include <service/TimeService.h>

class IrrigationSystemService
{

private:
    IrrigationSystemStatus *systemStatus;
    std::vector<PumpController *> pumpControllerList;
    TimeService *timeService;

    ControlMode controlMode;
    boolean irrigationInProgress;
    time_t lastIrrigationActivationTime;

    // Relevant for ControlMode::AUTOMATIC
    const std::vector<int> ACTIVATION_HOURS = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
    const std::vector<int> ACTIVATION_MINUTES = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55};
    const int ACTIVE_PERIOD = 30;

public:
    IrrigationSystemService(TimeService *tService);
    IrrigationSystemService(IrrigationSystemStatus *status,
                            std::vector<PumpController *> pumpControllerList,
                            TimeService *tService);

    void controlIrrigationSystem(IrrigationSystemStatus *status);
    void setControlMode(ControlMode cMode);
    ControlMode getControlMode();

    void activatePump(int pumpId);
    void activateAllPumps();
    void deactivatePump(int pumpId);
    void deactivateAllPumps();
    void setPumpSpeedSetpoint(int pumpId, int speed);
    void controlSpeedOfAllPumps();

    // Relevant for ControlMode::AUTOMATIC
    boolean itIsTimeToStartIrrigation();
    boolean itIsTimeToStopIrrigation();
};

#endif
