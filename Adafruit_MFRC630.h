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
#ifndef __ADAFRUIT_MFRC630_H__
#define __ADAFRUIT_MFRC630_H__

#include "Arduino.h"
#include <Wire.h>
#include "Adafruit_MFRC630_regs.h"

#define MFRC630_I2C_ADDR              (0x28)

/* Debug output level */
#define MFRC630_VERBOSITY_RELEASE     (0)   /* No debug output */
#define MFRC630_VERBOSITY_DEBUG       (1)   /* Debug message output */
#define MFRC630_VERBOSITY_TRACE       (2)   /* Full packet trace dumps */
#define MFRC630_VERBOSITY = MFRC630_VERBOSITY_TRACE

/* Macro for debug output */
#ifdef MFRC630_VERBOSITY >= MFRC630_VERBOSITY_DEBUG
  #define DEBUG_PRINT(...)   Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#else
  #define DEBUG_PRINT(...)
  #define DEBUG_PRINTLN(...)
#endif

/* Macro for trace output */
#ifdef MFRC630_VERBOSITY >= MFRC630_VERBOSITY_TRACE
  #define TRACE_PRINT(...)   Serial.print(__VA_ARGS__)
  #define TRACE_PRINTLN(...) Serial.println(__VA_ARGS__)
  #define TRACE_TIMESTAMP()  Serial.print("\t[+"); \
                             Serial.print(millis()); \
                             Serial.print("ms] ");
#else
  #define TRACE_PRINT(...)
  #define TRACE_PRINTLN(...)
  #define TRACE_TIMESTAMP(...)
#endif

class Adafruit_MFRC630
{
  public:
    Adafruit_MFRC630(int8_t pdown_pin = -1, uint8_t i2c_addr = MFRC630_I2C_ADDR);
    Adafruit_MFRC630(TwoWire* wireBus, int8_t pdown_pin = -1, uint8_t i2c_addr = MFRC630_I2C_ADDR);
    bool begin(void);

  private:
    int8_t _pdown;
    uint8_t _i2c_addr;
    TwoWire* _wire;

    void write8(byte reg, byte value);
    byte read8(byte reg);
    byte readBuffer(byte reg, byte len, uint8_t *buffer);
};

#endif
