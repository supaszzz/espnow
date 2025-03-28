#include "main.h"

bool setupMode = false;

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("Uruchamianie...");
    loadConfig();
    if (initDisplay()) {
        Serial.println("Polaczono wyswietlacz");
    }

    pinMode(2, OUTPUT);
    pinMode(4, INPUT_PULLUP);
    if (digitalRead(4) == LOW || !memcmp(espConfig->targetMAC, (const char[]){0,0,0,0,0,0}, 6))
        setupMode = true;

    // espConfig->signature[0] = 2;
    // saveConfig();

    if (setupMode) {
        runSetup();
        return;
    }

    runBridge();

}

void loop() {
    if (setupMode) {
        setupLoop();
        return;
    }
    bridgeLoop();
}

