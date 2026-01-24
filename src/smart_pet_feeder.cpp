#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048; 
Stepper feederMotor(stepsPerRevolution, 8, 9, 10, 11); // initialize the stepper on pins 8 through 11

// feeding settings
const int feedSpeed = 8;
const int smallPortion = 512;
const int largePortion = 1024;

// To prevent motor overheating, we will release the motor coils after each feeding
void releaseMotorCoils()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void setup() {
  Serial.begin(9600);

  // set motor control pins as outputs
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  Serial.println("Smart Pet Feeder Initialized");
  feederMotor.setSpeed(feedSpeed); // set speed to 10 RPM
  Serial.println("Rotating Stepper Motor 1 Revolution...");

  releaseMotorCoils(); // Release motor coils before stepping
}

void feedCat(int portionSteps){
  Serial.print("Dispensing food portion ");
  Serial.print(portionSteps);

  float feedTime = (portionSteps * 60.0) / (2048.0 * feedSpeed); // in milliseconds
  Serial.print(" Estimated feed time: ");
  Serial.println(feedTime, 1);
  Serial.println("Seconds...");

  unsigned long startTime = millis();

  feederMotor.step(portionSteps); // Rotate motor to dispense food
  releaseMotorCoils(); // Release motor coils after stepping

  // report actual feed time
  unsigned long actualFeedTime = millis() - startTime;
  Serial.print("Actual feed time: ");
  Serial.print(actualFeedTime / 1000.0, 1);
  Serial.println(" Seconds.");  
  Serial.println("Feeding complete.");
}

void loop() {
  Serial.println("Feeding pet...");
  // feederMotor.step(stepsPerRevolution); // Rotate one full revolution
  feedCat(smallPortion); // Dispense small portion
  delay(10000); // Wait for 10 seconds before next feeding
  releaseMotorCoils(); // Release motor coils after stepping
}
