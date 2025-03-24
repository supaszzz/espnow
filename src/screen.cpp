#include "screen.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, RESET_PIN);
bool displayConnected = false;

bool detectScreen() {
    Wire.beginTransmission(SCREEN_ADDRESS);
    return Wire.endTransmission() == 0;
}

bool initDisplay() {
    Wire.begin(14, 12);
    if(detectScreen() && display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        display.clearDisplay();
        display.display();
        display.setTextSize(1);
        display.setTextColor(1);
        displayConnected = true;
    }
    return displayConnected;
}

void displayMessage(const char* str) {
    if (displayConnected) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(str);
        display.display();
    }
}