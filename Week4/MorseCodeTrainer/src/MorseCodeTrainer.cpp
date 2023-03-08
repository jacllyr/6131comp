
#include <memory>
#include "Arduino.h"
#include "enumeration.h"
#include "Button.h"
#include "Press.h"

Button* btn = nullptr;
ButtonState current = ButtonState::OFF;
long lastLog;
long pressedAtMillis;
const int BUTTON_HOLDDOWN_DELAY = 2500;

long recordEpoch;
std::shared_ptr<Press> start = nullptr; //the start of our rhythm
std::shared_ptr<Press> last = nullptr; //last recorded Press

Mode mode = Mode::RECORDING;
long playbackEpoch;
std::shared_ptr<Press> playing; // currently "playing" Press


void setup() {
	Serial.begin(115200);
	pinMode(LED_PIN, OUTPUT);
	btn = new Button(SWITCH_PIN);
}

/**
 * Prints out the sequence represented by the specified Press*
 * @param current - the specified Press pointer, or nullptr
 */
void dumpSequence(std::shared_ptr<Press> current) {
	int counter = 0;
	while (current != nullptr) {

		Serial.print("Starts at ");
		Serial.print(current->start);
		Serial.print(" (");
		Serial.print(current->duration);
		Serial.println(")");

		current = current->next;
		counter++;
	}
	Serial.print("Counted ");
	Serial.println(counter);
}


/**
 * called once each time the button is released
 */
void buttonUp() {
	int pressedDuration = millis() - pressedAtMillis;
	if (pressedDuration > (BUTTON_HOLDDOWN_DELAY * 2)) {
		if (start != nullptr) {
			int count = start->deleteSequence();
			Serial.print("Deleted sequence length");
			Serial.println(count);
			last = start = nullptr;
			mode = Mode::RECORDING;
		} else {
			Serial.println("Request to delete, but no sequence recorded");
		}
		lastLog = millis(); // reset timer
	} else if (pressedDuration > BUTTON_HOLDDOWN_DELAY) {

		//create dummy pause press
		last = last->createNext(pressedAtMillis - recordEpoch,
				pressedAtMillis - recordEpoch);

		Serial.println("Beginning playback");
		playbackEpoch = millis();
		dumpSequence(start);
		playing = start;
		mode = Mode::PLAYING;
		lastLog = millis(); // reset timer
	} else {
		if (mode == Mode::RECORDING) {
			if (last == nullptr) {
				recordEpoch = pressedAtMillis;
				last = start = std::make_shared<Press>(pressedAtMillis - recordEpoch,
						millis() - recordEpoch);
			} else {
				last = last->createNext(pressedAtMillis - recordEpoch,
						millis() - recordEpoch);
			}
		}
	}
}


/**
 * Uses Button to check the (debounced) state of the connected button.
 * It will call other methods on state changes as required.
 */
void buttonCheck() {
	ButtonState now = btn->checkState();
	if (now != current) {
		current = now;
		if (current == ButtonState::ON) {
			pressedAtMillis = millis();
		} else
			buttonUp();
	}

}

/**
 * Logging method - reports button holddown and free RAM
 */
void logCheck() {
	int pressedFor = millis() - pressedAtMillis;
	if (current == ButtonState::ON && pressedFor > 0
			&& pressedFor % 1000 == 0) {
		if (millis() - lastLog > 5) {
			Serial.print("Button held for ");
			Serial.print(pressedFor);
			Serial.println(" secs");
			lastLog = millis();
		}
	}

	if (millis() - lastLog > 2500) {
		Serial.print("Free RAM: ");
		Serial.print(ESP.getFreeHeap());
		Serial.println(" bytes");
		lastLog = millis();
	}
}

/**
 * Iterates though the sequence (LL) of Press objects.
 * It turns the LED on at the current Press object's start time, and off at the end time.
 * At the end time, it iterates to the next Press in the linked list
 * If at the end, it starts again
 */
void playBack() {
	if (mode == Mode::PLAYING) {
		if (playing != nullptr) {
			long playBackTime = millis() - playbackEpoch;
			if (playBackTime >= playing->start) {
				if (playBackTime >= playing->getEndTime()) {
					//led off, next playing item
					digitalWrite(LED_PIN, LOW);
					playing = playing->next;
					if (playing == nullptr) {
						Serial.println("---Restarting");
						playing = start; // roll over
						playbackEpoch = millis();
					}
				} else
					// led on,
					digitalWrite(LED_PIN, HIGH);
			}
		}
	} else
		digitalWrite(LED_PIN, LOW);
}

/**
 * Main loop method - 3 responsibilities
 * -check for button presses
 * -check and update the log
 * -run playback routine
 */
void loop() {
	buttonCheck();
	logCheck();
	playBack();
}

