// ============================================================
// ESP32 pin assignments
// ============================================================

// Edited 2026-08-13 originally for the Boyertown Historical Vehicle Museum


// ============================================================
// Button inputs
//
// Buttons are externally pulled LOW.
// Pressing a button brings the corresponding pin HIGH.
// ============================================================

const int button1Pin = 32; // Brown to bread board
const int button2Pin = 33; // Red to bread board
const int button3Pin = 34; // Orange to bread board
const int button4Pin = 35; // Yellow to bread board


// ============================================================
// Outputs to audio board
//
// Audio board inputs are normally HIGH.
// Pulling an audio pin LOW triggers that audio channel.
// ============================================================

const int audioPin1 = 18; // Yellow to audio board
const int audioPin2 = 19; // Green to audio board
const int audioPin3 = 21; // Blue to audio board
const int audioPin4 = 22; // Purple to audio board


// ============================================================
// Signal output
// ============================================================

const int signalPin = 23; // Grey to bread board


// ============================================================
// Timing
// ============================================================

// On initial boot, hold ALL audio pins HIGH for a brief amount of time
const unsigned long startupHighTime = 600;

// Length of startup LOW trigger pulse
const unsigned long startupPulseLength = 100;

// Inactivity timeout
// 120000 ms = 2 minutes
const unsigned long inactivityTime = 120000;


// ============================================================
// Variables
// ============================================================

unsigned long startupTime = 0;
unsigned long lastButtonPressTime = 0;

bool startupFinished = false;


// Remember which button was pressed during startup.
//
// 0 = none
// 1 = button 1
// 2 = button 2
// 3 = button 3
// 4 = button 4
int startupButton = 0;


// ============================================================
// Helper function
//
// Set ALL audio outputs HIGH.
// ============================================================

void allAudioHigh() {

  digitalWrite(audioPin1, HIGH);
  digitalWrite(audioPin2, HIGH);
  digitalWrite(audioPin3, HIGH);
  digitalWrite(audioPin4, HIGH);
}


// ============================================================
// Helper function
//
// Send one 100 ms LOW pulse to the selected audio channel.
// ============================================================

void sendStartupPulse(int buttonNumber) {

  // Make absolutely sure every audio pin starts HIGH
  allAudioHigh();


  if (buttonNumber == 1) {

    digitalWrite(audioPin1, LOW);

  } else if (buttonNumber == 2) {

    digitalWrite(audioPin2, LOW);

  } else if (buttonNumber == 3) {

    digitalWrite(audioPin3, LOW);

  } else if (buttonNumber == 4) {

    digitalWrite(audioPin4, LOW);
  }


  // Hold selected trigger LOW for 100 ms
  delay(startupPulseLength);


  // Return ALL audio lines HIGH
  allAudioHigh();
}


// ============================================================
// Setup
// ============================================================

void setup() {

  // ==========================================================
  // AUDIO OUTPUTS
  //
  // Configure these immediately and force all of them HIGH.
  // ==========================================================

  pinMode(audioPin1, OUTPUT);
  pinMode(audioPin2, OUTPUT);
  pinMode(audioPin3, OUTPUT);
  pinMode(audioPin4, OUTPUT);

  allAudioHigh();


  // ==========================================================
  // BUTTON INPUTS
  // ==========================================================

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);


  // ==========================================================
  // Immediately check whether a button is already being held
  // when setup() begins.
  // ==========================================================

  if (digitalRead(button1Pin) == HIGH) {

    startupButton = 1;

  } else if (digitalRead(button2Pin) == HIGH) {

    startupButton = 2;

  } else if (digitalRead(button3Pin) == HIGH) {

    startupButton = 3;

  } else if (digitalRead(button4Pin) == HIGH) {

    startupButton = 4;
  }


  // ==========================================================
  // SIGNAL OUTPUT
  // ==========================================================

  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, HIGH);


  // ==========================================================
  // SERIAL
  // ==========================================================

  Serial.begin(115200);


  // ==========================================================
  // TIMERS
  // ==========================================================

  startupTime = millis();
  lastButtonPressTime = startupTime;
}


// ============================================================
// Main loop
// ============================================================

void loop() {

  // ==========================================================
  // Read all buttons
  // ==========================================================

  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  int button4State = digitalRead(button4Pin);


  // ==========================================================
  // INITIAL STARTUP
  //
  // During the first 2000 ms:
  //
  // 1. ALL audio pins stay HIGH.
  // 2. Any brief button press is remembered.
  // 3. After 2000 ms, the remembered button gets ONE
  //    100 ms LOW pulse.
  // 4. ALL audio pins return HIGH.
  // ==========================================================

  if (!startupFinished) {

    // Keep every audio output HIGH throughout startup
    allAudioHigh();


    // --------------------------------------------------------
    // If no button has been remembered yet, keep checking.
    // --------------------------------------------------------

    if (startupButton == 0) {

      if (button1State == HIGH) {

        startupButton = 1;
        lastButtonPressTime = millis();

      } else if (button2State == HIGH) {

        startupButton = 2;
        lastButtonPressTime = millis();

      } else if (button3State == HIGH) {

        startupButton = 3;
        lastButtonPressTime = millis();

      } else if (button4State == HIGH) {

        startupButton = 4;
        lastButtonPressTime = millis();
      }
    }


    // --------------------------------------------------------
    // Stay in startup mode until 2000 ms has passed.
    // --------------------------------------------------------

    if (millis() - startupTime < startupHighTime) {

      return;
    }


    // --------------------------------------------------------
    // 2000 ms has passed.
    //
    // If a startup button was detected, send ONE 100 ms pulse.
    // --------------------------------------------------------

    if (startupButton != 0) {

      Serial.print("Startup button detected: ");
      Serial.println(startupButton);

      sendStartupPulse(startupButton);

      lastButtonPressTime = millis();
    }


    // --------------------------------------------------------
    // Startup sequence is now permanently complete.
    // --------------------------------------------------------

    startupFinished = true;

    allAudioHigh();

    return;
  }


  // ==========================================================
  // NORMAL OPERATION
  //
  // A button press pulls its audio line LOW.
  // Releasing the button returns the line HIGH.
  // ==========================================================


  // ----------------------------------------------------------
  // Button 1
  // ----------------------------------------------------------

  if (button1State == HIGH) {

    digitalWrite(audioPin1, LOW);
    lastButtonPressTime = millis();

  } else {

    digitalWrite(audioPin1, HIGH);
  }


  // ----------------------------------------------------------
  // Button 2
  // ----------------------------------------------------------

  if (button2State == HIGH) {

    digitalWrite(audioPin2, LOW);
    lastButtonPressTime = millis();

  } else {

    digitalWrite(audioPin2, HIGH);
  }


  // ----------------------------------------------------------
  // Button 3
  // ----------------------------------------------------------

  if (button3State == HIGH) {

    digitalWrite(audioPin3, LOW);
    lastButtonPressTime = millis();

  } else {

    digitalWrite(audioPin3, HIGH);
  }


  // ----------------------------------------------------------
  // Button 4
  // ----------------------------------------------------------

  if (button4State == HIGH) {

    digitalWrite(audioPin4, LOW);
    lastButtonPressTime = millis();

  } else {

    digitalWrite(audioPin4, HIGH);
  }


  // ==========================================================
  // INACTIVITY SIGNAL
  // ==========================================================

  if (millis() - lastButtonPressTime > inactivityTime) {

    digitalWrite(signalPin, LOW);

  } else {

    digitalWrite(signalPin, HIGH);
  }
}
