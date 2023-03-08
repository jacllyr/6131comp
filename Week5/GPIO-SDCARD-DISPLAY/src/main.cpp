#include <Arduino.h>
#include "SPIFFS.h"


void setup() {
  Serial.begin(115200);
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("Error mounting SPIFFS");
    return;
  }
  // File file = SPIFFS.open("/myfile.txt", FILE_WRITE);
  // file.println("Test");
  // file.close();
}


void loop() {
  // Open the file for reading
  File file = SPIFFS.open("/myfile.txt", "r");
  
  // If the file opened successfully, read its contents
  if (file) {
    // Read the contents of the file and print it to the serial monitor
    while (file.available()) {
      Serial.write(file.read());
    }
    // Close the file
    file.close();
  }
  
  // Wait for some time before reading the file again
  delay(5000);
}
