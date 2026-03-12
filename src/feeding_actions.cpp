#include <Arduino.h>
#include "feeding_actions.h"

void feedCat(Stepper &motor,
             int portionSteps,
             int smallPortionSteps,
             int feedSpeedRpm,
             int stepsPerRevolution,
             int doorOpenTimeMs,
             void (*releaseMotorCoilsFn)())
{
    Serial.print("Dispensing ");
    if (portionSteps == smallPortionSteps)
    {
        Serial.println("Small Food Portion: ");
    }
    else
    {
        Serial.println("Large Food Portion: ");
    }

    Serial.println("Starting dispense...");

    float feedTime = (portionSteps * 60.0) / (stepsPerRevolution * feedSpeedRpm);
    Serial.print(" Estimated feed time: ");
    Serial.println(feedTime, 1);
    Serial.println("Seconds...");

    unsigned long startTime = millis();

    motor.step(portionSteps);
    releaseMotorCoilsFn();

    unsigned long actualFeedTime = millis() - startTime;
    Serial.print("Actual feed time: ");
    Serial.println(actualFeedTime / 1000.0, 1);
    Serial.println(" Seconds.");

    delay(doorOpenTimeMs);

    Serial.println("Feeding complete.");
    Serial.println("Dispense finished.");
}
