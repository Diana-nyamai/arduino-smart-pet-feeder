#pragma once

#include <RTClib.h>

typedef void (*FeedFunction)(int portionSteps);

void handleMorningFeeding(const DateTime &now,
                          int feedHour,
                          int feedMinute,
                          int portionSteps,
                          bool &hasFedMorning,
                          FeedFunction feedFn);

void handleEveningFeeding(const DateTime &now,
                          int feedHour,
                          int feedMinute,
                          int portionSteps,
                          bool &hasFedEvening,
                          FeedFunction feedFn);

void handleManualFeeding(int buttonPin,
                         unsigned long debounceMs,
                         int portionSteps,
                         int &buttonState,
                         int &lastButtonReading,
                         unsigned long &lastDebounceTime,
                         FeedFunction feedFn);
