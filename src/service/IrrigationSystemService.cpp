#include <service/IrrigationSystemService.h>

IrrigationSystemService::IrrigationSystemService(TimeService *tService) {}

IrrigationSystemService::IrrigationSystemService(IrrigationSystemStatus *status,
                                                 std::vector<PumpController *> pControllerList,
                                                 TimeService *tService)
{
    systemStatus = status;
    pumpControllerList = pControllerList;
    timeService = tService;

    controlMode = ControlMode::MANUAL;
    irrigationInProgress = false;
    lastIrrigationActivationTime = 0;
}

void IrrigationSystemService::controlIrrigationSystem(IrrigationSystemStatus *status)
{
    switch (getControlMode())
    {
    case ControlMode::AUTOMATIC:
        if (itIsTimeToStopIrrigation())
        {
            timeService->printDigitalClock();
            Serial.println("Pumps deactivated.");
            deactivateAllPumps();
            lastIrrigationActivationTime = timeService->getTime() - ACTIVE_PERIOD;
        }
        else if (itIsTimeToStartIrrigation())
        {
            timeService->printDigitalClock();
            Serial.println("Pumps activated. It is time for irrigation.");
            activateAllPumps();
            lastIrrigationActivationTime = timeService->getTime();
        }
        break;

    default:
        break;
    }

    // Control pump speeds according to speed set points and active status.
    controlSpeedOfAllPumps();
}

void IrrigationSystemService::setControlMode(ControlMode cMode)
{
    controlMode = cMode;
}

ControlMode IrrigationSystemService::getControlMode()
{
    return controlMode;
}

void IrrigationSystemService::activatePump(int pumpId)
{
    (pumpControllerList[pumpId])->setIsActive(true);
    irrigationInProgress = true;
}

void IrrigationSystemService::activateAllPumps()
{
    for_each(pumpControllerList.begin(),
             pumpControllerList.end(),
             [](PumpController *pC) -> void {
                 pC->setIsActive(true);
             });
    irrigationInProgress = true;
}

void IrrigationSystemService::deactivatePump(int pumpId)
{
    (pumpControllerList[pumpId])->setIsActive(false);
    irrigationInProgress = any_of(pumpControllerList.begin(),
                                  pumpControllerList.end(),
                                  [](PumpController *pC) -> boolean {
                                      return pC->getIsActive();
                                  });
}

void IrrigationSystemService::deactivateAllPumps()
{
    for_each(pumpControllerList.begin(),
             pumpControllerList.end(),
             [](PumpController *pC) -> void {
                 pC->setIsActive(false);
             });
    irrigationInProgress = false;
}

void IrrigationSystemService::setPumpSpeedSetpoint(int pumpId, int speed)
{
    (pumpControllerList[pumpId])->setPumpSpeedSetpoint(speed);
}

void IrrigationSystemService::controlSpeedOfAllPumps()
{
    for_each(pumpControllerList.begin(),
             pumpControllerList.end(),
             [](PumpController *pC) -> void {
                 pC->controlPumpSpeed();
             });
}

boolean IrrigationSystemService::itIsTimeToStartIrrigation()
{
    int currentHour = timeService->getCurrentHour();
    int currentMinute = timeService->getCurrentMinute();

    boolean isAtActivationTime = any_of(ACTIVATION_HOURS.begin(), ACTIVATION_HOURS.end(), [=](int aH) -> boolean {
                                     return aH == currentHour;
                                 }) &&
                                 any_of(ACTIVATION_MINUTES.begin(), ACTIVATION_MINUTES.end(), [=](int aM) -> boolean {
                                     return aM == currentMinute;
                                 });

    boolean equalsLastActivationTime = currentHour == hour(lastIrrigationActivationTime) &&
                                       currentMinute == minute(lastIrrigationActivationTime);

    return isAtActivationTime && !equalsLastActivationTime;
}

boolean IrrigationSystemService::itIsTimeToStopIrrigation()
{
    return irrigationInProgress &&
           timeService->getTime() == lastIrrigationActivationTime + ACTIVE_PERIOD;
}

void IrrigationSystemService::setActivationHours(std::vector<int> activationHours)
{
    ACTIVATION_HOURS = activationHours;
    Serial.print("Activation hours set to: ");
    printVector(ACTIVATION_HOURS);
}
void IrrigationSystemService::setActivationMinutes(std::vector<int> activationMinutes)
{
    ACTIVATION_MINUTES = activationMinutes;
    Serial.print("Activation minutes set to: ");
    printVector(ACTIVATION_MINUTES);
}
void IrrigationSystemService::setActivePeriod(int activePeriod)
{
    ACTIVE_PERIOD = activePeriod;
    Serial.println("Active period set to: " + String(ACTIVE_PERIOD) + " seconds");
}

void IrrigationSystemService::printVector(std::vector<int> vect)
{
    Serial.print("{ ");
    for_each(vect.begin(),
             vect.end(),
             [](int i) -> void {
                 Serial.print(String(i) + " ");
             });
    Serial.println("}");
}