#include <Arduino.h>

enum ButtonState
{
    ON,
    OFF
};

// returns true if specifiedDelay has elapsed since start (millis() values)
boolean timeDiff(unsigned long start, int specifiedDelay)
{
    return (millis() - start >= specifiedDelay);
}


ButtonState btnCurrent;

const int LED_PIN = 13;
const int SWITCH_PIN = 2;
const int LED_DELAY = 1000;
unsigned long NumberOfCounts;
int btnPresses = 0;

const int BOUNCE_DELAY_MS = 5;
ButtonState debouncedState = OFF;
ButtonState bouncedState = OFF;
long lastChange;

ButtonState getButtonState()
{
    ButtonState now = OFF;

    if (digitalRead(SWITCH_PIN))
        now = ON;

    if (now != bouncedState)
    {
        lastChange = millis();
        bouncedState = now;
    }

    if (timeDiff(lastChange, BOUNCE_DELAY_MS))
        debouncedState = now;

    return debouncedState;
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    btnCurrent = ButtonState::OFF;
}


int getLEDDelay()
{

    int delay = LED_DELAY;
    if (digitalRead(SWITCH_PIN) == HIGH)
        delay /= 2;
    return delay;
}

void ledOff()
{
    digitalWrite(LED_PIN, LOW);
    int delay = getLEDDelay();
    if (timeDiff(btnPresses, delay))
        btnCurrent = ButtonState::ON;
}

void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
    int delay = getLEDDelay();
    if (timeDiff(btnPresses, delay))
        btnCurrent = ButtonState::OFF;
}

void ledSwap()
{
    Serial.print("Swapping from ");
    Serial.println(digitalRead(LED_PIN));
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void loop()
{
    ButtonState now = getButtonState();
    if (now != btnCurrent)
    {
        // Save start time before loop execution
        btnCurrent = now;
        switch (btnCurrent)
        {
        case ON:
            btnPresses++;
            Serial.print("Button Presses (");
            Serial.print(btnPresses);
            Serial.println(")");
            break;
        case OFF:
            break;
        }
    }
    if (btnPresses == 3)
    {
        btnPresses = 0;
        ledSwap();
    }
}