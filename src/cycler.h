#pragma once

#include "types.h"

void cyclerBegin();

void cyclerStart(
    SystemData& systemData
);

void cyclerStop();

void cyclerUpdate(
    SystemData& systemData
);

bool cyclerRunning();