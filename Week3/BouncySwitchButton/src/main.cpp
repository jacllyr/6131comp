#include <Arduino.h>

enum ButtonState
{
    ON,
    OFF
};

ButtonState btnCurrent;

const int LED_PIN = 13;
const int SWITCH_PIN = 2;
const int LED_DELAY = 1000;
unsigned long NumberOfCounts;

void ledSwap()
{
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

ButtonState getButtonState () {
    if (digitalRead(SWITCH_PIN))
    return ON;
    else
    return OFF;
}


void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    btnCurrent = ButtonState::OFF;
}

// returns true if specifiedDelay has elapsed since start (millis() values)
boolean timeDiff(unsigned long start, int specifiedDelay)
{
    return (millis() - start >= specifiedDelay);
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
    Serial.printf("LED off ");
    if (timeDiff(btnPresses, delay))
        btnCurrent = ButtonState::ON;
}

void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
    int delay = getLEDDelay();
    Serial.printf("LED on ");
    Serial.printf("Number of counts ", btnPresses);
    if (timeDiff(btnPresses, delay))
        btnCurrent = ButtonState::OFF;
}

void loop()
{
    ButtonState now = getButtonState();
    // Save start time before loop execution
    btnCurrent = now;
    switch (btnCurrent)
    {
    case ON:
    btnPresses++;
        break;
    case OFF:
        break;
    }

    if (btnPresses == 1) {
        btnPresses = 0;
        ledSwap();
    }
} 