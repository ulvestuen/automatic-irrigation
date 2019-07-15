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
    int getCurrentHour();
    int getCurrentMinute();
    void printDigitalClock();

private:
    static void sendNTPpacket(IPAddress &address);
    void printDigits(int digits);
};

#endif
