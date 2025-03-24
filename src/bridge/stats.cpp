#include "stats.h"

double formatFileSize(unsigned long bytes, char* sizeUnit) {
    double result = bytes;
    uint unitIndex = 0;
    while (result >= 1024) {
      result /= 1024;
      unitIndex++;
    }
    switch (unitIndex) {
      case 1:
        strcpy(sizeUnit, "KB");
        break;
      case 2:
        strcpy(sizeUnit, "MB");
        break;
      case 3:
        strcpy(sizeUnit, "GB");
        break;
      case 4:
        strcpy(sizeUnit, "TB");
        break;
    }
    return result;
  }
  

void updateStatDisplay() {
    if (!displayConnected)
        return;

    char screenBuffer[128] = {0};
    char sentUnit[3] = "B\0";
    char lostUnit[3] = "B\0";
    char recvUnit[3] = "B\0";
  
    double packetRate = (double)lostPackets / sentPackets * 100;
    if (isnan(packetRate))
        packetRate = 0;
  
    snprintf(screenBuffer, 128,
        "Utracone pakiety:\r\n%.2f%%\r\nWyslane dane:\r\n%.2f %s\r\nUtracone dane:\r\n%.2f %s\r\nOdebrane dane:\r\n%.2f %s",
        packetRate,
        formatFileSize(sentBytes, sentUnit),
        sentUnit,
        formatFileSize(lostBytes, lostUnit),
        lostUnit,
        formatFileSize(recvBytes, recvUnit),
        recvUnit
    );

    displayMessage(screenBuffer);
}