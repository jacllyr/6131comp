#include <Arduino.h>

const int LED_PIN = 2;
const int DELAY = 500;


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("ON");
  digitalWrite(LED_PIN, HIGH);
  delay(DELAY);
  Serial.println("OFF");
  digitalWrite(LED_PIN, LOW);
  delay(DELAY);
}