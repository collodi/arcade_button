#include <Arduino.h>

#include "internet.h"

#define BTN_PIN 0
#define LED_PIN 2

void set_led(bool on);
void IRAM_ATTR button_pressed(void);
int64_t get_epoch_ms(void);

bool btn_pressed = 0;
time_t push_epoch = 0;

void setup() {
	Serial.begin(115200);
	Serial.setTimeout(200);

	pinMode(BTN_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);

	attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_pressed, FALLING);

	WiFi.mode(WIFI_STA);
	connect_to_internet(2);

	config_clock();

	// TODO register with server
}

void loop() {
	delay(200);

	if (btn_pressed) {
		push_epoch = get_epoch_ms();
		Serial.println(push_epoch);
		// TODO report to server
		btn_pressed = 0;
	}

	// TODO listen to server
}

void set_led(bool on) {
	digitalWrite(LED_PIN, on);
}

void IRAM_ATTR button_pressed(void) {
	btn_pressed = 1;
}

int64_t get_epoch_ms() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000LL + (tv.tv_usec / 1000LL);
}