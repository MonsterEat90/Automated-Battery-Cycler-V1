#include <Arduino.h>
#include "load.h"
#include "config.h"

static uint16_t currentPWM = 0;

void loadBegin()
{
    ledcSetup(
        PWM_CHANNEL,
        PWM_FREQUENCY,
        PWM_RESOLUTION
    );

    ledcAttachPin(
        LOAD_PWM_PIN,
        PWM_CHANNEL
    );

    loadOff();

    Serial.println(
        "[OK] Load Ready"
    );
}

void setLoadPWM(
    uint16_t pwm
)
{
    currentPWM =
        constrain(
            pwm,
            PWM_MIN,
            PWM_MAX
        );

    ledcWrite(
        PWM_CHANNEL,
        currentPWM
    );
}

uint16_t getLoadPWM()
{
    return currentPWM;
}

void loadOff()
{
    currentPWM = 0;

    ledcWrite(
        PWM_CHANNEL,
        0
    );
}

void loadFullOn()
{
    currentPWM =
        PWM_MAX;

    ledcWrite(
        PWM_CHANNEL,
        PWM_MAX
    );
}