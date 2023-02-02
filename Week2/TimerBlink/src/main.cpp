#include <Arduino.h>
#include <enumeration.h>


void ledOff() {
    unsigned long ledOffStartTime = millis();
    digitalWrite(LED_PIN, LOW);
    Serial.println("DEVICE IS NOW OFF" );
    if (timeDiff(lastChangedTime, LED_OFF_FOR)) {
        current = LED_ON;
    }
    unsigned long ledOffEndTime = millis();
    Serial.print("LED off time: ");
    Serial.println(ledOffEndTime - ledOffStartTime);  // Calculate and print LED off latency
}

void ledOn() {
    unsigned long ledOnStartTime = millis();
    digitalWrite(LED_PIN, HIGH);
    Serial.println("DEVICE IS NOW ON");
    if (timeDiff(lastChangedTime, LED_ON_FOR)) {
        current = LED_OFF;
    }
    unsigned long ledOnEndTime = millis();
     Serial.print("LED on time: ");
    Serial.println(ledOnEndTime - ledOnStartTime);  // Calculate and print LED on latency
}

unsigned long loopStartTime;

void setup() {
    // put your setup code here, to run once:
    current = LED_OFF;
    pinMode(LED_PIN, OUTPUT);
    lastChangedTime = 0;
    Serial.begin(115200);
}

void loop() {
    State old = current;
    loopStartTime = millis();  // Save start time before loop execution
    switch (current) {
        case LED_OFF:
            ledOff();
            break;
        case LED_ON:
            ledOn();
            break;
    }

    if (old != current) {
        lastChangedTime = millis();
    }

    unsigned long loopEndTime = millis();  // Save end time after loop execution
    Serial.print("Loop execution time: ");
    Serial.println(loopEndTime - loopStartTime);  // Calculate and print loop latency
}