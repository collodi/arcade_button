#include "internet.h"

int connect_to_internet(int status_pin) {
	while (true) {
		delay(2000);

		int conn = connect_to_wifi(status_pin);
		if (conn == 0) // connected
			return 0;

		if (conn == 2) // error, don't retr
			return 1;
	}
}

/*
	ret 0 = connected
	1 = error, retry
	2 = error, don't retry
*/
int connect_to_wifi(int status_pin) {
	WiFi.begin(SSID, PWD);

	while (WiFi.status() != WL_CONNECTED) {
        if (status_pin != -1)
            digitalWrite(status_pin, LOW);

		delay(1000);

        if (status_pin != -1)
            digitalWrite(status_pin, HIGH);

		delay(1000);

		wl_status_t stat = WiFi.status();
		if (stat == 4) {
			return 1;
		}

		// TODO no ssid error
		// TODO connection lost error
		// TODO wrong password error
	}

	return 0;
}

void config_clock(void) {
	configTime(0, 0, "pool.ntp.org", "time.nist.gov");
	time_t now = time(nullptr);

	// wait for clock to be set up
	while (now < 1510592825) {
		delay(1000);
		time(&now);
	}
}

int register_with_server(void) {
	char data[100];
	String ip = WiFi.localIP().toString();
	sprintf(data, "id=%06x&group=%s&color=%s&ip=%s", ESP.getChipId(), GROUP, COLOR, ip.c_str());

    HTTPClient http;
	WiFiClient wifi;

    http.begin(wifi, SERVER "/register");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int code = http.POST(data);

    String response = http.getString();
    http.end();

    if (code == 200 && response.compareTo("OK") == 0)
        return 0;

    return 1;
}

int report_button_push(int64_t epoch) {
	char data[100];
	sprintf(data, "id=%06x&epoch=%lld", ESP.getChipId(), epoch);

    HTTPClient http;
	WiFiClient wifi;

    http.begin(wifi, SERVER "/push");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int code = http.POST(data);

    String response = http.getString();
    http.end();

    if (code == 200 && response.compareTo("OK") == 0)
        return 0;

    return 1;
}