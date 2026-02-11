#include <Arduino.h>
#include <Stepper.h>
#include <RTClib.h>

const int stepsPerRevolution = 2048;
Stepper feederMotor(stepsPerRevolution, 8, 10, 9, 11); // Swap pins 9 and 10 for proper reversal
RTC_DS3231 rtc;

// feeding settings
const int feedSpeed = 8;
const int smallPortion = 512;
const int largePortion = 1024;

// door control settings
const int doorOpenSteps = 512;
const int doorOpenTime = 600;

// feeding schedule
const int morningFeedHour = 1;
const int feedMinutemorning = 55;
const int eveningFeedHour = 1;
const int feedMinuteEvening = 57;

// manual feed button
const int feedButtonPin = 2;
const unsigned long buttonDebounceMs = 50;

// track last feeding time
bool hasFedMorning = false;
bool hasFedEvening = false;

// button debounce state
int buttonState = HIGH;
int lastButtonReading = HIGH;
unsigned long lastDebounceTime = 0;

void releaseMotorCoils()
{
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void setup()
{
  Serial.begin(9600);

  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // set motor control pins as outputs
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // button uses internal pull-up (pressed = LOW)
  pinMode(feedButtonPin, INPUT_PULLUP);

  Serial.println("Smart Pet Feeder Initialized");
  feederMotor.setSpeed(feedSpeed); // set speed to 8 RPM

  releaseMotorCoils(); // Release motor coils before stepping
}

void openDoor()
{
  Serial.println("Opening door...");
  feederMotor.step(doorOpenSteps); // Rotate forward to open
  releaseMotorCoils();
  Serial.println("Door opened!");
}

void closeDoor()
{
  Serial.println("Closing door...");
  feederMotor.step(-doorOpenSteps); // Rotate backward to close
  releaseMotorCoils();
  Serial.println("Door closed!");
}

void feedCat(int portionSteps)
{
  Serial.print("Dispensing ");
  if (portionSteps == smallPortion)
  {
    Serial.println("Small Food Portion: ");
  }
  else
  {
    Serial.println("Large Food Portion: ");
  }

  // Open door to dispense food
  Serial.println("Opening door...");

  float feedTime = (portionSteps * 60.0) / (2048.0 * feedSpeed);
  Serial.print(" Estimated feed time: ");
  Serial.println(feedTime, 1);
  Serial.println("Seconds...");

  unsigned long startTime = millis();

  // Rotate motor to open door and dispense food in one motion
  feederMotor.step(portionSteps); // Open and dispense
  releaseMotorCoils();

  // report actual feed time
  unsigned long actualFeedTime = millis() - startTime;
  Serial.print("Actual feed time: ");
  Serial.println(actualFeedTime / 1000.0, 1);
  Serial.println(" Seconds.");

  // Wait for cat to eat
  delay(doorOpenTime);

  // Close door - return to starting position
  Serial.println("Closing door...");
  feederMotor.step(-portionSteps); // Close door
  releaseMotorCoils();
  Serial.println("Feeding complete.");
  Serial.println("Door closed!");
}

void loop()
{
  DateTime now = rtc.now();

  Serial.print("Current time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());

  // Manual feeding button (press to feed a small portion)
  int reading = digitalRead(feedButtonPin);
  if (reading != lastButtonReading)
  {
    lastDebounceTime = millis();
    lastButtonReading = reading;
  }

  if ((millis() - lastDebounceTime) > buttonDebounceMs)
  {
    if (reading != buttonState)
    {
      buttonState = reading;
      if (buttonState == LOW)
      {
        Serial.println("==== Manual feed button pressed ====");
        feedCat(smallPortion);
      }
    }
  }

  // Morning feeding
  if (now.hour() == morningFeedHour && now.minute() == feedMinutemorning)
  {
    if (!hasFedMorning)
    {
      Serial.println("==== Morning feeding time! ====");
      feedCat(largePortion); // Dispense large portion
      hasFedMorning = true;
    }
  }
  else
  {
    // Reset morning flag when we're past the feeding minute
    if (now.minute() != feedMinutemorning)
    {
      hasFedMorning = false;
    }
  }

  // Evening feeding
  if (now.hour() == eveningFeedHour && now.minute() == feedMinuteEvening)
  {
    if (!hasFedEvening)
    {
      Serial.println("==== Evening feeding time! ====");
      feedCat(largePortion); // Dispense small portion
      hasFedEvening = true;
    }
  }
  else
  {
    // Reset evening flag when we're past the feeding minute
    if (now.minute() != feedMinuteEvening)
    {
      hasFedEvening = false;
    }
  }

  delay(5000);         // check time every 5 seconds
  releaseMotorCoils(); // Release motor coils after stepping
}
