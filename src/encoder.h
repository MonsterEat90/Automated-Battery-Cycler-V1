#pragma once

#include "types.h"

void encoderBegin();

void encoderUpdate(
    SystemData& systemData
);

uint8_t getSelectedMenu();

bool isEditing();