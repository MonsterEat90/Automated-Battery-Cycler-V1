#include "safety.h"

#include <Arduino.h>

#include "config.h"

void safetyBegin()
{
    Serial.println(
        "[OK] Safety Ready"
    );
}

void safetyUpdate(
    SystemData& systemData
)
{
    /*
    Clear old faults
    */

    systemData.faults =
        FaultFlags();

    /*
    ==========================================
    UNDER VOLTAGE
    ==========================================
    */

    if(
        systemData.sensors.voltage
        <
        DISCHARGE_MIN_VOLTAGE
    )
    {
        systemData.faults.underVoltage =
            true;
    }

    /*
    ==========================================
    OVER VOLTAGE
    ==========================================
    */

    if(
        systemData.sensors.voltage
        >
        CHARGE_MAX_VOLTAGE
    )
    {
        systemData.faults.overVoltage =
            true;
    }

    /*
    ==========================================
    OVER CURRENT
    ==========================================
    */

    if(
        systemData.sensors.current
        >
        MAX_CURRENT
    )
    {
        systemData.faults.overCurrent =
            true;
    }

    /*
    ==========================================
    OVER TEMPERATURE
    ==========================================
    */

    if(
        systemData.sensors.temperature
        >
        MAX_TEMPERATURE
    )
    {
        systemData.faults.overTemperature =
            true;
    }

    /*
    ==========================================
    SENSOR FAILURE
    ==========================================
    */

    if(
        systemData.sensors.temperature
        <
        -100.0f
    )
    {
        systemData.faults.sensorError =
            true;
    }

    /*
    ==========================================
    ERROR CHECK
    ==========================================
    */

    if(
        systemData.faults.underVoltage
        ||
        systemData.faults.overVoltage
        ||
        systemData.faults.overCurrent
        ||
        systemData.faults.overTemperature
        ||
        systemData.faults.sensorError
    )
    {
        systemData.state =
            CycleState::ERROR_STATE;
    }
}

void printFaults(
    const FaultFlags& faults
)
{
    if(faults.underVoltage)
    {
        Serial.println(
            "[FAULT] Under Voltage"
        );
    }

    if(faults.overVoltage)
    {
        Serial.println(
            "[FAULT] Over Voltage"
        );
    }

    if(faults.overCurrent)
    {
        Serial.println(
            "[FAULT] Over Current"
        );
    }

    if(faults.overTemperature)
    {
        Serial.println(
            "[FAULT] Over Temperature"
        );
    }

    if(faults.sensorError)
    {
        Serial.println(
            "[FAULT] Sensor Error"
        );
    }
}

void printFaults(
    const FaultFlags& faults
);