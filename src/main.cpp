// ======== Library initialization ========

#include <Arduino.h>
#include "config.h"
#include "helpers.h"
#include <Adafruit_NeoPixel.h>
using namespace std;

// ======== Setup ========

void setup() {

  // // Initialize strand LED
  // ledcSetup(LEDC_CHANNEL, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  // ledcAttachPin(PWM_LED_PIN, LEDC_CHANNEL);

  // Setting the interrupt pin!!
  attachInterrupt(digitalPinToInterrupt(Button_Pin), buttonISR, CHANGE); // Detect both press and release

  // Initialize button
  pinMode(Button_Pin, INPUT);  // No need for PULLUP

  // Initializing the status light, will start with a green light
  StatusLight.begin();
  StatusLight.setPixelColor(0, StatusLight.Color(2, 2, 0)); // Dim yellow light for boot verification (GRB)
  StatusLight.show(); 

  NeoPixel_Chain.begin();
  NeoPixel_Chain.clear();
  NeoPixel_Chain.show();
  
  // Turn on serial monitor
  Serial.begin(115200);
  Serial.println("System initializing...");

  setPattern(); 
}

// ======== Loop ========
void loop() {

  if (lampSleep) {
    setPattern();
  }
  static int lastPressCount = 0;
  if (buttonInterrupt) {
    buttonInterrupt = false;  // Reset flag

    setPattern();
  }

}

