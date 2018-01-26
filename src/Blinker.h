/* Blinker.h
 *
 * Copyright (C) 2018 Jens-Christian Skibakk
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <Arduino.h>

#include <Ticker.h>

#define BLINKER_BLINK_MODE_OFF 0x00
#define BLINKER_BLINK_MODE_ONCE 0x01
#define BLINKER_BLINK_MODE_CONTINUOUS 0x02

class Blinker
{
public:
  // Constructor
  Blinker(const uint8_t, const uint16_t = 200, const uint8_t = LOW);

  // Functions
  void on();
  void off();
  void continuous(uint8_t);
  void once(uint8_t);

private:
  Ticker _ticker;

  uint8_t _pin;
  uint8_t _activeLevel;

  uint8_t _active;

  uint8_t _blinks;
  uint8_t _currentBlink;

  uint8_t _blinkMode;

  uint16_t _delay;

  static void onCallback(Blinker *blink);
  static void tickerCallback(Blinker *blink);
};
