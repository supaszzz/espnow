#pragma once
#include <Arduino.h>
#include "config.h"
#include "setup.h"
#include "incbin.h"

#define RES_SIZE 4096
#define MACSTR_SIZE 1024

void sendConfigPage();
void addFoundMac(const char*);