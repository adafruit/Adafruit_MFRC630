/***************************************************************************
  This is a library for the Adafruit MFRC630 Breakout

  Designed specifically to work with the Adafruit MFRC630 Breakout:
  http://www.adafruit.com/products/xxx

  These boards use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <stdint.h>

#ifndef __ADAFRUIT_MFRC630_CONSTS_H__
#define __ADAFRUIT_MFRC630_CONSTS_H__

extern uint8_t antcfg_iso14443a_106[18];
extern uint8_t antcfg_iso14443a_212[18];
extern uint8_t antcfg_iso14443a_424[18];
extern uint8_t antcfg_iso14443a_848[18];

extern uint8_t protcfg_iso14443a_106[24];
extern uint8_t protcfg_iso14443a_212[24];
extern uint8_t protcfg_iso14443a_424[24];
extern uint8_t protcfg_iso14443a_848[24];

#endif
