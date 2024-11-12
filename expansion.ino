#include <Wire.h>               // For I2C communication
#include <LiquidCrystal_I2C.h>   // For controlling the LCD

const int lightSensorPin = A0;  // Light sensor connected to A0
const int micPin = A1;          // Microphone connected to A1
#define LED 6                   // LED connected to pin D6
#define BUZZER 5                // Buzzer connected to pin D5

const int lightThreshold = 60;   // Light threshold value
const int soundThreshold = 100;  // Sound threshold value 

// Initialize the LCD (I2C address 0x27 is common for many I2C LCDs)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD 16x2, I2C address 0x27

void setup() {
    pinMode(LED, OUTPUT);       // Set LED pin as output
    pinMode(BUZZER, OUTPUT);    // Set buzzer pin as output
    Serial.begin(9600);         // Initialize serial communication for debugging

    // Initialize the LCD
    lcd.begin(16, 2);           // Initialize the LCD with 16 columns and 2 rows
    lcd.backlight();            // Turn on the backlight
    lcd.clear();                // Clear the display
}

void loop() {
    int lightValue = analogRead(lightSensorPin); // Read light sensor value
    int soundValue = analogRead(micPin);         // Read microphone value

    // Debugging: Print the values to the Serial Monitor
    Serial.print("Light Value: ");
    Serial.print(lightValue);
    Serial.print(" Sound Value: ");
    Serial.println(soundValue);

    // Check conditions for LED, buzzer, and LCD display activation
    if (lightValue > lightThreshold && soundValue > soundThreshold) {
        digitalWrite(LED, HIGH);    // Turn on LED
        digitalWrite(BUZZER, HIGH); // Turn on Buzzer
        lcd.clear();                // Clear the LCD
        lcd.setCursor(0, 0);        // Set cursor to the first line
        lcd.print("Intruder");      // Display "Intruder"
    } else {
        digitalWrite(LED, LOW);     // Turn off LED
        digitalWrite(BUZZER, LOW);  // Turn off Buzzer
        lcd.clear();                // Clear the LCD
        lcd.setCursor(0, 0);        // Set cursor to the first line
        lcd.print("System Ready");  // Display "System Ready"
    }

    delay(100); // Small delay for stability
}
