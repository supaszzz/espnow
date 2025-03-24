#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "bridge/messages.h"

#define SCREEN_ADDRESS 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define RESET_PIN -1

bool initDisplay();
void displayMessage(const char*);

extern Adafruit_SSD1306 display;
extern bool displayConnected;