// Run Stepper Motor with A4998  

int x; 
#define BAUD (9600)
const int dirPin = 2;
const int stepPin = 3;
const int enablePin = 6;


void setup() 
{
  Serial.begin(BAUD);
  pinMode(enablePin,OUTPUT); // Enable
  pinMode(stepPin,OUTPUT); // Step
  pinMode(dirPin,OUTPUT); // Dir
  digitalWrite(enablePin,LOW); // Set Enable low
}

void loop() 
{
  digitalWrite(dirPin, HIGH);// Set Dir high (CW)
  Serial.println("Loop 200*5 steps (1*5 rev)");
  for(x = 0; x < 1000; x++) // Loop 200 times
  {
    digitalWrite(stepPin,HIGH); // Output high
    delay(10); // Wait
    digitalWrite(stepPin,LOW); // Output low
    delay(10); // Wait
  }
  Serial.println("Pause");
  delay(1000); // pause one second
}

