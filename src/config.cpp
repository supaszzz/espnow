#include "config.h"

EspConfig *espConfig = nullptr;

EspConfig defaultConfig = {
    .signature = {'e', 's', 'p', 'N'},
    .version = 2,
    .targetMAC = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .baudRate = 9600,
    .parity = 000,
    .stopBits = 000,
    .dataBits = 003
};

void loadConfig() {
    EEPROM.begin(sizeof(EspConfig));
    espConfig = (EspConfig*) EEPROM.getDataPtr();

    if (strncmp(espConfig->signature, defaultConfig.signature, 5)) {
        Serial.println("Nie odnaleziono poprawnej konfiguracji - wczytywanie ustawien domyslnych");
        memcpy(espConfig, &defaultConfig, sizeof(EspConfig));
        saveConfig();
    }
}

void saveConfig() {
    EEPROM.commit();
    espConfig = (EspConfig*) EEPROM.getDataPtr();
}