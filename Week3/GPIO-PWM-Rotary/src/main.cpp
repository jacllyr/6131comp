#include <ESP32Encoder.h>
#include <Arduino.h>
#include <enumeration.h>

const int MIN_DELAY_MS = 10;
const int MAX_DELAY_MS = 750;

const int ROTARY_A = 16;
const int ROTARY_B = 17;

const int LED_PIN = 13;

LEDState current;
ESP32Encoder encoder;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    ESP32Encoder::useInternalWeakPullResistors = UP;
    encoder.attachHalfQuad(ROTARY_A, ROTARY_B);
    encoder.setCount(100);
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

int encodercnt = 0;

// range checks the encode
void rangeCheckEncoder()
{
    if (encodercnt != encoder.getCount())
    {
        encodercnt = encoder.getCount();

        if (encodercnt >= 200)
        {
            encodercnt = 200;
            encoder.setCount(encodercnt);
        }
        else if (encodercnt <= 0)
        {
            encodercnt = 0;
            encoder.setCount(encodercnt);
        }
        Serial.println(encodercnt);
    }
}

void loop()
{
    rangeCheckEncoder();

    int delayValue = map(encodercnt, 0, 200, MIN_DELAY_MS, MAX_DELAY_MS);

    current = ledCheckUpdate(current, delayValue);
}