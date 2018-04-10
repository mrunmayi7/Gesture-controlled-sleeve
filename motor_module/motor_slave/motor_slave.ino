/*
   == VIBRATION MOTOR SLAVE CODE ==
   Receive data from master on whether or not there is an incoming call
   Using standard delay() method at the moment
   MOST BASIC CODE POSSIBLE
*/

// --------- LIBRARIES ---------
#include <SoftwareSerial.h>


// --------- CONSTANTS ---------
// Assign pin numbers
const int motorPin = 3; // output pin for vibration motor
const int buttonPin = 2;  // input pin for push button

const int callMaxDuration = 5000;  // maximum ring length before call redirects

SoftwareSerial BTSerial(10, 11); // RX | TX pins (that should receive TX | RX respectively)


// --------- VARIABLES ---------
int callVal = LOW;
int motorVal = 0;
int motorOn = 51 * 2.0;
int motorState = 0;
int motorCount;
int motorFlag;

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;


//========================================

void setup() {

//  // For AT config mode, connect EN (Key) to Pin 9
//  pinMode(9, OUTPUT);
//  digitalWrite(9, HIGH);

  Serial.begin(38400);
  BTSerial.begin(38400);  // HC-05 default speed in AT command mode

  Serial.println("Start up HC-05 slave module. Push button to activate motor.");

}

void loop() {
  
  currentMillis = millis(); 
  
  BTStateListener();  // listens for data from master Bluetooh device
  updateMotorStates();
  switchMotor();

}

//========================================

void BTStateListener() {

  // Constantly checks for data from BT master device
  if (BTSerial.available() > 0) {
    callVal = BTSerial.read();
    Serial.println(callVal);
  }
}

//========================================


void updateMotorStates() {
  if (callVal == LOW) {
    motorState = 0;
    
    if (motorFlag == 1) {
      motorFlag = 0;
      Serial.println("End of call");
    }
  }
  else if (callVal == HIGH) {
    motorState = 1;
    
    if (motorFlag == 0) {
      motorFlag = 1;
      motorCount = 0;
      Serial.println("\n\n'Incoming Call' detected");
    }
  }
}

void switchMotor() {

  if (motorState == 1) {
    // Vibrate motor 5 times and interrupt to turn off/mute if button is pressed again

//    Serial.println("Turn motor on");
    analogWrite(motorPin, motorOn);
    delay(500);

    analogWrite(motorPin, 0);
    delay(100);

  }
  else if (motorFlag == 0) {
    analogWrite(motorPin, 0);
  } 
}

