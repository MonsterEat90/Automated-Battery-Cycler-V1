#include "sensors.h"

#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#include <Adafruit_ADS1X15.h>
#include <Adafruit_INA219.h>

#include "config.h"

static Adafruit_ADS1115 ads;
static Adafruit_INA219 ina219;

static bool ads_ok = false;
static bool ina_ok = false;

static float ntcVoltageToTemperature(
    float voltage
)
{
    if(voltage <= 0.01f)
    {
        return -999.0f;
    }

    float r_ntc =
        (3.3f * NTC_FIXED_RESISTOR / voltage)
        - NTC_FIXED_RESISTOR;

    float tempK =
        1.0f /
        (
            (1.0f / (NTC_T0 + 273.15f))
            +
            (1.0f / NTC_BETA)
            *
            log(r_ntc / NTC_R0)
        );

    return tempK - 273.15f;
}

bool sensorsBegin()
{
    Wire.begin(
        I2C_SDA_PIN,
        I2C_SCL_PIN
    );

    /*
    ADS1115
    */

    ads_ok =
        ads.begin(
            ADS1115_ADDR
        );

    if(ads_ok)
    {
        ads.setGain(
            GAIN_ONE
        );

        Serial.println(
            "[OK] ADS1115"
        );
    }
    else
    {
        Serial.println(
            "[ERR] ADS1115"
        );
    }

    /*
    INA219
    */

    ina_ok =
        ina219.begin();

    if(ina_ok)
    {
        Serial.println(
            "[OK] INA219"
        );
    }
    else
    {
        Serial.println(
            "[ERR] INA219"
        );
    }

    return (
        ads_ok &&
        ina_ok
    );
}

bool sensorsUpdate(
    SensorData& sensorData
)
{
    if(
        !ads_ok ||
        !ina_ok
    )
    {
        return false;
    }

    /*
    ADS1115
    */

    int16_t rawBattery =
        ads.readADC_SingleEnded(
            ADC_BATTERY_CHANNEL
        );

    int16_t rawNTC =
        ads.readADC_SingleEnded(
            ADC_TEMPERATURE_CHANNEL
        );

    float batteryVoltageADC =
        ads.computeVolts(
            rawBattery
        );

    float ntcVoltage =
        ads.computeVolts(
            rawNTC
        );

    /*
    INA219
    */

    float shuntVoltage =
        ina219.getShuntVoltage_mV();   // mV

    float currentA =
        shuntVoltage / 2.0f;

    /*
    Populate structure
    */

    sensorData.rawBattery =
        rawBattery;

    sensorData.rawNTC =
        rawNTC;

    sensorData.voltage =
        batteryVoltageADC *
        VOLTAGE_DIVIDER_RATIO -
        0.03f;

    sensorData.current =
        currentA;

    sensorData.power =
        sensorData.voltage *
        sensorData.current;

    sensorData.temperature =
        ntcVoltageToTemperature(
            ntcVoltage
        );

    return true;
}

bool adsConnected()
{
    return ads_ok;
}

bool inaConnected()
{
    return ina_ok;
}