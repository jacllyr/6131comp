#include <Arduino.h>
#include <enumeration.h>

const int MIN_ANALOGUE = 0;
const int MAX_ANALOGUE = 4096;
const int MAX_PWM_DUTY = 100;
const int MIN_PWM_DUTY = 0;

const int LED_PIN = 13;
const int RES_PIN = 26;

LEDState current;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
}

unsigned long lastChangeTime;
LEDState ledCheckUpdate(LEDState currentState, int duty)
{
    int delayValue = duty * 100;
    int delayValueOff = 1000 - duty;

    if (currentState == LEDState::ON && usTimeDiff(lastChangeTime, delayValue))
        currentState = LEDState::OFF;
    else if (usTimeDiff(lastChangeTime, delayValueOff))
    {
        currentState = LEDState::ON;
        lastChangeTime = micros();
    }
    if (currentState == LEDState::ON)
        digitalWrite(LED_PIN, HIGH);
    else
        digitalWrite(LED_PIN, LOW);
    return currentState;
}

int oldDuty = 0;


void loop()
{
    int aRead = analogRead(RES_PIN);
    int duty = map(aRead, MIN_ANALOGUE, MAX_ANALOGUE, MIN_PWM_DUTY, MAX_PWM_DUTY);
    analogWrite(LED_PIN, duty); // Analog LED light get's brighter when light is shown to photoresistor
    if (oldDuty != duty && millis() % 500 == 0)
    {
        oldDuty = duty;
        Serial.print("led bitbang ");
        Serial.println(duty);
    }
    //current = ledCheckUpdate(current, duty); // Analog LED light get's dimmer when covering photoresistor

    // Serial.println(aRead);
}