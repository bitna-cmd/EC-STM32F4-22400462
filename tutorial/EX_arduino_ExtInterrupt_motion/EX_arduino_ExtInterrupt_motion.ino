// set pin numbers
const int motionPin = 5;    // the number of the Motion detection sensor
const int btnPin = 3;       // the number of the push button pin
const int ledPin = 13;      // the number of the LED pin

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  
  // initialize the Motion detection sensor pin as an interrupt input:
  pinMode(motionPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(motionPin), motionDetected, RISING);

  // initialize the push button pin as an interrupt input:
  pinMode(btnPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(btnPin), btnPressed, FALLING);
}

void loop() {

}

void motionDetected(){
  // LED on
  digitalWrite(ledPin, HIGH);
}

void btnPressed(){
  // LED off
  digitalWrite(ledPin, LOW);
}