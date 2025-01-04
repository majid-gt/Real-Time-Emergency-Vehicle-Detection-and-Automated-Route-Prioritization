const int redPin = 7;    // Pin for red LED
const int greenPin = 8; // Pin for green LED

void setup() {
    pinMode(redPin, OUTPUT);   // Set red pin as output
    pinMode(greenPin, OUTPUT); // Set green pin as output
    Serial.begin(9600);        // Start serial communication
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read(); // Read command from Python
        if (command == 'R') {
            digitalWrite(redPin, HIGH);   // Turn on red LED
            digitalWrite(greenPin, LOW);   // Turn off green LED
        } else if (command == 'G') {
            digitalWrite(greenPin, HIGH);  // Turn on green LED
            digitalWrite(redPin, LOW);      // Turn off red LED
        }
    }
}
