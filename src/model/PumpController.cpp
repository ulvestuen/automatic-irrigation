#include <model/PumpController.h>

PumpController::PumpController(TimeService *timeService) {}

PumpController::PumpController(uint8_t pin, TimeService *timeService)
{
    pumpOutputPin = pin;
    pinMode(pumpOutputPin, OUTPUT);
    digitalWrite(pumpOutputPin, LOW);
}

void PumpController::setIsActive(boolean active)
{
    isActive = active;
}

boolean PumpController::getIsActive()
{
    return isActive;
}

void PumpController::setPumpSpeedSetpoint(int speed)
{
    pumpDutyCycle = ((double)speed) / 100;
    pumpActivationTime = timeService->getTime();
    pumpNextActivationTime = pumpActivationTime + PUMP_MAX_ACTIVE_TIME;
}

int PumpController::getPumpSpeedSetpoint()
{
    return pumpDutyCycle * 100;
}

void PumpController::controlPumpSpeed()
{
    if (!isActive)
    {
        digitalWrite(pumpOutputPin, LOW);
        return;
    }

    time_t nowTime = timeService->getTime();
    if (nowTime < pumpActivationTime + pumpDutyCycle * PUMP_MAX_ACTIVE_TIME)
    {
        digitalWrite(pumpOutputPin, HIGH);
    }
    else if (nowTime < pumpNextActivationTime)
    {
        digitalWrite(pumpOutputPin, LOW);
    }
    else
    {
        pumpActivationTime = pumpNextActivationTime;
        pumpNextActivationTime += PUMP_MAX_ACTIVE_TIME;
        digitalWrite(pumpOutputPin, HIGH);
    }
}
