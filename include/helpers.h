// ======== Library initialization ========
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// ======== Function prototypes ========

// Defined in helpers.cpp
void handleButtonPress();
void cyclePatterns();
void setPattern();
void cyclePatterns();
void enterDeepSleep();
void IRAM_ATTR buttonISR();
int getButtonPresses();
void watchdogCheck();
void lightPixel(int position, int Red, int Green, int Blue, int White);
void lightStrand(int PWM);
void pickRandomColor(int &r, int &g, int &b);

// Defined in patterns.cpp
void TestPattern(int presses);
void DefaultPattern();
void Pattern1();
void Pattern2();
void Pattern3();
void Pattern4();
