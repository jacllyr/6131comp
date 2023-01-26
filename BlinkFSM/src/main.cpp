#include <Arduino.h>


enum State {
  LED_ON,
  LED_OFF
};

State current;
const int LED_PIN = 12;
const int LED_DELAY = 1000;
unsigned long lastChangeTime;

boolean timeDiff(unsigned long start, int specifiedDelay) {
  return (millis()-start >= specifiedDelay);
}

void setup() {
  // put your setup code here, to run once:
  current = LED_OFF;
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  State old = current;
  switch (current) {
    case LED_OFF:
      digitalWrite(LED_PIN, LOW);
      if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_ON;
         Serial.println("hello jac");
      break;

    case LED_ON:
      digitalWrite(LED_PIN, HIGH);
      if (timeDiff(lastChangeTime, LED_DELAY))
        current = LED_OFF;
  
    break;
  }
  if (old != current)
  lastChangeTime = millis();
}

