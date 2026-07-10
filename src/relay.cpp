#include "relay.h"

#include <Arduino.h>

#include "config.h"

static bool process_enabled = false;

static bool charge_mode = false;

void relayBegin()
{
    pinMode(
        RELAY_CUT_PIN,
        OUTPUT
    );

    pinMode(
        RELAY_MODE_PIN,
        OUTPUT
    );

    processDisable();

    setDischargeMode();
}

void processEnable()
{
    digitalWrite(
        RELAY_CUT_PIN,
        HIGH
    );

    process_enabled = true;
}

void processDisable()
{
    digitalWrite(
        RELAY_CUT_PIN,
        LOW
    );

    process_enabled = false;
}

void setChargeMode()
{
    digitalWrite(
        RELAY_MODE_PIN,
        HIGH
    );

    charge_mode = true;
}

void setDischargeMode()
{
    digitalWrite(
        RELAY_MODE_PIN,
        LOW
    );

    charge_mode = false;
}

bool processEnabled()
{
    return process_enabled;
}

bool chargeModeActive()
{
    return charge_mode;
}