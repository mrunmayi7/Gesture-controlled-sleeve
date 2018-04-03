/*
 * == VIBRATION MOTOR TEST CODE ==
 * Push button to simulate "incoming call" to turn on motor
 * Bluetooth not yet integrated
 */

const int motorPin = 3; // ouput pin for vibration motor
const int pushPin = 2;  // input pin for push button
int pushVal = 0;  // variable for reading the pin status
int motorFlag = 0;
int i = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(pushPin, INPUT);
  
  Serial.begin(38400);
//  BTSerial.begin(38400); // uncomment for Bluetooth integration

  Serial.println("Start up component test for motor. Push button to activate motor");
}

void loop() {
  pushVal = digitalRead(pushPin); // read input value from push button

  // Checks request to activate motor and marks flag
  // if pushVal input is HIGH (button released)
  if (pushVal == HIGH) {
    motorFlag = 1;
    Serial.println("'Incoming Call' activated");
  }

  if (motorFlag == 1) {
    // Vibrate motor 5 times and interrupt to turn off/mute if button is pressed again
    i = 0;
    do {
      digitalWrite(motorPin, HIGH);
      delay(500);
      
      digitalWrite(motorPin, LOW);
      delay(100);
      i++;
    } while ((i < 5) && (pushVal != HIGH));

    // Turn off motor until next activation and set flag back to 0
    digitalWrite(motorPin, LOW);
    
    motorFlag = 0;
  }
  else if (motorFlag == 0) {
    digitalWrite(motorPin, LOW);
  }

}
