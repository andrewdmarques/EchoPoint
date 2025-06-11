// Pin definitions
const int audioPin1 = 4;
const int audioPin2 = 5;
const int audioPin3 = 18;
const int audioPin4 = 19;
const int signalPin = 21;

const int buttonPin1 = 13;
const int buttonPin2 = 14;
const int buttonPin3 = 27;
const int buttonPin4 = 26;

unsigned long lastInteractionTime = 0;
const unsigned long timeoutDuration = 60000; // 60s timeout

void setup() {
  // Immediately configure input pins
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);

  // Detect early button press before anything else
  int initialPressed = 0;
  if (digitalRead(buttonPin1) == HIGH) initialPressed = 1;
  else if (digitalRead(buttonPin2) == HIGH) initialPressed = 2;
  else if (digitalRead(buttonPin3) == HIGH) initialPressed = 3;
  else if (digitalRead(buttonPin4) == HIGH) initialPressed = 4;

  // Setup output pins
  pinMode(audioPin1, OUTPUT);
  pinMode(audioPin2, OUTPUT);
  pinMode(audioPin3, OUTPUT);
  pinMode(audioPin4, OUTPUT);
  pinMode(signalPin, OUTPUT);

  // All pins high initially
  digitalWrite(audioPin1, HIGH);
  digitalWrite(audioPin2, HIGH);
  digitalWrite(audioPin3, HIGH);
  digitalWrite(audioPin4, HIGH);
  digitalWrite(signalPin, HIGH);  // Critical signal pin HIGH

  delay(250);  // Small hardware stabilization time

  // If a button was detected early, trigger corresponding audio
  if (initialPressed == 1) pulsePin(audioPin1);
  else if (initialPressed == 2) pulsePin(audioPin2);
  else if (initialPressed == 3) pulsePin(audioPin3);
  else if (initialPressed == 4) pulsePin(audioPin4);

  // Start timer for signal pin timeout
  lastInteractionTime = millis();
}

void loop() {
  bool buttonPressed = false;

  if (digitalRead(buttonPin1) == HIGH) {
    pulsePin(audioPin1);
    buttonPressed = true;
  }
  if (digitalRead(buttonPin2) == HIGH) {
    pulsePin(audioPin2);
    buttonPressed = true;
  }
  if (digitalRead(buttonPin3) == HIGH) {
    pulsePin(audioPin3);
    buttonPressed = true;
  }
  if (digitalRead(buttonPin4) == HIGH) {
    pulsePin(audioPin4);
    buttonPressed = true;
  }

  if (buttonPressed) {
    lastInteractionTime = millis();
    digitalWrite(signalPin, HIGH); // keep alive
    delay(200); // debounce delay
  }

  if (millis() - lastInteractionTime > timeoutDuration) {
    digitalWrite(signalPin, LOW); // power off after 60s inactivity
  }
}

// Helper: pulse output pin LOW for 200ms
void pulsePin(int pin) {
  digitalWrite(pin, LOW);
  delay(200);
  digitalWrite(pin, HIGH);
}

