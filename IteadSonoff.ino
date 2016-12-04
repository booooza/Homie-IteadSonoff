/* WARNING: untested */

#include <Homie.h>

#define FW_NAME "sonoff-firmware"
#define FW_VERSION "1.0.0"

/* Magic sequence for Autodetectable Binary Upload */
const char *__FLAGGED_FW_NAME = "\xbf\x84\xe4\x13\x54" FW_NAME "\x93\x44\x6b\xa7\x75";
const char *__FLAGGED_FW_VERSION = "\x6a\x3f\x3e\x0e\xe1" FW_VERSION "\xb0\x30\x48\xd4\x1a";
/* End of magic sequence for Autodetectable Binary Upload */

const int PIN_RELAY = 12;
const int PIN_LED = 13;
const int PIN_BUTTON = 0;

HomieNode switchNode("switch", "switch");

bool switchOnHandler(String value) {
  if (value == "true") {
    digitalWrite(PIN_RELAY, HIGH);
    Homie.setNodeProperty(switchNode, "on", "true");
    Serial.println("Switch is on");
  } else if (value == "false") {
    digitalWrite(PIN_RELAY, LOW);
    Homie.setNodeProperty(switchNode, "on", "false");
    Serial.println("Switch is off");
  } else {
    return false;
  }

  return true;
}

void setup() {
  pinMode(PIN_RELAY, OUTPUT);
  /* Default Action on Start */
  digitalWrite(PIN_RELAY, HIGH);

  Homie.setFirmware(FW_NAME, FW_VERSION);
  Homie.setLedPin(PIN_LED, LOW);
  Homie.setResetTrigger(PIN_BUTTON, LOW, 5000);
  switchNode.subscribe("on", switchOnHandler);
  Homie.registerNode(switchNode);
  Homie.setup();
}

void loop() {
  Homie.loop();
}
