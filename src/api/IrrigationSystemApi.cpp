#include <api/IrrigationSystemApi.h>

IrrigationSystemApi::IrrigationSystemApi() {}
IrrigationSystemApi::IrrigationSystemApi(IrrigationSystemStatus *status,
                                         IrrigationSystemService *service)
{
  server = new ESP8266WebServer(80);
  systemStatus = status;
  systemService = service;
}

void IrrigationSystemApi::setup()
{
  server->on("/", [=]() -> void {
    server->send(200, "text/plain", "Automatic irrigation system");
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

  server->begin();
  Serial.println("HTTP server started");
}

void IrrigationSystemApi::handleClient()
{
  server->handleClient();
}
