#pragma once

#include "types.h"

/*
==================================================
INITIALIZATION
==================================================
*/

bool displayBegin();

/*
==================================================
SCREENS
==================================================
*/

void displayMenu(
    const TestSettings& settings,
    uint8_t selectedItem,
    bool editing
);

void displayRun(
    const SystemData& systemData
);

void displayError(
    const SystemData& systemData
);