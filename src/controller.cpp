#include "controller.h"

#include <Arduino.h>

#include "config.h"
#include "load.h"

static uint16_t pwmOutput = 0;

void controllerBegin()
{
    pwmOutput = 0;

    loadOff();

    Serial.println(
        "[OK] Controller Ready"
    );
}

void controllerReset()
{
    pwmOutput = 0;

    loadOff();
}

uint16_t getControllerPWM()
{
    return pwmOutput;
}

/*
==================================================
CONSTANT CURRENT
==================================================
*/

static void controlCC(
    float targetCurrent,
    float measuredCurrent
)
{
    float error =
        targetCurrent -
        measuredCurrent;

    if(error > 0.20f)
    {
        pwmOutput += 8;
    }
    else if(error > 0.05f)
    {
        pwmOutput += 2;
    }
    else if(error < -0.20f)
    {
        pwmOutput -= 8;
    }
    else if(error < -0.05f)
    {
        pwmOutput -= 2;
    }
}

/*
==================================================
CONSTANT POWER
==================================================
*/

static void controlCP(
    float targetPower,
    float measuredPower
)
{
    float error =
        targetPower -
        measuredPower;

    if(error > 0.50f)
    {
        pwmOutput += 8;
    }
    else if(error > 0.10f)
    {
        pwmOutput += 2;
    }
    else if(error < -0.50f)
    {
        pwmOutput -= 8;
    }
    else if(error < -0.10f)
    {
        pwmOutput -= 2;
    }
}

/*
==================================================
UPDATE
==================================================
*/

void controllerUpdate(
    const SensorData& sensors,
    const TestSettings& settings
)
{
    switch(settings.mode)
    {
        case DischargeMode::CONSTANT_CURRENT:
        {
            controlCC(
                settings.ccCurrent,
                sensors.current
            );
            break;
        }

        case DischargeMode::CONSTANT_POWER:
        {
            controlCP(
                settings.cpPower,
                sensors.power
            );
            break;
        }
    }

    pwmOutput =
        constrain(
            pwmOutput,
            PWM_MIN,
            PWM_MAX
        );

    setLoadPWM(
        pwmOutput
    );
}