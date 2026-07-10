#pragma once

#include <Arduino.h>

/*
==================================================
SYSTEM STATES
==================================================
*/

enum class CycleState
{
    IDLE,

    DISCHARGE,

    CHARGE,

    FINISHED,

    ERROR_STATE
};


/*
==================================================
DISCHARGE MODES
==================================================
*/

enum class DischargeMode
{
    CONSTANT_CURRENT,

    CONSTANT_POWER
};


/*
==================================================
SENSOR DATA
==================================================
*/

struct SensorData
{
    /*
    Battery Measurements
    */

    float voltage = 0.0f;       // V
    float current = 0.0f;       // A
    float power = 0.0f;         // W

    float temperature = 0.0f;   // °C

    /*
    Raw ADC Values
    */

    int16_t rawBattery = 0;
    int16_t rawNTC = 0;
};


/*
==================================================
USER SETTINGS
==================================================
*/

struct TestSettings
{
    /*
    Number of cycles
    */

    uint16_t cycleTarget = 1;

    /*
    Discharge Mode
    */

    DischargeMode mode =
        DischargeMode::CONSTANT_CURRENT;

    /*
    CC Mode
    */

    float ccCurrent = 3.5f;     // A

    /*
    CP Mode
    */

    float cpPower = 11.2f;      // W
};


/*
==================================================
LIVE TEST DATA
==================================================
*/

struct CycleData
{
    /*
    Current cycle
    */

    uint16_t cycleNumber = 0;

    /*
    Capacity
    */

    float dischargeCapacity_mAh = 0.0f;

    /*
    Energy
    */

    float dischargeEnergy_Wh = 0.0f;

    /*
    Runtime
    */

    uint32_t elapsedSeconds = 0;
};


/*
==================================================
SAFETY STATUS
==================================================
*/

struct FaultFlags
{
    bool underVoltage = false;

    bool overVoltage = false;

    bool overCurrent = false;

    bool overTemperature = false;

    bool sensorError = false;

    bool sdError = false;
};


/*
==================================================
SYSTEM DATA
==================================================
*/

struct SystemData
{
    CycleState state =
        CycleState::IDLE;

    SensorData sensors;

    TestSettings settings;

    CycleData cycle;

    FaultFlags faults;
};

enum class MenuItem
{
    CYCLE_COUNT,
    MODE,
    SETPOINT,
    START
};

enum class UiState
{
    NAVIGATE,
    EDIT
};