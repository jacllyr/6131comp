#include <Arduino.h>
#include <HardwareSerial.h>

void setup() {
	Serial.begin(115200);
}

void loop() {
	const char end = '.';

	const char * charStr = "Hello";
	char charArrStr[] = { 'H', 'e', 'l', 'l', 'o', '\0', 'a', 'l', 'l' };
	String ardStr = "Hello";
	char* dynCharArr = new char[20];
	dynCharArr[0] = 'H';
	dynCharArr[1] = 'e';
	dynCharArr[2] = 'l';
	dynCharArr[3] = 'l';
	dynCharArr[4] = 'o';
	dynCharArr[5] = '\0';

	char* dynCharArr2 = new char[20];
	dynCharArr2[0] = 'H';
	dynCharArr2[1] = 'e';
	dynCharArr2[2] = 'l';
	dynCharArr2[3] = 'l';
	dynCharArr2[4] = 'o';

	Serial.print(charStr);
	Serial.println(end);
	Serial.print(charArrStr);
	Serial.println(end);
	Serial.print(ardStr);
	Serial.println(end);
	Serial.print(dynCharArr);
	Serial.println(end);
	Serial.print(dynCharArr2);
	Serial.println(end);
	Serial.println("------");

//	delete[] dynCharArr;
//	delete[] dynCharArr2;

	delay(2000);

}
