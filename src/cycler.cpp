#include "cycler.h"

#include <Arduino.h>

#include "config.h"
#include "relay.h"
#include "load.h"
#include "controller.h"
#include "logger.h"

static bool running = false;

static uint32_t fullChargeTimer = 0;
static uint32_t lastSecond = 0;

void cyclerBegin()
{
    running = false;
    fullChargeTimer = 0;
}

void cyclerStart(SystemData& systemData)
{
    controllerReset();

    setDischargeMode();

    processEnable();

    systemData.cycle = CycleData();

    lastSecond = millis();

    fullChargeTimer = 0;

    systemData.state = CycleState::DISCHARGE;

    running = true;

    Serial.println("[STATE] START -> DISCHARGE");
}

void cyclerStop()
{
    processDisable();

    loadOff();

    controllerReset();

    loggerStop();

    fullChargeTimer = 0;

    running = false;

    Serial.println("[CYCLER] STOP");
}

bool cyclerRunning()
{
    return running;
}

void cyclerUpdate(SystemData& systemData)
{
    /*
    ==========================================
    Runtime Counter
    ==========================================
    */

    if(
        running &&
        millis() - lastSecond >= 1000
    )
    {
        lastSecond += 1000;

        systemData.cycle.elapsedSeconds++;
    }

    switch(systemData.state)
    {
        /*
        ==========================================
        IDLE
        ==========================================
        */

        case CycleState::IDLE:
        {
            break;
        }

        /*
        ==========================================
        DISCHARGE
        ==========================================
        */

        case CycleState::DISCHARGE:
        {
            controllerUpdate(
                systemData.sensors,
                systemData.settings
            );

            if(
                systemData.sensors.voltage
                <=
                DISCHARGE_STOP_VOLTAGE
            )
            {
                Serial.println(
                    "[STATE] DISCHARGE -> CHARGE"
                );

                controllerReset();

                setChargeMode();

                fullChargeTimer = 0;

                systemData.state =
                    CycleState::CHARGE;
            }

            break;
        }

        /*
        ==========================================
        CHARGE
        ==========================================
        */

        case CycleState::CHARGE:
        {
            loadOff();

            if(
                systemData.sensors.voltage >= CHARGE_FULL_VOLTAGE &&
                systemData.sensors.current <= CHARGE_FULL_CURRENT
            )
            {
                if(fullChargeTimer == 0)
                {
                    fullChargeTimer = millis();

                    Serial.println(
                        "[CHARGE] Waiting for full confirmation..."
                    );
                }

                if(
                    millis() - fullChargeTimer >=
                    CHARGE_FULL_DELAY_MS
                )
                {
                    systemData.cycle.cycleNumber++;

                    Serial.print(
                        "[CYCLER] Cycle "
                    );

                    Serial.println(
                        systemData.cycle.cycleNumber
                    );

                    if(
                        systemData.cycle.cycleNumber >=
                        systemData.settings.cycleTarget
                    )
                    {
                        Serial.println(
                            "[STATE] CHARGE -> FINISHED"
                        );

                        systemData.state =
                            CycleState::FINISHED;
                    }
                    else
                    {
                        Serial.println(
                            "[STATE] CHARGE -> DISCHARGE"
                        );

                        controllerReset();

                        setDischargeMode();

                        fullChargeTimer = 0;

                        systemData.state =
                            CycleState::DISCHARGE;
                    }
                }
            }
            else
            {
                fullChargeTimer = 0;
            }

            break;
        }

        /*
        ==========================================
        FINISHED
        ==========================================
        */

        case CycleState::FINISHED:
        {
            cyclerStop();

            break;
        }

        /*
        ==========================================
        ERROR
        ==========================================
        */

        case CycleState::ERROR_STATE:
        {
            cyclerStop();

            break;
        }
    }
}