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
    @brief  Write a buffer to the specified register
*/
/**************************************************************************/
void Adafruit_MFRC630::writeBuffer(byte reg, byte len, uint8_t *buffer)
{
  uint8_t i;

  TRACE_TIMESTAMP();
  TRACE_PRINT("WRITING ");
  TRACE_PRINT(len);
  TRACE_PRINT(" byte(s) to 0x");
  TRACE_PRINTLN(reg, HEX);

  TRACE_TIMESTAMP();
  _wire->beginTransmission(_i2c_addr);
  _wire->write(reg);
  for (i = 0; i < len; i++)
  {
    _wire->write(buffer[i]);
    TRACE_PRINT("0x");
    TRACE_PRINT(buffer[i], HEX);
    TRACE_PRINT(" ");
  }
  _wire->endTransmission();
  TRACE_PRINTLN("");
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
  /* Display alert for DEBUG and TRACE output. */
  DEBUG_PRINTLN("\tDebug output enabled: D [+ms] Message");
  TRACE_PRINTLN("\tTrace output enabled: . [+ms] Message");

  /* Enable I2C */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("Initialising I2C");
  _wire->begin();

  /* Reset the MFRC630 if possible */
  if (_pdown != -1)
  {
    DEBUG_TIMESTAMP();
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
  DEBUG_TIMESTAMP();
  DEBUG_PRINT("Checking I2C address 0x");
  DEBUG_PRINTLN(_i2c_addr, HEX);

  /* Read the VERSION register */
  byte ver = read8(MFRC630_REG_VERSION);

  /* If ver == 0xFF likely an I2C bus failure */
  if (ver == 0xFF)
  {
    DEBUG_TIMESTAMP();
    DEBUG_PRINTLN("I2C bus failure!");
    return false;
  }

  /* If !1.8, there was a problem */
  if (ver != 0x18)
  {
    DEBUG_TIMESTAMP();
    DEBUG_PRINTLN("FAILED!");
    return false;
  }

  DEBUG_TIMESTAMP();
  DEBUG_PRINT("IC Version = ");
  DEBUG_PRINT((ver & 0xF0) >> 4, HEX);
  DEBUG_PRINT(".");
  DEBUG_PRINTLN(ver & 0x0F, HEX);

  return true;
}

/**************************************************************************/
/*!
    @brief  Determines the number of bytes in the HW FIFO buffer (max 512)

    @returns The number of bytes available in the HW FIFO buffer
*/
/**************************************************************************/
int16_t Adafruit_MFRC630::readFIFOLen(void)
{
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("Checking FIFO length");

  /* Read the MFRC630_REG_FIFO_LENGTH register */
  /* In 512 byte mode, the upper two bits are stored in FIFO_CONTROL */
  byte hi = read8(MFRC630_REG_FIFO_CONTROL);
  byte lo = read8(MFRC630_REG_FIFO_LENGTH);

  /* Determine len based on FIFO size (255 byte or 512 byte mode) */
  int16_t l = (hi & 0x80) ? lo : (((hi & 0x3) << 8) | lo);

  DEBUG_TIMESTAMP();
  DEBUG_PRINT("FIFO contains ");
  DEBUG_PRINT(l);
  DEBUG_PRINTLN(" bytes");

  return l;
}

/**************************************************************************/
/*!
    @brief  Read 'len' bytes from the HW FIFO buffer (max 512 bytes)

    @returns The number of bytes read from the FIFO, or -1 if an error occured.
*/
/**************************************************************************/
int16_t Adafruit_MFRC630::readFIFO(uint16_t len, uint8_t *buffer)
{
  int16_t counter = 0;

  /* Check for 512 byte overflow */
  if (len > 512)
  {
    return -1;
  }

  DEBUG_TIMESTAMP();
  DEBUG_PRINT("Reading ");
  DEBUG_PRINT(len);
  DEBUG_PRINTLN(" bytes from FIFO");

  /* Read len bytes from the FIFO */
  for (uint16_t i = 0; i < len; i++)
  {
    buffer[i] = read8(MFRC630_REG_FIFO_DATA);
    counter++;
  }

  return counter;
}

/**************************************************************************/
/*!
    @brief  Writes the specified number of bytes to the HW FIFO

    @returns The number of bytes written to the FIFO, -1 if an error occured.
*/
/**************************************************************************/
int16_t Adafruit_MFRC630::writeFIFO(uint16_t len, uint8_t *buffer)
{
  int counter = 0;

  /* Check for 512 byte overflow */
  if (len > 512)
  {
    return -1;
  }

  DEBUG_TIMESTAMP();
  DEBUG_PRINT("WRITING ");
  DEBUG_PRINT(len);
  DEBUG_PRINTLN(" bytes to FIFO");

  /* Write len bytes to the FIFO */
  for (uint16_t i = 0; i < len; i++)
  {
    write8(MFRC630_REG_FIFO_DATA, buffer[i]);
    counter++;
  }

  return counter;
}

/**************************************************************************/
/*!
    @brief  Flushes the contents of the FIFo buffer
*/
/**************************************************************************/
void Adafruit_MFRC630::clearFIFO(void)
{
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("Clearing FIFO buffer ");

  uint8_t ctrl = read8(MFRC630_REG_FIFO_CONTROL);
  write8(MFRC630_REG_FIFO_CONTROL, ctrl | (1<<4));
}

/**************************************************************************/
/*!
    @brief  Writes a parameter-less command to the internal state machine
*/
/**************************************************************************/
void Adafruit_MFRC630::writeCommand(byte command)
{
  uint8_t buff[1] = { command };

  DEBUG_TIMESTAMP();
  DEBUG_PRINT("Sending CMD 0x");
  DEBUG_PRINTLN(command, HEX);

  writeBuffer(MFRC630_REG_COMMAND, 1, buff);
}

/**************************************************************************/
/*!
    @brief  Writes a parametered command to the internal state machine
*/
/**************************************************************************/
void Adafruit_MFRC630::writeCommand(byte command, uint8_t paramlen,
  uint8_t *params)
{
  /* Arguments and/or data necessary to process a command, are exchanged via
     the FIF0 buffer:

     - Each command that needs a certain number of arguments will start
       processing only when it has received the correct number of arguments
       via the FIFO buffer.
     - The FIFO buffer is not cleared automatically at command start. It is
       recommended to write the command arguments and/or the data bytes into
       the FIFO buffer and start the command afterwards.
     - Each command may be stopped by the host by writing a new command code
       into the command register e.g.: the Idle-Command. */

  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("Transceiving Command");

  /* Cancel any current command. */
  write8(MFRC630_REG_COMMAND, MFRC630_CMD_IDLE);

  /* Flush the FIFO */
  clearFIFO();

  /* Write data to the FIFO */
  writeFIFO(paramlen, params);

  /* Send the transceive command */
  write8(MFRC630_REG_COMMAND, command);
}

/**************************************************************************/
/*!
    @brief  Gets the three bit COM status for the IC
*/
/**************************************************************************/
uint8_t Adafruit_MFRC630::getComStatus(void)
{
  return (read8(MFRC630_REG_STATUS) & 0b111);
}

/**************************************************************************/
/*!
    @brief  Configures the radio for the specific protocol
*/
/**************************************************************************/
bool Adafruit_MFRC630::configRadio(mfrc630radiocfg cfg)
{
  DEBUG_TIMESTAMP();
  DEBUG_PRINT("Configuring the radio for ");

  switch(cfg)
  {
    case MFRC630_RADIOCFG_ISO1443A_106:
      DEBUG_PRINTLN("ISO1443A-106");
      writeBuffer(MFRC630_REG_DRV_MOD,
          sizeof(antcfg_iso14443a_106), antcfg_iso14443a_106);

      DEBUG_TIMESTAMP();
      DEBUG_PRINTLN("Setting driver mode");
      write8(MFRC630_REG_DRV_MOD, 0x8E);  /* Driver mode register */

      DEBUG_TIMESTAMP();
      DEBUG_PRINTLN("Setting transmitter amplifier (residual carrier %)");
      write8(MFRC630_REG_TX_AMP, 0x12);   /* Transmiter amplifier register */

      DEBUG_TIMESTAMP();
      DEBUG_PRINTLN("Setting driver configuration");
      write8(MFRC630_REG_DRV_CON, 0x39);  /* Driver configuration register */

      DEBUG_TIMESTAMP();
      DEBUG_PRINTLN("Configuring transmitter (overshoot/TX load)");
      write8(MFRC630_REG_TXL, 0x06);      /* Transmitter register */
      break;
    default:
      DEBUG_PRINTLN("[UNKNOWN!]");
      return false;
      break;
  }

  return true;
}

/**************************************************************************/
/*!
    @brief  Waits up to 'timeout' seconds for a tag (0 to wait forever).
*/
/**************************************************************************/
uint16_t Adafruit_MFRC630::waitForTag(float timeout)
{
  uint16_t atqa = 0;

  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("Configuring device to wait for a tag");
  DEBUG_TIMESTAMP();
  DEBUG_PRINT("Timeout = ");
  DEBUG_PRINTLN(timeout);

  /* Cancel any current command */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("1. Sending IDLE (Cancel current command)");
  writeCommand(MFRC630_CMD_IDLE);

  /* Flushg the FIFO */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("2. Flushing the FIFO buffer");
  clearFIFO();

  /* Configure radio to scan for tags */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3. Configuring the radio to listen for ISO14443 tags.");

  /*
   * Define the number of bits from the last byte should be sent. 000 means
   * that all bits of the last data byte are sent, 1..7 causes the specified
   * number of bits to be sent. Also set the DataEn bit to enable data xfer.
   */
  write8(MFRC630_REG_TX_DATA_NUM, 0x07 | (1<<3));

  /* Disable CRC. */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3.a. Disabling CRC checks.");
  write8(MFRC630_REG_TX_CRC_PRESET, 0x18);
  write8(MFRC630_REG_RX_CRC_CON, 0x18);

  /* Clear the receiver control regiter. */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3.b. Clearing the receiver control register.");
  write8(MFRC630_REG_RX_BIT_CTRL, 0);

  /* Clear the interrupts. */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3.c. Clearing and configuring interrupts.");
  write8(MFRC630_REG_IRQ0, 0b01111111);
  write8(MFRC630_REG_IRQ1, 0b00111111);
  /* Allow the receiver and Error IRQs to be propagated to the GlobalIRQ. */
  write8(MFRC630_REG_IRQOEN, (1 << 2) | (1 << 1));
  /* Allow Timer0 IRQ to be propagated to the GlobalIRQ. */
  write8(MFRC630_REG_IRQ1EN, (1 << 0));

  /* Configure the timeout on Timer1. */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3.d. Configuring timeout (211.875kHz, post TX, 5ms timeout).");
  write8(MFRC630_REG_T0_CONTROL, 0b10001);
  write8(MFRC630_REG_T0_RELOAD_HI, 1000 >> 8);
  write8(MFRC630_REG_TO_RELOAD_LO, 0xFF);
  write8(MFRC630_REG_T0_COUNTER_VAL_HI, 1000 >> 8);
  write8(MFRC630_REG_T0_COUNTER_VAL_LO, 0xFF);

  /* Send the ISO14443 REQA command. */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3.e. Sending ISO14443 'REQA' command.");
  uint8_t send_req[] = { ISO14443_CMD_REQA };
  writeCommand(MFRC630_CMD_TRANSCEIVE, 1, send_req);

  /* Wait here until we're done reading, get an error, or timeout. */
  /* TODO: Update to use timeout parameter! */
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3.f. Waiting for a response or timeout.");
  uint8_t irqval = 0;
  while (!(irqval & 1)) {
    irqval = read8(MFRC630_REG_IRQ1);
    /* Check for a global interrrupt, which can only be ERR or RX. */
    if (irqval & (1 << 6)) {
      break;
    }
  }

  /* Cancel the current command (in case we timed out or error occurred). */
  write8(MFRC630_REG_COMMAND, MFRC630_CMD_IDLE);

  /* Check the RX IRQ, and exit appropriately if it has fired (error). */
  irqval = read8(MFRC630_REG_IRQ0);
  if ( (!(irqval & (1<<2))) || (irqval & (1<<1)) ) {
    DEBUG_TIMESTAMP();
    DEBUG_PRINTLN("ERROR: No RX flag set, transceive failed or timed out.");
    return 0;
  }

  /* Read the response */
  uint16_t rxlen = readFIFOLen();
  DEBUG_TIMESTAMP();
  DEBUG_PRINTLN("3.g. Reading response from FIFO buffer.");
  /* If we have 2 bytes, response is likely ATQA. */
  if (rxlen == 2) {  // ATQA should answer with 2 bytes.
    readFIFO(rxlen, (uint8_t*) &atqa);
    DEBUG_TIMESTAMP();
    DEBUG_PRINTLN("Received ATQA answer:");
    DEBUG_TIMESTAMP();
    DEBUG_PRINTLN(atqa);
    return atqa;
  }

  return 0;
}
