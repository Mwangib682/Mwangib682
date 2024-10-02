// Define IR sensor pins
const int sensor1Pin = 2; // Lane 1 IR sensor
const int sensor2Pin = 3; // Lane 2 IR sensor

// Define traffic light pins for Lane 1
const int greenLight1 = 4;
const int yellowLight1 = 5;
const int redLight1 = 6;

// Define traffic light pins for Lane 2
const int greenLight2 = 7;
const int yellowLight2 = 8;
const int redLight2 = 9;

// Timing constants (in milliseconds) when IR senses
const int greenDuration = 10000; // Green light duration
const int yellowDuration = 0;  // Yellow light duration

//Timing without IR
const int ONgreenDuration = 10000; // Green light duration
const int ONyellowDuration = 2000;  // Yellow light duration

// Sensor thresholds
const int vehicleThreshold = 1; // Minimum number of vehicles to consider lane busy

void setup() {
  // Initialize sensor pins
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);

  // Initialize traffic light pins
  pinMode(greenLight1, OUTPUT);
  pinMode(yellowLight1, OUTPUT);
  pinMode(redLight1, OUTPUT);
  pinMode(greenLight2, OUTPUT);
  pinMode(yellowLight2, OUTPUT);
  pinMode(redLight2, OUTPUT);

  // Start with both lanes red
  setRedLights();
}

void loop() {
  bool lane1Busy = digitalRead(sensor1Pin) == LOW; // Assuming LOW means vehicle detected
  bool lane2Busy = digitalRead(sensor2Pin) == LOW; // Assuming LOW means vehicle detected

  if (lane1Busy && !lane2Busy) {
    // Lane 1 has vehicles, Lane 2 does not
    lane1GreenLight();
    delay(greenDuration);
    lane1YellowLight();
    delay(yellowDuration);
    setRedLights();
  } else if (!lane1Busy && lane2Busy) {
    // Lane 2 has vehicles, Lane 1 does not
    lane2GreenLight();
    delay(greenDuration);
    lane2YellowLight();
    delay(yellowDuration);
    setRedLights();
  } else {
    // Both lanes are either busy or clear
    // Cycle through lanes to ensure fairness
    lane1GreenLight();
    delay(ONgreenDuration);
    lane1YellowLight();
    delay(ONyellowDuration);
    setRedLights();
    
    lane2GreenLight();
    delay(ONgreenDuration);
    lane2YellowLight();
    delay(ONyellowDuration);
    setRedLights();
  }
}

void setRedLights() {
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, HIGH);

  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, HIGH);
}

void lane1GreenLight() {
  digitalWrite(greenLight1, HIGH);
  digitalWrite(yellowLight1, LOW);
  digitalWrite(redLight1, LOW);
}

void lane1YellowLight() {
  digitalWrite(greenLight1, LOW);
  digitalWrite(yellowLight1, HIGH);
  digitalWrite(redLight1, LOW);
}

void lane2GreenLight() {
  digitalWrite(greenLight2, HIGH);
  digitalWrite(yellowLight2, LOW);
  digitalWrite(redLight2, LOW);
}

void lane2YellowLight() {
  digitalWrite(greenLight2, LOW);
  digitalWrite(yellowLight2, HIGH);
  digitalWrite(redLight2, LOW);
}

