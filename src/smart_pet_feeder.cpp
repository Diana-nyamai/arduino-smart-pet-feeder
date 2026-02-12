#include <Arduino.h>
#include <Stepper.h>
#include <RTClib.h>
#include "feeding_actions.h"
#include "feeding_schedule.h"

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
const int morningFeedHour = 6;
const int morningFeedMinute = 0;
const int eveningFeedHour = 18;
const int eveningFeedMinute = 0;

// manual feed button
const int feedButtonPin = 2;
const unsigned long buttonDebounceMs = 10;

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
  feederMotor.setSpeed(feedSpeed);

  releaseMotorCoils();
}

void openDoor()
{
  Serial.println("Opening door...");
  feederMotor.step(doorOpenSteps);
  releaseMotorCoils();
  Serial.println("Door opened!");
}

void closeDoor()
{
  Serial.println("Closing door...");
  feederMotor.step(-doorOpenSteps);
  releaseMotorCoils();
  Serial.println("Door closed!");
}

void feedPortion(int portionSteps)
{
  feedCat(feederMotor,
          portionSteps,
          smallPortion,
          feedSpeed,
          stepsPerRevolution,
          doorOpenTime,
          releaseMotorCoils);
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

  handleManualFeeding(feedButtonPin,
                      buttonDebounceMs,
                      smallPortion,
                      buttonState,
                      lastButtonReading,
                      lastDebounceTime,
                      feedPortion);

  handleMorningFeeding(now,
                       morningFeedHour,
                       morningFeedMinute,
                       largePortion,
                       hasFedMorning,
                       feedPortion);

  handleEveningFeeding(now,
                       eveningFeedHour,
                       eveningFeedMinute,
                       largePortion,
                       hasFedEvening,
                       feedPortion);

  delay(5000); // check time every 5 seconds
  releaseMotorCoils();
}
