#include <Arduino.h>

#define BTN_PIN 0
#define LED_PIN 2

void set_led(bool on);
void IRAM_ATTR button_pressed(void);

bool btn_pressed = 0;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(200);

  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_PIN), button_pressed, FALLING);
}

void loop() {
  delay(200);

  if (btn_pressed) {
    Serial.println("pressed");
    btn_pressed = 0;
  }
}

void set_led(bool on) {
  digitalWrite(LED_PIN, on);
}

void IRAM_ATTR button_pressed(void) {
  btn_pressed = 1;
}