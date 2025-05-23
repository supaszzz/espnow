#include "setup.h"

ESP8266WebServer server(80);
bool fastPair = false;
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

    server.on("/reset", []() {
        server.send(200, "text/html", "Ponowne uruchamianie urzadzenia i reset do ustawien domyslnych");
        delay(100);
        espConfig->signature[0] = 0;
        saveConfig();
        ESP.restart();
    });

    server.on("/restart", []() {
        server.send(200, "text/html", "Ponowne uruchamianie urzadzenia");
        delay(100);
        ESP.restart();
    });

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
    digitalWrite(2, LOW);
    for (int i = 0; i != 20; i++) {
        delay(100);
        if (digitalRead(4) == HIGH) {
            fastPair = true;
            break;
        }
    }
    displayMessage("Tryb konfiguracji\r\n\r\nSzukanie urzadzen...");
    initESPNow(true);
}

void setupLoop() {
    if (fastPair || pairingTimeout) {
        sendMessage(nullptr, 0);
        if (--pairingTimeout) {
            delay(500);
        } else if (!fastPair) {
            runAP();
        }
        return;
    }

    server.handleClient();
}