#pragma once
#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "screen.h"
#include "main.h"
#include "setup/discover.h"
#include "bridge.h"

#define WIFI_CHANNEL 1
#define SIGNATURE "espN"
#define SIG_LENGTH 4
#define MSG_SIZE 192


extern bool statsUpdated;

extern unsigned long lostPackets;
extern unsigned long sentPackets;

extern unsigned long lostBytes;
extern unsigned long sentBytes;
extern unsigned long recvBytes;

extern unsigned long lastSent;
extern unsigned long lastTried;

extern bool messagePending;

void sendMessage(uint8_t* msg, size_t len);
bool initESPNow(bool broadcast);