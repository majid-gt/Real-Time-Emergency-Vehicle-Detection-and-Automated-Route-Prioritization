#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "mallii";
const char* password = "1234567890";

WebServer server(80);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 columns, 2 rows

const int greenLedPin = 2;  // GPIO pin connected to green LED
const int redLedPin = 4;    // GPIO pin connected to red LED

void setup() {
    Serial.begin(115200);
    
    // Initialize LCD
    lcd.begin(16,2);
    lcd.backlight();
    
    // Set up LED pins
    pinMode(greenLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);  // Turn on red LED initially

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

    // Handle LCD message
    server.on("/lcd/<message>", []() {
        String message = server.uri().substring(5);  // Extract message from URL
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(message);
        server.send(200, "text/plain", "Message displayed on LCD");
    });

    // Handle LED control (green and red)
    server.on("/led/green", []() {
        digitalWrite(greenLedPin, HIGH);  // Turn on green LED
        digitalWrite(redLedPin, LOW);     // Turn off red LED
        server.send(200, "text/plain", "Green LED ON, Red LED OFF");
    });

    server.on("/led/red", []() {
        digitalWrite(greenLedPin, LOW);  // Turn off green LED
        digitalWrite(redLedPin, HIGH);   // Turn on red LED
        server.send(200, "text/plain", "Red LED ON, Green LED OFF");
    });

    // Start the server
    server.begin();
}

void loop() {
    server.handleClient();
}
