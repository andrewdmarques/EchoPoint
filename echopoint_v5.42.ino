// Define button pin constants
const int button1Pin = 4;
const int button2Pin = 5;
const int button3Pin = 13;
const int button4Pin = 12; 

// Define the output pins for audio
const int audioPin1 = 14;
const int audioPin2 = 0; //trying to fix this, testing 3,1,and now 0, 0 works
const int audioPin3 = 16;
const int audioPin4 = 10;


// Define the pin for signal
const int signalPin = 15;

// Variable to keep track of the last time a button was pressed
unsigned long lastButtonPressTime = 0;

// Variable to check if it's the first time the loop is running
bool firstRun = true;

void setup() {
  // Initialize the signal pin as an output and set to HIGH
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, HIGH);
  
  // Initialize button pins as inputs
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  
  // Initialize audio pins as outputs
  pinMode(audioPin1, OUTPUT);
  pinMode(audioPin2, OUTPUT);
  pinMode(audioPin3, OUTPUT);
  pinMode(audioPin4, OUTPUT);
  
  // Start serial communication at 9600 baud rate
  Serial.begin(9600);

  // Initialize the last button press time to the current time
  lastButtonPressTime = millis();
}

void loop() {
  // Read the state of each button pin
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  int button4State = digitalRead(button4Pin);

  // If it's the first run of the loop, pause to allow sound board to boot up.
  if (firstRun) {
//    delay(10);
//    int button1State = digitalRead(button1Pin);
//    int button2State = digitalRead(button2Pin);
//    int button3State = digitalRead(button3Pin);
//    int button4State = digitalRead(button4Pin);

    digitalWrite(audioPin1, HIGH);
    digitalWrite(audioPin2, HIGH);
    digitalWrite(audioPin3, HIGH);
    digitalWrite(audioPin4, HIGH);

    delay(500); // Delay on the first run only
    Serial.println("first loop");
    Serial.println(button1State);
    Serial.println(button2State);
    Serial.println(button3State);
    Serial.println(button4State);
    firstRun = false; // Set the first run to false so the delay doesn't happen again
    // Handle the state of audioPin1 based on button1Pin
    if (button1State == HIGH) {
      digitalWrite(audioPin1, LOW);
      Serial.println("Audio pin 1 set to LOW because button 1 is HIGH.");
      delay(100); // Allow the nodeMCU to send the low signal.
      digitalWrite(audioPin1, HIGH);
    } else if (button2State == HIGH) {
      digitalWrite(audioPin2, LOW);
      Serial.println("Audio pin 2 set to LOW because button 2 is HIGH.");
      delay(100); // Allow the nodeMCU to send the low signal.
      digitalWrite(audioPin2, HIGH);
    } else if (button3State == HIGH) {
      digitalWrite(audioPin3, LOW);
      Serial.println("Audio pin 3 set to LOW because button 3 is HIGH.");
      delay(100); // Allow the nodeMCU to send the low signal.
      digitalWrite(audioPin3, HIGH);
    } else if (button4State == HIGH) {
      digitalWrite(audioPin4, LOW);
      Serial.println("Audio pin 4 set to LOW because button 4 is HIGH.");
      delay(100); // Allow the nodeMCU to send the low signal.
      digitalWrite(audioPin4, HIGH);
    }
  } else {
    // Handle the state of audioPin1 based on button1Pin
    if (button1State == HIGH) {
      digitalWrite(audioPin1, LOW);
      Serial.println("Audio pin 1 set to LOW because button 1 is HIGH.");
      lastButtonPressTime = millis();
    } else {
      digitalWrite(audioPin1, HIGH);
  //    Serial.println("Audio pin 1 set to HIGH because button 1 is LOW.");
    }
  
    // Handle the state of audioPin2 based on button2Pin
    if (button2State == HIGH) {
      digitalWrite(audioPin2, LOW);
      Serial.println("Audio pin 2 set to LOW because button 2 is HIGH.");
      lastButtonPressTime = millis();
    } else {
      digitalWrite(audioPin2, HIGH);
//      Serial.println("Audio pin 2 set to HIGH because button 2 is LOW.");
    }
  
    // Handle the state of audioPin3 based on button3Pin
    if (button3State == HIGH) {
      digitalWrite(audioPin3, LOW);
      Serial.println("Audio pin 3 set to LOW because button 3 is HIGH.");
      lastButtonPressTime = millis();
    } else {
      digitalWrite(audioPin3, HIGH);
  //    Serial.println("Audio pin 3 set to HIGH because button 3 is LOW.");
    }
  
    // Handle the state of audioPin4 based on button4Pin
    if (button4State == HIGH) {
      digitalWrite(audioPin4, LOW);
      Serial.println("Audio pin 4 set to LOW because button 4 is HIGH.");
      lastButtonPressTime = millis();
    } else {
      digitalWrite(audioPin4, HIGH);
  //    Serial.println("Audio pin 4 set to HIGH because button 4 is LOW.");
      
    }
  
    // Check if 60 seconds have passed since the last button press
    if (millis() - lastButtonPressTime > 60000) {
      digitalWrite(signalPin, LOW); // Set signal pin LOW after 60 seconds of inactivity
    } else {
      digitalWrite(signalPin, HIGH); // Otherwise keep it HIGH
    }
  }
  

  // Small delay to prevent flooding the serial output
  delay(50);
}

