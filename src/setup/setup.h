#pragma once
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "screen.h"
#include "config_page.h"

void runSetup();
void setupLoop();

extern ESP8266WebServer server;