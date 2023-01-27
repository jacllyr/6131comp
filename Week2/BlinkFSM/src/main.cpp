#include <Arduino.h>

enum State
{
  LED_ON,
  LED_OFF
};

State current;
unsigned long lastChangedTime;

const int LED_PIN = 12;
const int LED_OFF_FOR = 750;
const int LED_ON_FOR = 250;

// returns true if specifiedDelay has elapsed since start (millis() values)
boolean timeDiff(unsigned long start, int specifiedDelay)
{
  return (millis() - start >= specifiedDelay);
}

void ledOff()
{
  digitalWrite(LED_PIN, LOW);
  Serial.println("DEVICE IS NOW OFF");
  if (timeDiff(lastChangedTime, LED_OFF_FOR))
    current = LED_ON;
}

void ledOn()
{
  digitalWrite(LED_PIN, HIGH);
  Serial.println("DEVICE IS NOW ON");
  if (timeDiff(lastChangedTime, LED_ON_FOR))
    current = LED_OFF;
}

void setup()
{
  // put your setup code here, to run once:
  current = LED_OFF;
  pinMode(LED_PIN, OUTPUT);
  lastChangedTime = 0;

  Serial.begin(115200);
}

void loop()
{
  State old = current;
  switch (current)
  {
  case LED_OFF:
    ledOff();
    break;

  case LED_ON:
    ledOn();
    break;
  }

  if (old != current)
    lastChangedTime = millis();
}
