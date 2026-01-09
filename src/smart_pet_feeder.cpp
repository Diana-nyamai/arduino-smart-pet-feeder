#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 512; // change this to fit the number of steps per revolution for your motor
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // initialize the stepper library on pins 8 through 11

void releaseMotorCoils(){
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Smart Pet Feeder Initialized");
  myStepper.setSpeed(15); // set speed to 10 RPM
  Serial.println("Rotating Stepper Motor 1 Revolution...");

  releaseMotorCoils(); // Release motor coils before stepping
}

void loop() {
  Serial.println("Feeding pet...");
  myStepper.step(stepsPerRevolution); // Rotate one full revolution
  delay(120000); // Wait for 2 minutes before next feeding
  releaseMotorCoils(); // Release motor coils after stepping
}
