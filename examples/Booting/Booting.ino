#include <Blinker.h>

// blink the builtin led, with 200ms timing, LED is on when output in LOW
Blinker blinker(LED_BUILTIN, 200, LOW);

void setup() {
  // blink two times continuous
  blinker.continuous(2);

  // connect to WiFi etc ...
  delay(5000);

  // when all is done, set led on
  blinker.on();
}

void loop() {
}
