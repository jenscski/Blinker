/* Blinker.cpp
 *
 * Copyright (C) 2018 Jens-Christian Skibakk
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */

#include <Blinker.h>

Blinker::Blinker(const uint8_t pin, const uint16_t delay, const uint8_t activeLevel)
{
  _pin = pin;
  _delay = delay;
  _activeLevel = activeLevel;
  _active = 0;
  _blinks = 0;
  _currentBlink = 0;
  _blinkMode = BLINKER_BLINK_MODE_OFF;

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, !_activeLevel); // turn led off
}

void Blinker::on(void)
{
  _ticker.detach(); // stop ticker
  _blinkMode = BLINKER_BLINK_MODE_OFF;
  _active = 1;

  digitalWrite(_pin, _activeLevel);
}

void Blinker::off(void)
{
  _ticker.detach(); // stop ticker
  _blinkMode = BLINKER_BLINK_MODE_OFF;
  _active = 0;

  digitalWrite(_pin, !_activeLevel);
}

void Blinker::continuous(uint8_t blinks)
{
  if (_blinkMode == BLINKER_BLINK_MODE_OFF)
  {
    _blinkMode = BLINKER_BLINK_MODE_CONTINUOUS;
    _blinks = blinks;
    _currentBlink = 0;

    _ticker.detach(); // stop ticker
    tickerCallback(this);
  }
}

void Blinker::once(uint8_t blinks)
{
  if (_blinkMode == BLINKER_BLINK_MODE_OFF)
  {
    _blinkMode = BLINKER_BLINK_MODE_ONCE;
    _blinks = blinks;
    _currentBlink = 0;

    _ticker.detach(); // stop ticker

    if (_active)
    {
      digitalWrite(_pin, !_activeLevel);
      _ticker.once_ms(_delay, tickerCallback, this);
    }
    else
      tickerCallback(this);
  }
}

void Blinker::onCallback(Blinker *blinker)
{
  blinker->on();
}

void Blinker::tickerCallback(Blinker *blinker)
{
  if ((blinker->_currentBlink + 1) / 2 >= blinker->_blinks)
  {
    if (blinker->_blinkMode == BLINKER_BLINK_MODE_CONTINUOUS)
    {
      digitalWrite(blinker->_pin, !blinker->_activeLevel); // turn led off

      blinker->_currentBlink = 0;
      blinker->_ticker.once_ms(blinker->_delay * 3, tickerCallback, blinker);
    }
    else if (blinker->_active)
    {
      digitalWrite(blinker->_pin, !blinker->_activeLevel); // turn led off
      blinker->_ticker.once_ms(blinker->_delay, onCallback, blinker);
    }
    else
    {
      blinker->off();
    }
  }
  else if (blinker->_currentBlink % 2 == 0)
  {
    digitalWrite(blinker->_pin, blinker->_activeLevel); // turn led on

    blinker->_currentBlink++;
    blinker->_ticker.once_ms(blinker->_delay, tickerCallback, blinker);
  }
  else
  {
    digitalWrite(blinker->_pin, !blinker->_activeLevel); // turn led off

    blinker->_currentBlink++;
    blinker->_ticker.once_ms(blinker->_delay, tickerCallback, blinker);
  }
}
