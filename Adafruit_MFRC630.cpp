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
  TRACE_TIMESTAMP();
  TRACE_PRINT("WRITING 0x");
  TRACE_PRINT(value, HEX);
  TRACE_PRINT(" to 0x");
  TRACE_PRINTLN(reg, HEX);

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

  TRACE_TIMESTAMP();
  TRACE_PRINT("REQUESTING ");
  TRACE_PRINT(len);
  TRACE_PRINT(" byte(s) from 0x");
  TRACE_PRINTLN(reg, HEX);

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

  TRACE_TIMESTAMP();
  TRACE_PRINT("RESPONSE (len=");
  TRACE_PRINT(len);
  TRACE_PRINT("):");
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
 Adafruit_MFRC630::Adafruit_MFRC630(int8_t pdown_pin, uint8_t i2c_addr)
 {
   /* Set the PDOWN pin */
   _pdown = pdown_pin;

   /* Set the I2C address */
   _i2c_addr = i2c_addr;

   /* Set the I2C bus instance */
   _wire = &Wire;
 }

/**************************************************************************/
/*!
    @brief  Instantiates a new instance of the Adafruit_MFRC630 class
*/
/**************************************************************************/
Adafruit_MFRC630::Adafruit_MFRC630(TwoWire* wireBus, int8_t pdown_pin, uint8_t i2c_addr)
{
  /* Set the PDOWN pin */
  _pdown = pdown_pin;

  /* Set the I2C address */
  _i2c_addr = i2c_addr;

  /* Set the I2C bus instance */
  _wire = wireBus;
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

  /* Reset the MFRC630 if possible */
  if (_pdown != -1)
  {
    DEBUG_PRINTLN("Resetting MFRC630");
    pinMode(_pdown, OUTPUT);
    digitalWrite(_pdown, HIGH);
    digitalWrite(_pdown, LOW);
    digitalWrite(_pdown, HIGH);
    digitalWrite(_pdown, LOW);
    /* Typical 2.5ms startup delay */
    delay(5);
  }

  /* Check device ID for bus response */
  DEBUG_PRINT("Checking I2C address 0x");
  DEBUG_PRINTLN(_i2c_addr, HEX);

  /* Read the VERSION register */
  byte ver = read8(MFRC630_REG_VERSION);

  /* If ver == 0xFF likely an I2C bus failure */
  if (ver == 0xFF)
  {
    DEBUG_PRINTLN("I2C bus failure!");
    return false;
  }

  /* If !1.8, there was a problem (or never chips?!?) */
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
