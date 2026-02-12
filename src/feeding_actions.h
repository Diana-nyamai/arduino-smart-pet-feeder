#pragma once

#include <Stepper.h>

void feedCat(Stepper &motor,
             int portionSteps,
             int smallPortionSteps,
             int feedSpeedRpm,
             int stepsPerRevolution,
             int doorOpenTimeMs,
             void (*releaseMotorCoilsFn)());
