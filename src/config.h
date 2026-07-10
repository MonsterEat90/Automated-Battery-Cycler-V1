#pragma once
#include <Arduino.h>

constexpr const char PROJECT_NAME[] = "Battery Cycler V1";
constexpr const char FW_VERSION[]   = "1.0.0";

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

#define ADS1115_ADDR 0x48
#define INA219_ADDR 0x40
#define OLED_ADDR 0x3C

#define ENC_CLK_PIN 25
#define ENC_DT_PIN 33
#define ENC_SW_PIN 32

#define RELAY_CUT_PIN 15
#define RELAY_MODE_PIN 4

#define LOAD_PWM_PIN 27

#define SD_CS_PIN 5

#define ADC_BATTERY_CHANNEL 0
#define ADC_TEMPERATURE_CHANNEL 1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

/*
==================================================
VOLTAGE DIVIDER
==================================================
Battery ---- 10k ---- ADC ---- 10k ---- GND

Ratio = (R1 + R2) / R2 = 2.0
==================================================
*/
constexpr float VOLTAGE_R1 = 9930.0f;
constexpr float VOLTAGE_R2 = 9920.0f;

constexpr float VOLTAGE_DIVIDER_RATIO =
    (VOLTAGE_R1 + VOLTAGE_R2) / VOLTAGE_R2;

/*
==================================================
NTC PARAMETERS
==================================================
10k NTC
Beta = 3950
==================================================
*/
constexpr float NTC_BETA = 3950.0f;
constexpr float NTC_R0 = 9930.0f;
constexpr float NTC_T0 = 25.0f;

constexpr float NTC_FIXED_RESISTOR = 10000.0f;

/*
==================================================
BATTERY LIMITS
==================================================
*/
constexpr float CHARGE_STOP_VOLTAGE = 3.65f;
constexpr float CHARGE_MAX_VOLTAGE  = 3.70f;

constexpr float DISCHARGE_STOP_VOLTAGE = 2.30f;
constexpr float DISCHARGE_MIN_VOLTAGE  = 2.10f;

constexpr float MAX_TEMPERATURE = 75.0f;
constexpr float MAX_CURRENT = 5.0f;

constexpr float CC_DISCHARGE_CURRENT = 3.5f;
constexpr float CP_DISCHARGE_POWER = 11.2f;

constexpr uint16_t MIN_CYCLE_COUNT = 1;
constexpr uint16_t MAX_CYCLE_COUNT = 4000;

constexpr float MIN_CC_CURRENT = 0.5f;
constexpr float MAX_CC_CURRENT = 5.0f;
constexpr float CC_STEP = 0.1f;

constexpr float MIN_CP_POWER = 1.0f;
constexpr float MAX_CP_POWER = 12.0f;
constexpr float CP_STEP = 0.1f;

/*
==================================================
CHARGE TERMINATION
==================================================
*/

constexpr float CHARGE_FULL_VOLTAGE = 3.60f;

constexpr float CHARGE_FULL_CURRENT = 0.20f;

constexpr uint32_t CHARGE_FULL_DELAY_MS = 30000;   // 30 seconds

/*
==================================================
LOGGING
==================================================
*/
constexpr uint32_t LOG_INTERVAL_MS = 1000;
constexpr const char LOG_FILENAME[] = "/cycler.csv";

/*
==================================================
STATE MACHINE TIMING
==================================================
*/
constexpr uint32_t SENSOR_UPDATE_MS = 100;
constexpr uint32_t DISPLAY_UPDATE_MS = 200;
constexpr uint32_t CONTROL_UPDATE_MS = 20;

/*
==================================================
LOAD PWM
==================================================
*/
constexpr uint8_t PWM_CHANNEL = 0;
constexpr uint32_t PWM_FREQUENCY = 20000;
constexpr uint8_t PWM_RESOLUTION = 10;
constexpr uint16_t PWM_MIN = 0;
constexpr uint16_t PWM_MAX = 1023;