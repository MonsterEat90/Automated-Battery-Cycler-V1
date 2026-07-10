#include "logger.h"

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "config.h"

static bool sdReady = false;

static const char* stateToString(CycleState state)
{
    switch(state)
    {
        case CycleState::IDLE:        return "IDLE";
        case CycleState::DISCHARGE:   return "DISCHARGE";
        case CycleState::CHARGE:      return "CHARGE";
        case CycleState::FINISHED:    return "FINISHED";
        case CycleState::ERROR_STATE: return "ERROR";
    }

    return "UNKNOWN";
}

bool loggerBegin()
{
    if(!SD.begin(SD_CS_PIN))
    {
        Serial.println("[ERR] SD Card");
        sdReady = false;
        return false;
    }

    Serial.println("[OK] SD Card");

    sdReady = true;

    if(!SD.exists(LOG_FILENAME))
    {
        File file =
            SD.open(LOG_FILENAME, FILE_WRITE);

        if(!file)
        {
            Serial.println("[ERR] Create Log File");
            sdReady = false;
            return false;
        }

        file.println(
            "Time_s,Cycle,State,Voltage,Current,Power,Temperature"
        );

        file.close();
    }

    return true;
}

bool loggerReady()
{
    return sdReady;
}

void loggerUpdate(const SystemData& systemData)
{
    if(!sdReady)
    {
        return;
    }

    File file =
        SD.open(LOG_FILENAME, FILE_APPEND);

    Serial.print("[LOG] ");
    Serial.println(systemData.cycle.elapsedSeconds);

    if(!file)
    {
        Serial.println("[ERR] Open Log File");
        return;
    }

    file.print(systemData.cycle.elapsedSeconds);
    file.print(",");

    file.print(systemData.cycle.cycleNumber);
    file.print(",");

    file.print(stateToString(systemData.state));
    file.print(",");

    file.print(systemData.sensors.voltage,3);
    file.print(",");

    file.print(systemData.sensors.current,3);
    file.print(",");

    file.print(systemData.sensors.power,3);
    file.print(",");

    file.println(systemData.sensors.temperature,1);

    file.flush();
    file.close();
}

void loggerStop()
{
    Serial.println("[LOGGER] Closed");
}