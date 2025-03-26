#include "messages.h"

uint8_t broadcastAddr[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
bool isBroadcasting = false;

bool statsUpdated = true;

bool messagePending = false;
int messageSize = 0;

unsigned long lostPackets = 0;
unsigned long sentPackets = 0;

unsigned long lostBytes = 0;
unsigned long sentBytes = 0;
unsigned long recvBytes = 0;

void onSent(uint8_t* macAddr, uint8_t sendStatus) {
    sentPackets++;
    if (sendStatus) {
        lostPackets++;
        lostBytes += messageSize;
    } else {
        sentBytes += messageSize;
    }
    messagePending = false;
    statsUpdated = true;
}

void onData(uint8_t* macAddr, uint8_t* data, uint8_t len) {
    if ((!isBroadcasting && memcmp(espConfig->targetMAC, macAddr, 6)) || memcmp(data, SIGNATURE, SIG_LENGTH))
        return;
    
    if (setupMode) {
        if (fastPair) {
            memcpy(espConfig->targetMAC, macAddr, 6);
            onPaired();
        } else {
            foundMac(macAddr);
        }
        return;
    }

    len -= SIG_LENGTH;

    digitalWrite(5, HIGH);
    delay(1);
    serial2.write(data + SIG_LENGTH, len);
    // Serial.write(data + SIG_LENGTH, len);
    digitalWrite(5, LOW);

    recvBytes += len;
    statsUpdated = true;
}

void sendMessage(uint8_t* msg, size_t len) {
    uint8_t packet[MSG_SIZE + SIG_LENGTH] = SIGNATURE;
    memcpy(packet + SIG_LENGTH, msg, len);
    esp_now_send(isBroadcasting? broadcastAddr : espConfig->targetMAC, packet, len + SIG_LENGTH);
    messagePending = true;
    messageSize = len;
}

bool initESPNow(bool broadcast) {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    Serial.print("Adres MAC: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init()) {
        return false;
    }
    isBroadcasting = broadcast;

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(broadcast? broadcastAddr : espConfig->targetMAC, ESP_NOW_ROLE_COMBO, WIFI_CHANNEL, NULL, 0);
    esp_now_register_recv_cb(onData);
    esp_now_register_send_cb(onSent);

    return true;
}
  