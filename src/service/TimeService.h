#ifndef TimeService_h
#define TimeService_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>

class TimeService
{

public:
    TimeService();
    static time_t getNtpTime();
    time_t getTime();

private:
    static void sendNTPpacket(IPAddress &address);
    void digitalClockDisplay();
    void printDigits(int digits);
};

#endif
