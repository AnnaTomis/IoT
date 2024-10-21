const int lightSensorPin = A0;  // Light sensor connected to A0
const int micPin = A1;           // Microphone connected to A1
#define LED 6            // LED connected to pin D6
#define BUZZER 5        // Buzzer connected to pin D5

const int lightThreshold = 60;   // Light threshold value
const int soundThreshold = 70;   // Sound threshold value 

void setup() {
    pinMode(LED, OUTPUT);       // Set LED pin as output
    pinMode(BUZZER, OUTPUT);    // Set buzzer pin as output
    Serial.begin(9600);         // Initialize serial communication for debugging
}

void loop() {
    int lightValue = analogRead(lightSensorPin); // Read light sensor value
    int soundValue = analogRead(micPin);         // Read microphone value

    // Debugging: Print the values to the Serial Monitor
    Serial.print("Light Value: ");
    Serial.print(lightValue);
    Serial.print(" Sound Value: ");
    Serial.println(soundValue);

    // Check conditions for LED and buzzer activation
    if (lightValue > lightThreshold && soundValue > soundThreshold) {
        digitalWrite(LED, HIGH);    // Turn on LED
        digitalWrite(BUZZER, HIGH); // Turn on Buzzer
    } else {
        digitalWrite(LED, LOW);     // Turn off LED
        digitalWrite(BUZZER, LOW);  // Turn off Buzzer
    }

    delay(100); // Small delay for stability
}