#include <Arduino.h>

#include "config.h"
#include "types.h"

#include "sensors.h"
#include "relay.h"
#include "load.h"
#include "controller.h"
#include "cycler.h"
#include "safety.h"
#include "display.h"
#include "encoder.h"
#include "logger.h"

SystemData systemData;

static uint32_t sensorTimer = 0;
static uint32_t controlTimer = 0;
static uint32_t displayTimer = 0;
static uint32_t loggerTimer = 0;

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println(PROJECT_NAME);
    Serial.println(FW_VERSION);

    /*Hardware*/
    sensorsBegin();
    relayBegin();
    loadBegin();

    /*Logic*/
    controllerBegin();
    cyclerBegin();
    safetyBegin();

    /*UI*/
    displayBegin();
    encoderBegin();

    /*Storage*/
    loggerBegin();

    /*Initial State*/
    systemData.state = CycleState::IDLE;
    systemData.settings.cycleTarget = 1;
    systemData.settings.mode = DischargeMode::CONSTANT_CURRENT;
}

void loop()
{
    uint32_t now = millis();

    if(now - controlTimer >= 20)
    {
        controlTimer = now;

        if(
            systemData.state ==
            CycleState::IDLE
        )
        {
            encoderUpdate(
                systemData
            );
        }
    }

    if(now - sensorTimer >= 100)
    {
        sensorTimer = now;

        sensorsUpdate(
            systemData.sensors
        );

        safetyUpdate(
            systemData
        );

        cyclerUpdate(
            systemData
        );
    }

    if(now - displayTimer >= 200)
    {
        displayTimer = now;

        if(
            systemData.state ==
            CycleState::IDLE
        )
        {
            displayMenu(
                systemData.settings,
                getSelectedMenu(),
                isEditing()
            );
        }
        else if(
            systemData.state ==
            CycleState::ERROR_STATE
        )
        {
            displayError(
                systemData
            );
        }
        else
        {
            displayRun(
                systemData
            );
        }
    }

    if(now - loggerTimer >= 1000)
    {
        loggerTimer = now;

        loggerUpdate(
            systemData
        );
    }
}