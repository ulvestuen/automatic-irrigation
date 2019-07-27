#include <api/IrrigationSystemApi.h>

IrrigationSystemApi::IrrigationSystemApi() {}
IrrigationSystemApi::IrrigationSystemApi(IrrigationSystemStatus *status,
                                         IrrigationSystemService *service)
{
  server = new ESP8266WebServer(80);
  httpUpdater = new ESP8266HTTPUpdateServer();
  systemStatus = status;
  systemService = service;
}

void IrrigationSystemApi::setup()
{
  server->on("/", [=]() -> void {
    server->send(200, "text/plain", "Automatic irrigation system");
  });

  server->on("/health", [=]() -> void {
    if (systemStatus->isHealthy())
    {
      server->send(200, "text/plain", "OK");
    }
    else
    {
      server->send(500, "text/plain", "Not OK");
    }
  });

  // Pump
  server->on("/pump/activate", HTTP_POST, [=]() -> void {
    Serial.println("Activating pump control...");
    systemService->activatePump(server->hasArg("pump_id") ? server->arg("pump_id").toInt() : -1);
    server->send(200, "text/plain", "Pump with ID activated: " + String(server->arg("pump_id")));
  });

  server->on("/pump/deactivate", HTTP_POST, [=]() -> void {
    Serial.println("Deactivating pump control...");
    systemService->deactivatePump(server->hasArg("pump_id") ? server->arg("pump_id").toInt() : -1);
    server->send(200, "text/plain", "Pump with ID deactivated: " + String(server->arg("pump_id")));
  });

  server->on("/pump/active", HTTP_GET, [=]() -> void {
    Serial.println("Getting pump activation status...");
    Serial.println("Pump active statuses are: " + String(systemStatus->getPumpActiveStatuses()));
    server->send(200, "text/plain", "Pump active statuses: " + String(systemStatus->getPumpActiveStatuses()));
  });

  server->on("/pump/speed", HTTP_POST, [=]() -> void {
    Serial.println("Setting pump speed...");
    systemService->setPumpSpeedSetpoint(server->hasArg("pump_id") ? server->arg("pump_id").toInt() : -1,
                                        server->hasArg("speed") ? server->arg("speed").toInt() : 0);
    Serial.println("Pump speed set to: " + String(server->arg("speed")));
    server->send(200, "text/plain", "Pump speed: " + String(server->arg("speed")));
  });

  server->on("/pump/speed", HTTP_GET, [=]() -> void {
    Serial.println("Getting pump speeds...");
    Serial.println("Pump speeds are: " + String(systemStatus->getPumpSpeeds()));
    server->send(200, "text/plain", "Pump speeds: " + String(systemStatus->getPumpSpeeds()));
  });

  server->on("/controlmode/manual", HTTP_POST, [=]() -> void {
    Serial.println("Setting manual control mode...");
    systemService->setControlMode(ControlMode::MANUAL);
    Serial.println("Control mode set to MANUAL");
    server->send(200, "text/plain", "Control mode set to MANUAL");
  });

  server->on("/controlmode/automatic", HTTP_POST, [=]() -> void {
    Serial.println("Setting automatic control mode...");

    if (server->hasArg("activation_hours"))
    {
      systemService->setActivationHours(toVector(server->arg("activation_hours"), ","));
    }
    if (server->hasArg("activation_minutes"))
    {
      systemService->setActivationMinutes(toVector(server->arg("activation_minutes"), ","));
    }
    if (server->hasArg("active_period"))
    {
      systemService->setActivePeriod(server->arg("active_period").toInt());
    }

    systemService->setControlMode(ControlMode::AUTOMATIC);
    Serial.println("Control mode set to AUTOMATIC");
    server->send(200, "text/plain", "Control mode set to AUTOMATIC");
  });

  // Enable OTA update of firmware.
  httpUpdater->setup(server);

  server->begin();
  Serial.println("HTTP server started");
}

void IrrigationSystemApi::handleClient()
{
  server->handleClient();
}

std::vector<int> IrrigationSystemApi::toVector(String stringWithDelimiter, std::string delimiter)
{
  std::vector<int> list;
  std::string sList = std::string(stringWithDelimiter.c_str());

  size_t pos = 0;
  std::string token;
  while ((pos = sList.find(delimiter)) != std::string::npos)
  {
    token = sList.substr(0, pos);
    list.push_back(atoi(token.c_str()));
    sList.erase(0, pos + delimiter.length());
  }
  list.push_back(atoi(sList.c_str()));
  return list;
}