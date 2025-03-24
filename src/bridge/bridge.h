#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <HardwareSerial.h>
#include "messages.h"
#include "screen.h"
#include "stats.h"

extern HardwareSerial serial2;

void runBridge();
void bridgeLoop();