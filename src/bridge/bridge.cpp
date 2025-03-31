#include "bridge.h"

SoftwareSerial serial2(13, 15);

void runBridge() {
    serial2.begin(espConfig->baudRate, static_cast<EspSoftwareSerial::Config>(espConfig->dataBits | espConfig->parity | espConfig->stopBits));
    if (!initESPNow(false)) {
        Serial.println("Nie udalo sie uruchomic ESP-NOW");
        displayMessage("Nie udalo sie uruchomic ESP-NOW");
        for (;;);
    }
    pinMode(5, OUTPUT);
    digitalWrite(5, LOW);
    Serial.println("Zakonczono uruchamianie");
}

void bridgeLoop() {
    if (statsUpdated) {
        statsUpdated = false;
        updateStatDisplay();
    }

    if (messagePending)
        return;

    uint bytesToRead = serial2.available();
    if (!bytesToRead) {
        auto time = millis();
        if (!lastTried || time - lastTried >= 4000)
            sendMessage(nullptr, 0);
        if (!lastSent || time - lastSent >= 5000)
            digitalWrite(2, HIGH);
        else
            digitalWrite(2, LOW);

        return;
    }
    if (bytesToRead > MSG_SIZE)
        bytesToRead = MSG_SIZE;
    char messageBuffer[MSG_SIZE];
    serial2.readBytes(messageBuffer, bytesToRead);
    // Serial.write(messageBuffer, bytesToRead);
    sendMessage((uint8_t*) messageBuffer, bytesToRead);
}