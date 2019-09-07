#include <model/IrrigationSystemStatus.h>

IrrigationSystemStatus::IrrigationSystemStatus(std::vector<PumpController *> pControllerList,
                                               TimeService *tService)
{
    pumpControllerList = pControllerList;
    jsonStatus = new DynamicJsonDocument(1024);
}

String IrrigationSystemStatus::getPumpStatuses()
{
    jsonStatus->clear();

    for (std::size_t i = 0; i < pumpControllerList.size(); i++)
    {
        StaticJsonDocument<JSON_OBJECT_SIZE(3)> pumpStatusDoc;
        JsonObject pumpStatus = pumpStatusDoc.to<JsonObject>();
        pumpStatus["id"] = i;
        pumpStatus["active"] = (pumpControllerList[i])->getIsActive();
        pumpStatus["speed_setpoint"] = (pumpControllerList[i])->getPumpSpeedSetpoint();
        jsonStatus->add(pumpStatus);
    }

    String jsonString = "";
    serializeJson(*jsonStatus, jsonString);
    return jsonString;
}

String IrrigationSystemStatus::getPumpSpeeds()
{
    return "";
}

boolean IrrigationSystemStatus::isHealthy()
{
    return timeService->isHealthy();
}
