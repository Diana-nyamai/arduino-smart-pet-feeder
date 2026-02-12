#include <Arduino.h>
#include "feeding_schedule.h"

void handleMorningFeeding(const DateTime &now,
                          int feedHour,
                          int feedMinute,
                          int portionSteps,
                          bool &hasFedMorning,
                          FeedFunction feedFn)
{
    if (now.hour() == feedHour && now.minute() == feedMinute)
    {
        if (!hasFedMorning)
        {
            Serial.println("==== Morning feeding time! ====");
            feedFn(portionSteps);
            hasFedMorning = true;
        }
    }
    else
    {
        if (now.minute() != feedMinute)
        {
            hasFedMorning = false;
        }
    }
}

void handleEveningFeeding(const DateTime &now,
                          int feedHour,
                          int feedMinute,
                          int portionSteps,
                          bool &hasFedEvening,
                          FeedFunction feedFn)
{
    if (now.hour() == feedHour && now.minute() == feedMinute)
    {
        if (!hasFedEvening)
        {
            Serial.println("==== Evening feeding time! ====");
            feedFn(portionSteps);
            hasFedEvening = true;
        }
    }
    else
    {
        if (now.minute() != feedMinute)
        {
            hasFedEvening = false;
        }
    }
}

void handleManualFeeding(int buttonPin,
                         unsigned long debounceMs,
                         int portionSteps,
                         int &buttonState,
                         int &lastButtonReading,
                         unsigned long &lastDebounceTime,
                         FeedFunction feedFn)
{
    int reading = digitalRead(buttonPin);
    if (reading != lastButtonReading)
    {
        lastDebounceTime = millis();
        lastButtonReading = reading;
    }

    if ((millis() - lastDebounceTime) > debounceMs)
    {
        if (reading != buttonState)
        {
            buttonState = reading;
            if (buttonState == LOW)
            {
                Serial.println("==== Manual feed button pressed ====");
                feedFn(portionSteps);
            }
        }
    }
}
