#pragma once

#include "types.h"

bool sensorsBegin();

bool sensorsUpdate(
    SensorData& sensorData
);

bool adsConnected();

bool inaConnected();