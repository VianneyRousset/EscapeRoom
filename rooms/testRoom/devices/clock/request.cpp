#include "request.hpp"
#include "communication.hpp"
#include "logger.hpp"
#include "device.hpp"
#include <Arduino.h>
#include "debug.hpp"

//TODO all components set/get are proccessed in another module. Any change of
//a component status send a RTN_STATUS_UPDATE"

#define argv(i) (sscanf(msg+2*i, "%2" SCNx8, &p) == 1)
#define parsingFailure(err) \
	logger_error(String(err) + String(" (got: '") + String(msg) + String("')"))

static bool execPing(Address_t, String msgstr);
static bool execGet(Address_t, String msgstr);
static bool execSet(Address_t, String msgstr);
static int sendStatusUpdate(Component_t comp, const char* status);

bool request_handler(Address_t src, String msgstr)
{
	const char* msg = msgstr.c_str();
	uint8_t p;

	logger_info(String("Trying to exec: ") + msgstr);

	if (!argv(0)) {
		parsingFailure("Failed to parse cmd code");
		return false;
	}

	switch (p) {
		case CMD_PING:
			return execPing(src, msgstr);
		case CMD_GET:
			return execGet(src, msgstr);
		case CMD_SET:
			return execSet(src, msgstr);
		default:
			parsingFailure("Invalid cmd");
			return false;
	}
}

static bool execPing(Address_t, String msgstr)
{
	ReturnCode_t rtn[] = {RTN_PING_BACK};
	com_send(1, rtn);
	return true;
}

static bool execGet(Address_t, String msgstr)
{
	const char* msg = msgstr.c_str();
	uint8_t p;

	if (!argv(1)) {
		parsingFailure("Failed to parse component code for 'get'");
		return false;
	}

	switch (p) {
		case COMP_LED_BUILTIN:
			switch (digitalRead(LED_BUILTIN)) {
				case LOW:
					sendStatusUpdate(COMP_LED_BUILTIN, "00");
					return 1;
				case HIGH:
					sendStatusUpdate(COMP_LED_BUILTIN, "01");
					return 1;
			}
			return true;
		default:
			parsingFailure("Invalid component code for 'get'");
			return false;
	}

	return false;
}


static bool execSet(Address_t, String msgstr)
{
	const char* msg = msgstr.c_str();
	uint8_t p;

	if (!argv(1)) {
		parsingFailure("Failed to parse component code for 'set'");
		return false;
	}


	switch (p) {

		case COMP_LED_BUILTIN:
			if (!argv(2)) {
				parsingFailure("Failed to parse status code for 'set'");
				return false;
			}
			switch (p) {
				case 0:
					digitalWrite(LED_BUILTIN, LOW);
					return true;
				case 1:
					digitalWrite(LED_BUILTIN, HIGH);
					return true;
				default:
					parsingFailure("Invalid status code for 'set'");
					return false;
			}

		default:
			parsingFailure("Invalid component code for 'set'");

	}

	return false;
}

static int sendStatusUpdate(Component_t comp, const char* status) {
	char tmp[3] = "  ";
	sprintf(tmp, "%02x", RTN_STATUS_UPDATE);
	String rtn(tmp);
	sprintf(tmp, "%02x", comp);
	return com_send(rtn + String(tmp) + String(status));
}
