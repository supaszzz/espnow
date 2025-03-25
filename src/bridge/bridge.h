#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "messages.h"
#include "screen.h"
#include "stats.h"

extern SoftwareSerial serial2;

void runBridge();
void bridgeLoop();