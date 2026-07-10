#pragma once

#include "types.h"

void controllerBegin();

void controllerUpdate(
    const SensorData& sensors,
    const TestSettings& settings
);

uint16_t getControllerPWM();

void controllerReset();