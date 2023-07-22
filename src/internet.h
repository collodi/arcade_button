#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "credentials.h"
#include "device_info.h"

// TODO local DNS
#define SERVER "http://192.168.0.13:5000"

int connect_to_internet(int status_pin);
int connect_to_wifi(int status_pin);
void config_clock(void);

int register_with_server(void);
int report_button_push(int64_t);