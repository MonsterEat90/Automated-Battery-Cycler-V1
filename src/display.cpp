#include "display.h"

#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

static Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

static const char* stateToString(
    CycleState state
)
{
    switch(state)
    {
        case CycleState::IDLE:
            return "IDLE";

        case CycleState::DISCHARGE:
            return "DCHG";

        case CycleState::CHARGE:
            return "CHRG";

        case CycleState::FINISHED:
            return "DONE";

        case CycleState::ERROR_STATE:
            return "ERROR";
    }

    return "---";
}

bool displayBegin()
{
    if(
        !display.begin(
            SSD1306_SWITCHCAPVCC,
            OLED_ADDR
        )
    )
    {
        Serial.println(
            "[ERR] OLED"
        );

        return false;
    }

    display.clearDisplay();

    display.setTextSize(1);

    display.setTextColor(
        SSD1306_WHITE
    );

    display.display();

    Serial.println(
        "[OK] OLED"
    );

    return true;
}

void displayMenu(
    const TestSettings& settings,
    uint8_t selectedItem,
    bool editing
)
{
    display.clearDisplay();

    display.setCursor(0,0);

    display.print(
        selectedItem == 0 ?
        (editing ? "*" : ">")
        :
        " "
    );

    display.print("cycle=");

    display.println(
        settings.cycleTarget
    );

    display.print(
        selectedItem == 1 ?
        (editing ? "*" : ">")
        :
        " "
    );

    display.print("mode=");

    if(
        settings.mode ==
        DischargeMode::CONSTANT_CURRENT
    )
    {
        display.println("CC");
    }
    else
    {
        display.println("CP");
    }

    display.print(
        selectedItem == 2 ?
        (editing ? "*" : ">")
        :
        " "
    );

    display.print("set=");

    if(
        settings.mode ==
        DischargeMode::CONSTANT_CURRENT
    )
    {
        display.print(
            settings.ccCurrent,
            1
        );

        display.println("A");
    }
    else
    {
        display.print(
            settings.cpPower,
            1
        );

        display.println("W");
    }

    display.print(
        selectedItem == 3 ?
        (editing ? "*" : ">")
        :
        " "
    );

    display.print("start>");

    display.display();
}

void displayRun(
    const SystemData& systemData
)
{
    display.clearDisplay();

    display.setCursor(0,0);

    display.print(
        systemData.sensors.voltage,
        2
    );

    display.print("V ");

    display.print(
        systemData.sensors.current,
        2
    );

    display.println("A");

    display.print(
        systemData.sensors.power,
        1
    );

    display.print("W ");

    display.print(
        systemData.sensors.temperature,
        1
    );

    display.println("C");

    display.print("C:");

    display.print(
        systemData.cycle.cycleNumber
    );

    display.print(" ");

    display.print(
        stateToString(
            systemData.state
        )
    );

    display.display();
}

void displayError(
    const SystemData& systemData
)
{
    display.clearDisplay();

    display.setCursor(0,0);

    display.println("ERROR");

    if(
        systemData.faults.overTemperature
    )
    {
        display.println("TEMP");
    }
    else if(
        systemData.faults.overCurrent
    )
    {
        display.println("CURRENT");
    }
    else if(
        systemData.faults.overVoltage
    )
    {
        display.println("OVERVOLT");
    }
    else if(
        systemData.faults.underVoltage
    )
    {
        display.println("UNDERVOLT");
    }
    else
    {
        display.println("UNKNOWN");
    }

    display.display();
}

