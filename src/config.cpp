
// ======== Includes ========

#include <Adafruit_NeoPixel.h>
#include <vector>
#include "config.h"
using namespace std;


// ======== GPIO Pin Definitions ========
const int Button_Pin = 0;  // Define the GPIO pin for the button
const int LED_Strand = 1; // Define GPIO pin for the LED strand

// ======== NeoPixel Definitions ========
Adafruit_NeoPixel StatusLight(1, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NeoPixel_Chain(8, 2, NEO_GRBW + NEO_KHZ800);

// ======== Constants ========

// A (very simple) map of the NeoPixels for adjacency
vector<int> graph[8] = {
  {1},
  {0, 2},
  {1, 3},
  {2, 4},
  {3, 5},
  {4, 6},
  {5, 7},
  {6, 0}
};

// ======== Button & Pattern Behavior Definitions ========
int patternIndex = 1;
bool buttonPressed = false;
unsigned long buttonPressTime = 0;
const int longPressDuration = 2000; // 2 seconds for long press
volatile bool buttonInterrupt = false;
volatile bool lampSleep = false;
volatile int buttonPressCount = 0;  // Counter for button presses
unsigned long pressStartTime = 0;
bool buttonHeld = false;
volatile unsigned long lastPressTime = 0;  // Track last button press time

// LED strand

const int LEDC_CHANNEL = 0;     // Use PWM channel 0
const int LEDC_TIMER_BIT = 8;   // 8-bit resolution (0-255)
const int LEDC_BASE_FREQ = 5000; // 5 kHz frequency
const int PWM_LED_PIN = 1;      // GPIO pin for the LED

// Color options

const int colorOptions[][3] = {
    {255, 0, 0},    // Red
    {0, 255, 0},    // Green
    {0, 0, 255},    // Blue
    {255, 255, 0},  // Yellow
    {0, 255, 255},  // Cyan
    {255, 0, 255},  // Magenta
    {255, 165, 0},  // Orange
    {75, 0, 130}    // Indigo
};

const int numColors = sizeof(colorOptions) / sizeof(colorOptions[0]);  // Now this works