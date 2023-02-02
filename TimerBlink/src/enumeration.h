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