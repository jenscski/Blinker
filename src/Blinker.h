/* Blinker.h
 *
 * Copyright (C) 2018 Jens-Christian Skibakk
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <Arduino.h>

#include <Ticker.h>

class Blinker
{
public:
  // Constructor
  Blinker(const uint8_t, const uint16_t = 200, const uint8_t = LOW);

  // Functions
  void on();
  void off();
  void blink(uint8_t);

private:
  Ticker _ticker;

  uint8_t _pin;
  uint8_t _activeLevel;

  uint8_t _blinks;
  uint8_t _currentBlink;

  uint16_t _delay;

  static void tickerCallback(Blinker *blink);
};
