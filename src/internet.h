#include <ESP8266WiFi.h>

#include "credentials.h"

int connect_to_internet(int status_pin);
int connect_to_wifi(int status_pin);
void config_clock(void);