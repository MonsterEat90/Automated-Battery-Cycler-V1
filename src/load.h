#pragma once

#include <Arduino.h>

void loadBegin();

void setLoadPWM(
    uint16_t pwm
);

uint16_t getLoadPWM();

void loadOff();

void loadFullOn();