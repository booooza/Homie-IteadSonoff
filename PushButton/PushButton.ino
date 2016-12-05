#include <Homie.h>

const int PIN_BUTTON = 0;

Bounce debouncer = Bounce(); // Bounce is built into Homie, so you can use it without including it first
int lastButtonValue = -1;

HomieNode buttonNode("button", "button");

void loopHandler() {
  int buttonValue = debouncer.read();

  if (buttonValue != lastButtonValue) {
     Serial.print("Door is now: ");
     Serial.println(buttonValue ? "open" : "close");

     if (Homie.setNodeProperty(buttonNode, "open", buttonValue ? "true" : "false", true)) {
       lastButtonValue = buttonValue;
     } else {
       Serial.println("Sending failed");
     }
  }
}

void setup() {
  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUTTON, HIGH);
  debouncer.attach(PIN_BUTTON);
  debouncer.interval(50);

  Homie.setResettable(false);
  Homie.enableLogging(true);
  Homie.setFirmware("awesome-button", "1.0.0");
  Homie.registerNode(buttonNode);
  Homie.setLoopFunction(loopHandler);
  Homie.setup();
}

void loop() {
  Homie.loop();
  debouncer.update();
}
