#ifndef CONFIG_H
#define CONFIG_H

#include <Adafruit_NeoPixel.h>


// ======== NeoPixel Declarations ========
extern Adafruit_NeoPixel StatusLight;
extern Adafruit_NeoPixel NeoPixel_Chain;

// ======== Button, GPIO, and Pattern Declarations ========
extern int patternIndex;
extern bool buttonPressed;
extern unsigned long buttonPressTime;
extern const int Button_Pin;  // GPIO pin for the button
extern const int longPressDuration; // Long press duration in milliseconds
extern const int LED_Strand; // GPIO pin for the strand LED
extern const int POT; // GPIO pin for the potentiometer

extern volatile unsigned long lastDebounceTime; // Stores last button press time
extern const unsigned long debounceDelay;  // Minimum delay in ms to avoid multiple counts
extern const int longPressDuration; // 2 seconds for long press

extern volatile bool buttonInterrupt;
extern volatile bool lampSleep;
extern volatile int buttonPressCount;  // Counter for button presses
extern unsigned long pressStartTime;
extern volatile unsigned long lastPressTime;
extern bool buttonHeld;

// LED Strand config
extern const int LEDC_CHANNEL;     // Use PWM channel 0
extern const int LEDC_TIMER_BIT;   // 8-bit resolution (0-255)
extern const int LEDC_BASE_FREQ; // 5 kHz frequency
extern const int PWM_LED_PIN;      // GPIO pin for the LED

// Color options
extern const int colorOptions[][3];  // Explicitly declare as a 2D array
extern const int numColors;          // Declare numColors for access in other files

#endif // CONFIG_H
