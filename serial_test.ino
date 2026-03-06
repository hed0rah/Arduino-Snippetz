#include <SoftwareSerial.h>

#define LED_PIN 13 // Built-in LED pin on Arduino Uno R4

SoftwareSerial BT05(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  BT05.begin(9600);
}

void loop() {
  if (BT05.available()) {
    int c = BT05.read();
    Serial.print("Received from Bluetooth Device (as integer): ");
    Serial.println(c); // Print the received character as an integer
    Serial.print("Received from Bluetooth Device (as char): ");
    Serial.println((char)c); // Print the received character as a character
    
    switch (c) {
      case '0': // ASCII for '0'
        Serial.println("Turning LED off");
        digitalWrite(LED_PIN, LOW);
        BT05.println("LED is now OFF"); // Send response
        break;
      case '1': // ASCII for '1'
        Serial.println("Turning LED on");
        digitalWrite(LED_PIN, HIGH);
        BT05.println("LED is now ON"); // Send response
        break;
      default:
        Serial.println("Received unknown command");
        BT05.println("Invalid command received"); // Send response
        break;
    }
  }
}
