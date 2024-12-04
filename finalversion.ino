#include <Wire.h>

// Pin assignments
const int lightSensorPin = A0;  // Light sensor connected to A0
const int micPin = A1;          // Microphone connected to A1
#define LED 6                   // LED connected to pin D6
#define BUZZER 5                // Buzzer connected to pin D5

// Threshold values
const int lightThreshold = 60;  // Light threshold value
const int soundThreshold = 70;  // Sound threshold value 

// Grove LCD I2C addresses
#define LCD_ADDRESS 0x3E        // Default I2C address for Grove LCD (text mode)
#define RGB_ADDRESS 0x62        // Default I2C address for Grove RGB backlight

void setup() {
    // Initialize pins
    pinMode(LED, OUTPUT);       
    pinMode(BUZZER, OUTPUT);    

    // Initialize serial communication for debugging
    Serial.begin(9600);

    // Initialize I2C and LCD
    Wire.begin();           
    initLCD();              // Initialize the LCD display
    setRGB(0, 255, 0);      // Set backlight color to green
    printText("Monitoring"); // Display "Monitoring" on the LCD
}

void loop() {
    // Read sensor values
    int lightValue = analogRead(lightSensorPin); 
    int soundValue = analogRead(micPin);         

    // Debugging: Print values to Serial Monitor
    Serial.print("Light Value: ");
    Serial.print(lightValue);
    Serial.print(" Sound Value: ");
    Serial.println(soundValue);

    // Check if both light and sound exceed thresholds
    if (lightValue > lightThreshold && soundValue > soundThreshold) {
        digitalWrite(LED, HIGH);    // Turn on LED
        digitalWrite(BUZZER, HIGH); // Turn on Buzzer

        // Update LCD to show "Intruder!" with red backlight
        setRGB(255, 0, 0); 
        printText("Intruder!");
    } else {
        digitalWrite(LED, LOW);     // Turn off LED
        digitalWrite(BUZZER, LOW);  // Turn off Buzzer

        // Reset LCD to normal state with green backlight
        setRGB(0, 255, 0);
        printText("Monitoring");
    }

    delay(100); // Small delay for stability
}

// Function to initialize the LCD
void initLCD() {
    Wire.beginTransmission(LCD_ADDRESS);
    Wire.write(0x80);   // Control byte
    Wire.write(0x38);   // Function set: 2-line display
    Wire.endTransmission();
    delay(50);

    Wire.beginTransmission(LCD_ADDRESS);
    Wire.write(0x80);   // Control byte
    Wire.write(0x0C);   // Display ON, Cursor OFF, Blink OFF
    Wire.endTransmission();
    delay(50);

    Wire.beginTransmission(LCD_ADDRESS);
    Wire.write(0x80);   // Control byte
    Wire.write(0x01);   // Clear display
    Wire.endTransmission();
    delay(50);
}

// Function to set the RGB backlight color
void setRGB(uint8_t red, uint8_t green, uint8_t blue) {
    Wire.beginTransmission(RGB_ADDRESS);
    Wire.write(0x00);   // Command register
    Wire.write(0x00);   // Mode 1 register
    Wire.endTransmission();

    Wire.beginTransmission(RGB_ADDRESS);
    Wire.write(0x01);   // Command register
    Wire.write(0x00);   // Mode 2 register
    Wire.endTransmission();

    Wire.beginTransmission(RGB_ADDRESS);
    Wire.write(0x08);   // Red PWM register
    Wire.write(red);    // Set red value
    Wire.endTransmission();

    Wire.beginTransmission(RGB_ADDRESS);
    Wire.write(0x09);   // Green PWM register
    Wire.write(green);  // Set green value
    Wire.endTransmission();

    Wire.beginTransmission(RGB_ADDRESS);
    Wire.write(0x0A);   // Blue PWM register
    Wire.write(blue);   // Set blue value
    Wire.endTransmission();
}

// Function to print text on the LCD
void printText(const char* text) {
    Wire.beginTransmission(LCD_ADDRESS);
    Wire.write(0x80);   // Control byte to set DDRAM address
    Wire.write(0x02);   // Move cursor to beginning
    Wire.endTransmission();

    delay(50);

    Wire.beginTransmission(LCD_ADDRESS);
    Wire.write(0x40);   // Control byte for data
    while (*text) {
        Wire.write(*text++);  // Write each character
    }
    Wire.endTransmission();
}
