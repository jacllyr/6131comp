#include <Arduino.h>

enum class LEDState
{
    ON,
    OFF
};

LEDState current;

const int LED_PIN = 13;
const int SWITCH_PIN = 2;
const int LED_DELAY = 1000;
long lastChangedTime = 0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    current = LEDState::OFF;
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
        delay /= 6;
    return delay;
}

void ledOff()
{
    digitalWrite(LED_PIN, LOW);
    int delay = getLEDDelay();
    Serial.println("LED off ");
    if (timeDiff(lastChangedTime, delay))
        current = LEDState::ON;
}

void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
    int delay = getLEDDelay();
    Serial.printf("LED on ");
    if (timeDiff(lastChangedTime, delay))
        current = LEDState::OFF;
}

void loop()
{
    LEDState old = current;
    // Save start time before loop execution
    switch (current)
    {
    case LEDState::OFF:
        ledOff();
        break;
    case LEDState::ON:
        ledOn();
        break;
    }

    if (old != current)
        lastChangedTime = millis();
    
} 