# Blinker
Blinker is a library for ESP8266 programmed with Arduino, which simplifies the usage of a LED to tell the status of the sketch.

It's possible to control the led on and off, and let it blink a give number of times, either once or continuous.

## Use cases
* Boot process 
  * Blink one time continuous while booting, set to on when normal operation
* Error situations
  * Blink two, or more times continuous when in different error situations, let the numbe of blinks tell about what error has occured
* Setup mode
  * Continuous blinking while in setup mode
  
## API
