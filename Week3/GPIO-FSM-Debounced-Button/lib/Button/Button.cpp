int pinny;

#include "Button.h"
#include <Arduino.h>

Button::Button(){}

Button::Button(int pin)
{
    this->pin = pin;
    pinMode(this->pin, INPUT);
    this->lastChange = 0;
}

ButtonState Button::checkState()
{
    ButtonState now = ButtonState::OFF;
    if (digitalRead(pin))
        now = ButtonState::ON;

    if (now != bouncedState)
    {
        lastChange = millis();
        bouncedState = now;
    }

    if ((millis() - lastChange) >= BOUNCE_DELAY_MS)
        debouncedState = now;

    return debouncedState;
}
