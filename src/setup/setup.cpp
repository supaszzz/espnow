#include "setup.h"

ESP8266WebServer server(80);

uint pairingTimeout = 11;

void runAP() {
    char ssid[22] = "esp_";

    digitalWrite(2, HIGH);
    displayMessage("Tryb konfiguracji\r\n\r\nUruchamianie AP...");
    esp_now_deinit();
    WiFi.mode(WIFI_AP);
    strcat(ssid, WiFi.macAddress().c_str());
    WiFi.softAP(ssid, "poleko123$");

    server.on("/", sendConfigPage);

    server.onNotFound([]() {
        server.send(404, "text/plain", "Nie odnaleziono podanego adresu");
    });

    server.begin();

    char printStr[128];
    snprintf(printStr, 128, "Tryb konfiguracji\r\n\r\nMAC:\r\n%s\r\n\r\nIP: %s", &ssid[4], WiFi.softAPIP().toString().c_str());

    Serial.println(printStr);
    displayMessage(printStr);
}

void runSetup() {
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    displayMessage("Tryb konfiguracji\r\n\r\nSzukanie urzadzen...");
    initESPNow(true);
}

void setupLoop() {
    if (pairingTimeout) {
        sendMessage(nullptr, 0);
        pairingTimeout--;
        if (pairingTimeout)
            delay(500);
        else
            runAP();
        return;
    }

    server.handleClient();
}