#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 4); // RX, TX on ATtiny85
const int ledPin = 0;       // Pin 0 for the LED
const int buttonPin = 2;    // Pin 2 for the button input
const int signalPin = 1;    // Pin 1 for sending the signal when button is pressed
const long timeout = 60000; // 15 seconds timeout
int lastButtonState = LOW;
int trackNumber = 1;
unsigned long lastButtonPress = 0; // Timestamp of the last button press

void setup() {
  pinMode(ledPin, OUTPUT);       // Set the LED pin as an output
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor
  pinMode(signalPin, OUTPUT);    // Set the signal pin as an output
  digitalWrite(ledPin, HIGH);    // Turn on the LED immediately on power up
  mySerial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);  // Assuming you're using the internal pull-up
  delay(1000);  // Give DFPlayer some time to initialize
  setVolume(30);  // Set volume to maximum
  playTrack(trackNumber); // Play first track on startup
}

void loop() {
  // Check if the button is pressed
  int buttonState = digitalRead(buttonPin);
  if (digitalRead(buttonPin) == LOW) { // Button reads LOW when pressed due to pull-up resistor
    digitalWrite(signalPin, HIGH);     // Send signal if button is pressed
    lastButtonPress = millis();        // Update the last button press timestamp
  } else {
    digitalWrite(signalPin, LOW);  // Otherwise, turn off the signalPin
  }

  // Check if no button press for more than 15 seconds
  if (millis() - lastButtonPress > timeout) {
    digitalWrite(ledPin, LOW); // Turn off the LED
  }
  if (buttonState == LOW && lastButtonState == HIGH) { // Button is active low
    trackNumber++;
    if (trackNumber > 4) { // Replace 10 with the total number of your tracks
      trackNumber = 1;
    }
    playTrack(trackNumber);
    delay(1000); // This delay ensures one track per press and acts as a debounce time
  }
  lastButtonState = buttonState;
}

void playTrack(int track) {
  mySerial.write((uint8_t)0x7E);
  mySerial.write((uint8_t)0xFF);
  mySerial.write((uint8_t)0x06);
  mySerial.write((uint8_t)0x03);
  mySerial.write((uint8_t)0x00);
  mySerial.write((track & 0xFF00) >> 8);
  mySerial.write(track & 0x00FF);
  mySerial.write((uint8_t)0xEF);
}

void setVolume(int volume) {
  mySerial.write((uint8_t)0x7E);
  mySerial.write((uint8_t)0xFF);
  mySerial.write((uint8_t)0x06);
  mySerial.write((uint8_t)0x06);
  mySerial.write((uint8_t)0x00);
  mySerial.write((uint8_t)0x00);
  mySerial.write((uint8_t)volume);
  mySerial.write((uint8_t)0xEF);
}

