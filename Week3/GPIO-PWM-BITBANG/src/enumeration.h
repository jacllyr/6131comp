#include <Arduino.h>


enum class LEDState
{
  ON,
  OFF
};


// returns true if specifiedDelay has elapsed since start (millis() values)
boolean usTimeDiff(unsigned long start, int specifiedDelay)
{
  return (micros() - start >= specifiedDelay);
}