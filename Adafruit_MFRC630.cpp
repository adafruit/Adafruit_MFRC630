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

#include <Wire.h>

#include "Adafruit_MFRC630.h"

/***************************************************************************
 PRIVATE FUNCTIONS
 ***************************************************************************/

 /**************************************************************************/
 /*!
     @brief  Write a byte to the specified register
 */
 /**************************************************************************/
void Adafruit_MFRC630::write8(byte reg, byte value)
{
  #ifdef MFRC630_VERBOSITY >= MFRC630_VERBOSITY_TRACE
  TRACE_TIMESTAMP();
  TRACE_PRINT("WRITE 0x");
  TRACE_PRINT(value, HEX);
  TRACE_PRINT(" to 0x");
  TRACE_PRINTLN(reg, HEX);
  #endif

  _wire->beginTransmission(_i2c_addr);
  _wire->write(reg);
  _wire->write(value);
  _wire->endTransmission();
}

/**************************************************************************/
/*!
    @brief  Read a byte from the specified register
*/
/**************************************************************************/
byte Adafruit_MFRC630::read8(byte reg)
{
  uint8_t value;

  readBuffer(reg, 1, &value);

  return value;
}

/**************************************************************************/
/*!
    @brief  Read 'len' bytes from the specified register
*/
/**************************************************************************/
byte Adafruit_MFRC630::readBuffer(byte reg, byte len, uint8_t *buffer)
{
  uint8_t i;

  #ifdef MFRC630_VERBOSITY >= MFRC630_VERBOSITY_TRACE
  TRACE_TIMESTAMP();
  TRACE_PRINT("RQST ");
  TRACE_PRINT(len);
  TRACE_PRINT(" byte(s) from 0x");
  TRACE_PRINTLN(reg, HEX);
  #endif

  #ifdef __SAM3X8E__
    /* http://forum.arduino.cc/index.php?topic=385377.msg2947227#msg2947227 */
    _wire->requestFrom(_i2c_addr, len, reg, 1, true);
  #else
    _wire->beginTransmission(_i2c_addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(_i2c_addr, (byte)len);
  #endif

  /* Dump the response into the supplied buffer */
  for (i=0; i<len; i++)
  {
    buffer[i] = _wire->read();
  }

  #ifdef MFRC630_VERBOSITY >= MFRC630_VERBOSITY_TRACE
  TRACE_TIMESTAMP();
  TRACE_PRINT("RESP ");
  TRACE_PRINT(len);
  TRACE_PRINT(" byte(s):");
  for (i=0; i<len; i++)
  {
    TRACE_PRINT(" 0x");
    if (buffer[i] <= 0xF)
    {
      TRACE_PRINT("0");
    }
    TRACE_PRINT(buffer[i], HEX);
  }
  TRACE_PRINTLN("");
  #endif

  return len;
}

/***************************************************************************
 CONSTRUCTOR
 ***************************************************************************/

 /**************************************************************************/
 /*!
     @brief  Instantiates a new instance of the Adafruit_MFRC630 class
 */
 /**************************************************************************/
 Adafruit_MFRC630::Adafruit_MFRC630(uint8_t i2c_addr)
 {
   /* Set the I2C bus instance */
   _wire = &Wire;

   /* Set the I2C address */
   _i2c_addr = i2c_addr;
 }

/**************************************************************************/
/*!
    @brief  Instantiates a new instance of the Adafruit_MFRC630 class
*/
/**************************************************************************/
Adafruit_MFRC630::Adafruit_MFRC630(TwoWire* wireBus, uint8_t i2c_addr)
{
  /* Set the I2C bus instance */
  _wire = wireBus;

  /* Set the I2C address */
  _i2c_addr = i2c_addr;
}

/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Sets up the HW
*/
/**************************************************************************/
bool Adafruit_MFRC630::begin()
{
  /* Enable I2C */
  DEBUG_PRINTLN("Initialising I2C");
  _wire->begin();

  /* Check device ID for bus response */
  DEBUG_PRINT("Checking I2C address 0x");
  DEBUG_PRINTLN(_i2c_addr, HEX);

  /* Read the VERSION register */
  byte ver = read8(MFRC630_REG_VERSION);

  /* If !1.8, there was a problem */
  if (ver != 0x18)
  {
    DEBUG_PRINTLN("FAILED!");
    return false;
  }

  DEBUG_PRINT("IC Version = ");
  DEBUG_PRINT((ver & 0xF0) >> 4, HEX);
  DEBUG_PRINT(".");
  DEBUG_PRINTLN(ver & 0x0F, HEX);

  return true;
}
