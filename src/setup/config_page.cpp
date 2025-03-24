#include "config_page.h"

INCTXT(indexHtml, "src/setup/index.html");

char macString[MACSTR_SIZE] = {0};

void addFoundMac(const char* macAddr) {
    size_t length = strlen(macString);
    snprintf(macString + length, MACSTR_SIZE - length, "<option>%s</option>", macAddr);
}

void sendConfigPage() {
    char response[RES_SIZE];
    char errMessage[32] = {0};

    if (server.hasArg("save") && server.arg("save") == "1") {
        try {
            EspConfig newConfig = *espConfig;

            int scanRes = sscanf(server.arg("mac").c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                &newConfig.targetMAC[0],
                &newConfig.targetMAC[1],
                &newConfig.targetMAC[2],
                &newConfig.targetMAC[3],
                &newConfig.targetMAC[4],
                &newConfig.targetMAC[5]);
            if (scanRes != 6)
                throw 1;

            scanRes = sscanf(server.arg("baud").c_str(), "%u", &newConfig.baudRate);
            if (scanRes != 1)
                throw 2;

            memcpy(espConfig, &newConfig, sizeof(EspConfig));
            strcpy(errMessage, "Zapisano");
            saveConfig();
        } catch (int err) {
            strcpy(errMessage, "Niepoprawne dane");
        }
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
        errMessage);
    server.send(200, "text/html", response);
}