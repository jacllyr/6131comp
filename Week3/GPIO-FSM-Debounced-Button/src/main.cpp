#include <Arduino.h>
#include "Button.h"

ButtonState btnCurrent;
int btnPresses = 0;
const int LED_PIN = 13;
const int SWITCH_PIN = 2;
Button* button = NULL;

void setup()
{

    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    button = new Button(SWITCH_PIN);
}

void ledSwap()
{
    Serial.print("Swapping from ");
    Serial.println(digitalRead(LED_PIN));
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}


void loop()
{

    ButtonState btnRead = button->checkState();
    if (btnRead != btnCurrent)
    {
        btnCurrent = btnRead;
        switch (btnCurrent)
        {
        case ButtonState::ON:
            btnPresses++;
            Serial.print("Button Presses (");
            Serial.print(btnPresses);
            Serial.println(")");
            break;
        case ButtonState::OFF:
            break;
        }
    }
    if (btnPresses == 3)
    {
        btnPresses = 0;
        ledSwap();
    }
}