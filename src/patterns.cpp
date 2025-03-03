
// ======== Includes ========

#include "helpers.h"
#include "config.h"
#include <vector>
#include <queue>
#include <math.h>  // required for sin() function
#include <unordered_map>
using namespace std;

void DefaultPattern(){
  NeoPixel_Chain.clear();
  NeoPixel_Chain.show();

  // lightStrand(0);
}

// A basic light
void Pattern1() {

  for (int i = 0; i < 8; i++) {
    lightPixel(i, 255, 150, 50, 255);
  }

  // lightStrand(255);

  while (!buttonInterrupt){
    if (buttonInterrupt) {
          Serial.println("Button pressed! Exiting DefaultPattern...");
          buttonInterrupt = false;  // Reset flag
          return;
    }
  }
}

// ======== Pattern 2 ========
// All pixels shift smoothly from red to green to blue to red
void Pattern2() {
  // // Turn on strand light
  // lightStrand(255);
  
  Serial.println("Beginning Pattern2!");

  int red = 255, green = 0, blue = 0, white = 0; // Start with red
  int fadeSpeed = 1; // Speed of fade
  unsigned long previousMillis = millis();
  const unsigned long interval = 50; // Delay equivalent

  while (!buttonInterrupt) { // Stay in loop unless button is pressed again
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Reset timer

      // Color transition logic - properly loops from blue back to red
      if (red == 255 && green < 255 && blue == 0) {   // Red -> Yellow -> Green
        green += fadeSpeed;
      } else if (green == 255 && red > 0 && blue == 0) {   // Green -> Cyan
          red -= fadeSpeed;
      } else if (green == 255 && red == 0 && blue < 255) {   // Cyan -> Blue
          blue += fadeSpeed;
      } else if (blue == 255 && green > 0 && red == 0) {   // Blue -> Magenta
          green -= fadeSpeed;
      } else if (blue == 255 && green == 0 && red < 255) {   // Magenta -> Red
          red += fadeSpeed;
      } else if (red == 255 && blue > 0 && green == 0) {   // Back to Red
          blue -= fadeSpeed;
      }

      for (int i = 0; i < 8; i++){
        lightPixel(i, red, green, blue, white);
      }
      

      // Exit the pattern if button is pressed again
      if (buttonInterrupt) {
        Serial.println("Button pressed! Exiting Pattern2...");
        return;
      }
    }
  }
}

// Pattern 3: turning on a rainbow
void Pattern3() {
  const unsigned long interval = 500;  // Interval between pixel updates
  const int numPixels = 8;            // Total pixels
  unsigned long previousMillis = 0;   // Tracks last update time
  unsigned long offMillis = 0;        // Tracks when to turn off pixels
  //int buttonPresses = getButtonPresses();

  NeoPixel_Chain.clear();
  NeoPixel_Chain.show();

  int currentPixel = 0;               // Track which pixel is being lit
  bool turningOff = false;            // Track if we are in the turn-off phase

  while (!buttonInterrupt) {
    // int buttonPresses = getButtonPresses();

    unsigned long currentMillis = millis(); // Continuously update millis()

    // Light up pixels one by one
    if (!turningOff && (currentMillis - previousMillis >= interval)) {
      previousMillis = currentMillis; // Reset timer

      int hue = (currentPixel * 256 / numPixels);  // Spread hues across pixels
      uint32_t color = StatusLight.ColorHSV(hue * 256, 255, 150); // Convert to NeoPixel color
      lightPixel(currentPixel, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, 0);

      currentPixel++;  // Move to the next pixel

      // Once all pixels are lit, start turn-off sequence
      if (currentPixel >= numPixels) {
        turningOff = true;
        currentPixel = 0;
        offMillis = millis(); // Mark start of turn-off sequence
      }
    }

    // Turn pixels off in sequence
    if (turningOff && (currentMillis - offMillis >= interval)) {
      offMillis = currentMillis; // Reset timer

      lightPixel(currentPixel, 0, 0, 0, 0); // Turn off current pixel
      currentPixel++;

      // Once all pixels are turned off, restart the sequence
      if (currentPixel >= numPixels) {
        turningOff = false;
        currentPixel = 0;
      }
    }

    // Exit the pattern if button is pressed again
    if (buttonInterrupt) {
      Serial.println("Button pressed! Exiting Pattern3...");
      // buttonInterrupt = false;  // Reset flag
      return;
    }
  }
}

// Pattern 4: Independent breathing for Each Pixel
void Pattern4() {
    Serial.println("Starting Breathing Pattern");

    const int numPixels = 8;
    float brightness[numPixels];  // Brightness as a sine wave function
    unsigned long startTime[numPixels]; // When each pixel's cycle started
    int cycleDuration[numPixels]; // Duration of each sine wave cycle
    int colors[numPixels][3]; // Current RGB color
    int newColors[numPixels][3]; // Next color for transition
    bool waitingForMin[numPixels]; // Ensures color change happens only once per cycle

    for (int i = 0; i < numPixels; i++) {
        startTime[i] = millis();
        cycleDuration[i] = random(5000, 20000); // 2 to 10 sec per cycle
        waitingForMin[i] = true; // Start in a state where we wait for the min brightness

        pickRandomColor(colors[i][0], colors[i][1], colors[i][2]);   // Pick initial color
        pickRandomColor(newColors[i][0], newColors[i][1], newColors[i][2]); // Pick next color
    }

    while (!buttonInterrupt) {
        unsigned long currentMillis = millis();

        for (int i = 0; i < numPixels; i++) {
            float elapsedTime = (currentMillis - startTime[i]) % cycleDuration[i]; // Loop within cycle
            float phase = (elapsedTime / (float)cycleDuration[i]) * 2 * PI;  // Convert time to radians
            brightness[i] = (sin(phase - PI) + 1.0) / 2.0; // Reverse sine wave phase (min to max)

            int scaledBrightness = (brightness[i] * 255); // Scale from 25 to 255

            // Apply current color WITHOUT blending
            int red = (colors[i][0] * scaledBrightness) / 255;
            int green = (colors[i][1] * scaledBrightness) / 255;
            int blue = (colors[i][2] * scaledBrightness) / 255;

            lightPixel(i, red, green, blue, 0);

            if (brightness[i] < 0.01 && waitingForMin[i]) {
                waitingForMin[i] = false; // Prevent multiple changes in the same cycle

                // Switch to new color at the lowest brightness
                colors[i][0] = newColors[i][0];
                colors[i][1] = newColors[i][1];
                colors[i][2] = newColors[i][2];

                // Pick a new distinct color for the next cycle
                pickRandomColor(newColors[i][0], newColors[i][1], newColors[i][2]);
            }

            // Reset waiting flag when brightness is increasing again
            if (brightness[i] > 0.1) {
                waitingForMin[i] = true;
            }
        }

        // Show updates
        NeoPixel_Chain.show();

        delay(20); // Smooth updates
    }

    Serial.println("Exiting Breathing Pattern...");
}
