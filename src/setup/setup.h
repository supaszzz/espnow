#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "screen.h"
#include "config_page.h"
#include "bridge/bridge.h"
#include "main.h"

void runSetup();
void setupLoop();
void onPaired();

extern ESP8266WebServer server;
extern bool fastPair;