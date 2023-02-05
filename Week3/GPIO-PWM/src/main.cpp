#include <Arduino.h>
#include <enumeration.h>

const int MIN_ADC = 0;
const int MAX_ADC = 4096;
const int MAX_DELAY_MS = 1500;
const int MIN_DELAY_MS = 200;

const int LED_PIN = 13;
const int RES_PIN = 26;

    void
    setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
}

unsigned long lastChangeTime;
LEDState ledCheckUpdate(LEDState state, int delayValue)
{
    LEDState old = state;
    if (timeDiff(lastChangeTime, delayValue))
    {
        if (state == LEDState::ON)
            state = LEDState::OFF;
        else
            state = LEDState::ON;
    }
    if (state == LEDState::ON)
        digitalWrite(LED_PIN, HIGH);
    else
        digitalWrite(LED_PIN, LOW);

    if (old != state)
        lastChangeTime = millis();
    return state;
}

LEDState current;

void loop()
{
    int aRead = analogRead(RES_PIN);
    int delayValue = map(aRead, MIN_ADC, MAX_ADC, MIN_DELAY_MS, MAX_DELAY_MS);

    current = ledCheckUpdate(current, delayValue);

    Serial.println(aRead);
}