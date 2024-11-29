#include <Wire.h>
#include "rgb_lcd.h"

// Pin assignments
const int lightSensorPin = A0;  // Light sensor connected to A0
const int micPin = A1;          // Microphone connected to A1
#define LED 6                   // LED connected to pin D6
#define BUZZER 5                // Buzzer connected to pin D5

// Threshold values
const int lightThreshold = 60;  // Light threshold value
const int soundThreshold = 70;  // Sound threshold value 

// Grove LCD setup
rgb_lcd lcd;
const int colorR = 255;         // Red component for the backlight
const int colorG = 0;           // Green component for the backlight
const int colorB = 0;           // Blue component for the backlight

void setup() {
    // Initialize LED and buzzer pins
    pinMode(LED, OUTPUT);       
    pinMode(BUZZER, OUTPUT);    

    // Initialize Serial Monitor for debugging
    Serial.begin(9600);         

    // Initialize Grove LCD
    lcd.begin(16, 2);           // Initialize LCD with 16 columns and 2 rows
    lcd.setRGB(0, 255, 0);      // Set LCD backlight to green for normal state
    lcd.print("Monitoring..."); // Default message
}

void loop() {
    // Read light and sound sensor values
    int lightValue = analogRead(lightSensorPin); 
    int soundValue = analogRead(micPin);         

    // Debugging: Print sensor values to Serial Monitor
    Serial.print("Light Value: ");
    Serial.print(lightValue);
    Serial.print(" Sound Value: ");
    Serial.println(soundValue);

    // Check if both light and sound exceed their thresholds
    if (lightValue > lightThreshold && soundValue > soundThreshold) {
        digitalWrite(LED, HIGH);    // Turn on LED
        digitalWrite(BUZZER, HIGH); // Turn on Buzzer

        // Update LCD to show "Intruder!" in red
        lcd.setRGB(colorR, colorG, colorB); 
        lcd.clear();               // Clear previous text
        lcd.print("Intruder!");    // Display warning message
    } else {
        digitalWrite(LED, LOW);     // Turn off LED
        digitalWrite(BUZZER, LOW);  // Turn off Buzzer

        // Reset LCD to normal state
        lcd.setRGB(0, 255, 0);      // Green backlight for normal state
        lcd.clear();
        lcd.print("Monitoring..."); // Display default message
    }

    delay(100); // Small delay for stability
}
