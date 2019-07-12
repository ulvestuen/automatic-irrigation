#include <Arduino.h>
#include <service/WifiConnectionService.h>
#include <api/IrrigationSystemApi.h>
#include <model/IrrigationSystemStatus.h>
#include <service/IrrigationSystemService.h>

const std::vector<uint8_t> PUMP_PIN_LIST = {D8, D6};

WifiConnectionService *wifiConnectionService;
std::vector<PumpController *> pumpControllerList;
IrrigationSystemStatus *systemStatus;
IrrigationSystemService *irrigationSystemService;
IrrigationSystemApi *irrigationSystemApi;

void setup(void)
{
  // Connect to WiFi with details given in "secrets.h"
  wifiConnectionService = new WifiConnectionService();
  wifiConnectionService->connect();

  // Setup Pump controllers, system status and services
  std::for_each(PUMP_PIN_LIST.begin(),
                PUMP_PIN_LIST.end(),
                [=](uint8_t pin) -> void {
                  pumpControllerList.push_back(new PumpController(pin));
                  Serial.println("Pump controller added for pin " + String(pin));
                });

  systemStatus = new IrrigationSystemStatus(pumpControllerList);
  irrigationSystemService = new IrrigationSystemService(systemStatus,
                                                        pumpControllerList);

  // Setup API
  irrigationSystemApi = new IrrigationSystemApi(systemStatus,
                                                irrigationSystemService);
  irrigationSystemApi->setup();
}

void loop(void)
{
  irrigationSystemApi->handleClient();
  irrigationSystemService->controlIrrigationSystem(systemStatus);
}
