#include "encoder.h"
#include "types.h"

#include <Arduino.h>
#include <RotaryEncoder.h>

#include "config.h"
#include "cycler.h"

static RotaryEncoder encoder(
    ENC_CLK_PIN,
    ENC_DT_PIN,
    RotaryEncoder::LatchMode::TWO03
);

static int lastPosition = 0;

static uint8_t selectedItem = 0;

static UiState uiState =
    UiState::NAVIGATE;

void encoderBegin()
{
    pinMode(
        ENC_SW_PIN,
        INPUT_PULLUP
    );

    encoder.setPosition(0);

    lastPosition = 0;

    Serial.println(
        "[OK] Encoder"
    );
}

static int readRotation()
{
    encoder.tick();

    int position =
        encoder.getPosition();

    int movement =
        position -
        lastPosition;

    lastPosition =
        position;

    return movement;
}

static bool buttonPressed()
{
    static bool lastState = HIGH;
    static uint32_t lastDebounce = 0;

    bool state =
        digitalRead(
            ENC_SW_PIN
        );

    bool pressed = false;

    if(
        millis() - lastDebounce > 50
    )
    {
        if(
            lastState == HIGH &&
            state == LOW
        )
        {
            pressed = true;
            lastDebounce = millis();
        }
    }

    lastState = state;

    return pressed;
}

void encoderUpdate(
    SystemData& systemData
)
{
    encoder.tick();
    int move =
        readRotation();

    /*
    =====================================
    NAVIGATION MODE
    =====================================
    */

    if(
        uiState ==
        UiState::NAVIGATE
    )
    {
        if(move > 0)
        {
            if(selectedItem < 3)
            {
                selectedItem++;
            }
        }

        if(move < 0)
        {
            if(selectedItem > 0)
            {
                selectedItem--;
            }
        }

        if(buttonPressed())
        {
            if(
                selectedItem ==
                static_cast<uint8_t>(
                    MenuItem::START
                )
            )
            {
                cyclerStart(
                    systemData
                );
            }
            else
            {
                uiState =
                    UiState::EDIT;
            }
        }
    }

    /*
    =====================================
    EDIT MODE
    =====================================
    */

    else
    {
        switch(
            static_cast<MenuItem>(
                selectedItem
            )
        )
        {
            case MenuItem::CYCLE_COUNT:
            {
                systemData.settings.cycleTarget += move;

                systemData.settings.cycleTarget =
                    constrain(
                        systemData.settings.cycleTarget,
                        MIN_CYCLE_COUNT,
                        MAX_CYCLE_COUNT
                    );
                break;
            }

            case MenuItem::MODE:
            {
                if(move != 0)
                {
                    if(
                        systemData.settings.mode ==
                        DischargeMode::CONSTANT_CURRENT
                    )
                    {
                        systemData.settings.mode =
                            DischargeMode::CONSTANT_POWER;
                    }
                    else
                    {
                        systemData.settings.mode =
                            DischargeMode::CONSTANT_CURRENT;
                    }
                }
                break;
            }

            case MenuItem::SETPOINT:
            {
                if(move != 0)
                {
                    if(
                        systemData.settings.mode ==
                        DischargeMode::CONSTANT_CURRENT
                    )
                    {
                    systemData.settings.ccCurrent +=
                        move * CC_STEP;

                    systemData.settings.ccCurrent =
                        constrain(
                            systemData.settings.ccCurrent,
                            MIN_CC_CURRENT,
                            MAX_CC_CURRENT
                        );
                    }
                    else
                    {
                        systemData.settings.cpPower +=
                            move * CP_STEP;

                        systemData.settings.cpPower =
                            constrain(
                                systemData.settings.cpPower,
                                MIN_CP_POWER,
                                MAX_CP_POWER
                            );
                    }
                }

                break;
            }

            default:
                break;
        }

        if(buttonPressed())
        {
            uiState =
                UiState::NAVIGATE;
        }
    }
}

uint8_t getSelectedMenu()
{
    return selectedItem;
}

bool isEditing()
{
    return (
        uiState ==
        UiState::EDIT
    );
}
