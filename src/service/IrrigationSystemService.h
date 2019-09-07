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
    std::vector<int> ACTIVATION_HOURS = {0};
    std::vector<int> ACTIVATION_MINUTES = {0};
    int ACTIVE_PERIOD = 0;

    void printVector(std::vector<int> vect);

public:
    IrrigationSystemService(TimeService *tService);
    IrrigationSystemService(IrrigationSystemStatus *status,
                            std::vector<PumpController *> pControllerList,
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
    void setActivationHours(std::vector<int> activationHours);
    void setActivationMinutes(std::vector<int> activationMinutes);
    void setActivePeriod(int activePeriod);
};

#endif
