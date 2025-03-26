#include "config_page.h"

INCTXT(indexHtml, "src/setup/index.html");

char macString[MACSTR_SIZE] = {0};

const char* errors[] = {
    "Zapisano",
    "Niepoprawny adres MAC",
    "Niepoprawny baud rate",
    "Niepoprawna konfiguracja UART"
};

void addFoundMac(const char* macAddr) {
    size_t length = strlen(macString);
    snprintf(macString + length, MACSTR_SIZE - length, "<option>%s</option>", macAddr);
}

int updateConfig() {
    EspConfig newConfig = *espConfig;

    int scanRes = sscanf(server.arg("mac").c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        &newConfig.targetMAC[0],
        &newConfig.targetMAC[1],
        &newConfig.targetMAC[2],
        &newConfig.targetMAC[3],
        &newConfig.targetMAC[4],
        &newConfig.targetMAC[5]);
    if (scanRes != 6)
        return 1;

    scanRes = sscanf(server.arg("baud").c_str(), "%u", &newConfig.baudRate);
    if (scanRes != 1)
        return 2;

    scanRes = sscanf(server.arg("parity").c_str(), "%ho", &newConfig.parity);
    if (scanRes != 1)
        return 3;

    scanRes = sscanf(server.arg("stop").c_str(), "%ho", &newConfig.stopBits);
    if (scanRes != 1)
        return 3;
    
    scanRes = sscanf(server.arg("data").c_str(), "%ho", &newConfig.dataBits);
    if (scanRes != 1)
        return 3;

    memcpy(espConfig, &newConfig, sizeof(EspConfig));
    saveConfig();
    return 0;
}

void sendConfigPage() {
    char response[RES_SIZE];
    char message[32] = {0};
    char messageClass[8] = {0};

    if (server.hasArg("save") && server.arg("save") == "1") {
        int configErr = updateConfig();
        if (configErr) {
            strcpy(messageClass, "error");
        }
        strcpy(message, errors[configErr]);
    }

    snprintf(response, RES_SIZE, (char*)gindexHtmlData,
        macString,
        espConfig->targetMAC[0],
        espConfig->targetMAC[1],
        espConfig->targetMAC[2],
        espConfig->targetMAC[3],
        espConfig->targetMAC[4],
        espConfig->targetMAC[5],
        espConfig->baudRate,
        espConfig->parity,
        espConfig->stopBits,
        espConfig->dataBits,
        messageClass,
        message);
    server.send(200, "text/html", response);
}