#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <cstring>

typedef struct {
    char signature[4];
    uint8_t version;
    uint8_t targetMAC[6];
    unsigned int baudRate;
} EspConfig;

extern EspConfig *espConfig;

void loadConfig();
void saveConfig();