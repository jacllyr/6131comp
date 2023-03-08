#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 17     // DHT11 data pin is connected to digital pin 2
#define DHTTYPE DHT11 // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

int redPin = 12;   // Red pin of the RGB LED is connected to digital pin 9
int greenPin = 14; // Green pin of the RGB LED is connected to digital pin 10
int bluePin = 13;  // Blue pin of the RGB LED is connected to digital pin 11

const boolean invert = false;

uint8_t color = 0;        // a value from 0 to 255 representing the hue
uint32_t R, G, B;         // the Red Green and Blue color components
uint8_t brightness = 200; // 255 is maximum brightness, but can be changed

void setup()
{
    Serial.begin(115200);      // Start serial communication for debugging
    dht.begin();               // Initialize the DHT11 sensor
    pinMode(redPin, OUTPUT);   // Set the red pin as output
    pinMode(greenPin, OUTPUT); // Set the green pin as output
    pinMode(bluePin, OUTPUT);  // Set the blue pin as output
}

// function to convert a color to its Red, Green, and Blue components.
void hueToRGB(uint8_t hue, uint8_t brightness)
{
    uint16_t scaledHue = (hue * 6);
    uint8_t segment = scaledHue / 256; // segment 0 to 5 around the
    // color wheel
    uint16_t segmentOffset =
        scaledHue - (segment * 256); // position within the segment

    uint8_t complement = 0;
    uint16_t prev = (brightness * (255 - segmentOffset)) / 256;
    uint16_t next = (brightness * segmentOffset) / 256;

    if (invert)
    {
        brightness = 255 - brightness;
        complement = 255;
        prev = 255 - prev;
        next = 255 - next;
    }

    switch (segment)
    {
    case 0:                                                     // red
        analogWrite(redPin, (brightness * R) / 255);
        analogWrite(greenPin, (brightness * next) / 255);
        analogWrite(bluePin, (brightness * complement) / 255);
        break;
    case 1:                                                     // yellow
        analogWrite(redPin, (brightness * prev) / 255);
        analogWrite(greenPin, (brightness * brightness) / 255);
        analogWrite(bluePin, (brightness * complement) / 255);
        break;
    case 2:                                                     // green
        analogWrite(redPin, (brightness * complement) / 255);
        analogWrite(greenPin, (brightness * brightness) / 255);
        analogWrite(bluePin, (brightness * next) / 255);
        break;
    case 3:                                                    // cyan 
        analogWrite(redPin, (brightness * complement) / 255);
        analogWrite(greenPin, (brightness * prev) / 255);
        analogWrite(bluePin, (brightness * brightness) / 255);
        break;
    case 4:                                               // blue               
        analogWrite(redPin, (brightness * next) / 255);
        analogWrite(greenPin, (brightness * complement) / 255);
        analogWrite(bluePin, (brightness * brightness) / 255);
        break;
    case 5:                                              // magenta                     
        analogWrite(redPin, (brightness * brightness) / 255);
        analogWrite(greenPin, (brightness * complement) / 255);
        analogWrite(bluePin, (brightness * prev) / 255);
        break;
    }
}


// function to convert a color to its Red, Green, and Blue components.
void hueToRGB(uint8_t hue)
{
   uint16_t scaledHue = (hue * 6);
    uint8_t segment = scaledHue / 256; // segment 0 to 5 around the
    // color wheel
    uint16_t segmentOffset =
        scaledHue - (segment * 256); // position within the segment

    uint8_t complement = 0;
    uint16_t prev = (brightness * (255 - segmentOffset)) / 256;
    uint16_t next = (brightness * segmentOffset) / 256;

    if (invert)
    {
        brightness = 255 - brightness;
        complement = 255;
        prev = 255 - prev;
        next = 255 - next;
    }

    switch (segment)
    {
    case 0:
        analogWrite(redPin, brightness);
        analogWrite(greenPin, next);
        analogWrite(bluePin, complement);
        break;
    case 1:
        analogWrite(redPin, prev);
        analogWrite(greenPin, brightness);
        analogWrite(bluePin, complement);
        break;
    case 2:
        analogWrite(redPin, complement);
        analogWrite(greenPin, brightness);
        analogWrite(bluePin, next);
        break;
    case 3:
        analogWrite(redPin, complement);
        analogWrite(greenPin, prev);
        analogWrite(bluePin, brightness);
        break;
    case 4:
        analogWrite(redPin, next);
        analogWrite(greenPin, complement);
        analogWrite(bluePin, brightness);
        break;
    case 5:
        analogWrite(redPin, brightness);
        analogWrite(greenPin, complement);
        analogWrite(bluePin, prev);
        break;
    }
}



void loop() {
  delay(2000);  // Wait for 2 seconds between readings

  // Read the temperature and humidity values from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print the temperature and humidity values for debugging
  Serial.println("Sensor 1 data:");
  Serial.println("Temp: " + String(temperature) + "'C Humidity: " + String(humidity) + "%");

  // Change the color of the RGB LED based on the temperature value
  if (temperature < 20) {
    // If the temperature is less than 20°C, set the LED to blue
    hueToRGB(170, 255); // Set the color to blue
  } else if (temperature < 25) {
    // If the temperature is between 20°C and 25°C, set the LED to green
    hueToRGB(85, 50); // Set the color to green
  } else {
    // If the temperature is greater than or equal to 25°C, set the LED to red
    hueToRGB(0, 255); // Set the color to red
  }


}
