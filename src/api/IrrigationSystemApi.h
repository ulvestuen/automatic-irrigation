#ifndef IrrigationSystemApi_h
#define IrrigationSystemApi_h

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <model/IrrigationSystemStatus.h>
#include <service/IrrigationSystemService.h>

class IrrigationSystemApi
{

private:
  ESP8266WebServer *server;
  IrrigationSystemStatus *systemStatus;
  IrrigationSystemService *systemService;
  std::vector<int> toVector(String stringWithDelimiter, std::string delimiter);

public:
  IrrigationSystemApi();
  IrrigationSystemApi(IrrigationSystemStatus *status, IrrigationSystemService *service);
  void setup();
  void handleClient();
};

#endif
