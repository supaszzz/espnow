#include "discover.h"

uint8_t macArr[16][6];
uint8_t length = 0;

void foundMac(uint8_t *macAddr) {
    if (length == 16)
        return;

    for (int i = 0; i != length; i++)
        if (!memcmp(macAddr, macArr[i], 6))
            return;
    
    memcpy(macArr[length], macAddr, 6);
    length++;

    char macStr[18];
    snprintf(macStr, 18, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX",
        macAddr[0],
        macAddr[1],
        macAddr[2],
        macAddr[3],
        macAddr[4],
        macAddr[5]);
    addFoundMac(macStr);
}
