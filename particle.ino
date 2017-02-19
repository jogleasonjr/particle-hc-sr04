#define TRIG_PIN D6
#define ECHO_PIN D4

// store variable for Particle.publish here
double lastReadingInches = -1;
double lastReadingCm = -1;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

void setup() {

  Particle.variable("inches", lastReadingInches);
  Particle.variable("centimeters", lastReadingCm);

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial.begin(9600);
}

void loop() {

  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin
  // TODO: set a timeout so we don't lose connection to the particle cloud server
  while ( digitalRead(ECHO_PIN) == 0 );

  // Measure how long the echo pin was held high (pulse width)
  // Note: the micros() counter will overflow after ~70 min
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  // Calculate distance in centimeters and inches. The constants
  // are found in the datasheet, and calculated from the assumed speed 
  // of sound in air at sea level (~340 m/s).
  lastReadingCm = pulse_width / 58.0;
  lastReadingInches = pulse_width / 148.0;

  // Print out results
  if ( pulse_width > MAX_DIST ) {
    Serial.println("Out of range");
  } else {
    Serial.print(lastReadingCm);
    Serial.print(" cm \t");
    Serial.print(lastReadingInches);
    Serial.println(" in");
  }
  
  // Wait at least 60ms before next measurement
  delay(60);
}