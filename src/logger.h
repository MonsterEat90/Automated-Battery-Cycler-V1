#pragma once

#include "types.h"

bool loggerBegin();

void loggerUpdate(
    const SystemData& systemData
);

bool loggerReady();
void loggerStop();