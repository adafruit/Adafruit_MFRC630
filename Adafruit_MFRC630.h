/*!
 * @file Adafruit_MFRC630.h
 */
#ifndef __ADAFRUIT_MFRC630_H__
#define __ADAFRUIT_MFRC630_H__

#include "Adafruit_MFRC630_consts.h"
#include "Adafruit_MFRC630_regs.h"
#include "Arduino.h"
#include <SPI.h>
#include <Stream.h>
#include <Wire.h>

/*!
 * @brief MFRC630 I2C Address
 */
#define MFRC630_I2C_ADDR (0x28)

/* Debug output level */
/*
 * NOTE: Setting this macro above RELEASE may require more SRAM than small
 *       MCUs like the Atmel 32u4 can provide!
 */
#define MFRC630_VERBOSITY_RELEASE (0) //!< No debug output
#define MFRC630_VERBOSITY_DEBUG (1)   //!< Debug message output
#define MFRC630_VERBOSITY_TRACE (2)   //!< Full packet trace dumps
#define MFRC630_VERBOSITY                                                      \
  (MFRC630_VERBOSITY_RELEASE) //!< Sets verbosity variable

#define MFRC630_ALWAYS_DISP_ERRORS (1) //!< Sets error output

/* Macro for debug output */
#if MFRC630_VERBOSITY >= MFRC630_VERBOSITY_DEBUG
#define DEBUG_PRINT(...) Serial.print(__VA_ARGS__)
#define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__)
#define DEBUG_TIMESTAMP()                                                      \
  Serial.print(F("\tD [+"));                                                   \
  Serial.print(millis());                                                      \
  Serial.print(F("ms] "));
#else
#define DEBUG_PRINT(...)     //!< Disables debug printing
#define DEBUG_PRINTLN(...)   //!< Disables debug println
#define DEBUG_TIMESTAMP(...) //!< Disables debug timestamp
#endif

/* Macro for trace output */
#if MFRC630_VERBOSITY >= MFRC630_VERBOSITY_TRACE
#define TRACE_PRINT(...) Serial.print(__VA_ARGS__)
#define TRACE_PRINTLN(...) Serial.println(__VA_ARGS__)
#define TRACE_TIMESTAMP()                                                      \
  Serial.print(F("\t. [+"));                                                   \
  Serial.print(millis());                                                      \
  Serial.print(F("ms] "));
#else
#define TRACE_PRINT(...)     //!< Disables trace output printing
#define TRACE_PRINTLN(...)   //!< Disables trace output println
#define TRACE_TIMESTAMP(...) //!< Disables trace output timestamp
#endif

/* Macro for error output */
#if MFRC630_ALWAYS_DISP_ERRORS
#define ERROR_PRINT(...) Serial.print(__VA_ARGS__) //!< Enables error printing
#define ERROR_PRINTLN(...)                                                     \
  Serial.println(__VA_ARGS__) //!< Enables error println
#define ERROR_TIMESTAMP()                                                      \
  Serial.print(F("\t! [+"));                                                   \
  Serial.print(millis());                                                      \
  Serial.print(F("ms] ")); //!< Enables error timestamp
#else
#define ERROR_PRINT(...) DEBUG_PRINT(__VA_ARGS__)
#define ERROR_PRINTLN(...) DEBUG_PRINTLN(__VA_ARGS__)
#define ERROR_TIMESTAMP()                                                      \
  DEBUG_PRINT(F("\t! [+"));                                                    \
  DEBUG_PRINT(millis());                                                       \
  DEBUG_PRINT(F("ms] "));
#endif

/*!
 * @brief Different cases used for I2C, SPI, and SERIAL data transfer
 */
enum mfrc630_transport {
  MFRC630_TRANSPORT_I2C = 0,
  MFRC630_TRANSPORT_SPI = 1,
  MFRC630_TRANSPORT_SERIAL = 2
};

/**
 * Driver for the Adafruit MFRC630 RFID front-end.
 */
class Adafruit_MFRC630 {
public:
  /**
   * Default I2C bus constructor
   *
   * @param i2c_addr      The I2C address to use (default value is empty)
   * @param pdown_pin     The power down pin number (required)/
   */
  Adafruit_MFRC630(uint8_t i2c_addr, int8_t pdown_pin = -1);

  /**
   * Custom I2C bus constructor with user-defined I2C bus
   *
   * @param wireBus       The I2C bus to use
   * @param i2c_addr      The I2C address to use (default value is empty)
   * @param pdown_pin     The power down pin number (required)/
   */
  Adafruit_MFRC630(TwoWire *wireBus, uint8_t i2c_addr, int8_t pdown_pin = -1);

  /**
   * HW SPI bus constructor
   *
   * @param transport     The transport to use when communicating with the IC
   * @param cs            The CS/Sel pin for HW SPI access.
   * @param pdown_pin     The power down pin number (required)/
   *
   * @note This instance of the constructor requires the 'transport'
   *       parameter to distinguish is from the default I2C version.
   */
  Adafruit_MFRC630(enum mfrc630_transport transport, int8_t cs,
                   int8_t pdown_pin = -1);

  /**
   * SW serial bus constructor
   *
   * @param serial        The Serial instance to use
   * @param pdown_pin     The power down pin number (required)/
   */
  Adafruit_MFRC630(Stream *serial, int8_t pdown_pin = -1);

  /**
   * Initialises the IC and performs some simple system checks.
   *
   * @return True if init succeeded, otherwise false.
   */
  bool begin(void);

  /* FIFO helpers (see section 7.5) */
  /**
   * Returns the number of bytes current in the FIFO buffer.
   *
   * @return The number of bytes in the FIFO buffer.
   */
  int16_t readFIFOLen(void);

  /**
   * Reads data from the FIFO buffer.
   *
   * @param len       The number of bytes to read
   * @param buffer    The buffer to write data into.
   *
   * @return The actual number of bytes read from the FIFO buffer.
   */
  int16_t readFIFO(uint16_t len, uint8_t *buffer);

  /**
   * Write sdata into the FIFO buffer.
   *
   * @param len       The number of bytes to write.
   * @param buffer    The data to write into the FIFO buffer.
   *
   * @return The actual number of bytes written.
   */
  int16_t writeFIFO(uint16_t len, uint8_t *buffer);

  /**
   * Clears the contents of the FIFO buffer.
   */
  void clearFIFO(void);

  /* Command wrappers */
  /**
   * Sends an unparameterized command to the IC.
   *
   * @param command   The command register to send.
   */
  void writeCommand(byte command);

  /**
   * Sends a parametrized command to the IC.
   *
   * @param command   The command register to send.
   * @param paramlen  The number of parameter bytes.
   * @param params    The paramater values to send.
   */
  void writeCommand(byte command, uint8_t paramlen, uint8_t *params);

  /* Radio config. */
  /**
   * Configures the radio for the specified protocol.
   *
   * @param cfg   The radio config setup to use.
   *
   * @return True if succeeded, otherwise false.
   */
  bool configRadio(mfrc630radiocfg cfg);

  /* General helpers */
  /**
   * Returns the current 'comm status' of the IC's internal state machine.
   *
   * @return The 8-bit state ID.
   */
  uint8_t getComStatus(void);

  /**
   * Performs a soft-reset to put the IC into a known state.
   */
  void softReset(void);

  /* Generic ISO14443a commands (common to any supported card variety). */
  /**
   * Sends the REQA command, requesting an ISO14443A-106 tag.
   *
   * @return The ATQA value if a card was detected.
   */
  uint16_t iso14443aRequest(void);

  /**
   * Sends the WUPA wakeup command.
   *
   * @return The ATQA value if a card was detected.
   */
  uint16_t iso14443aWakeup(void);

  /**
   * Selects a detected ISO14443A card, retrieving the UID and SAK.
   *
   * @param uid   Pointer to the buffer where the uid should be written.
   * @param sak   Pointer to the placeholder for the SAK value.
   *
   * @return True if init succeeded, otherwise false.
   */
  uint8_t iso14443aSelect(uint8_t *uid, uint8_t *sak);

  /* Mifare commands. */
  /**
   * Loads the specified authentication keys on the IC.
   *
   * @param key   Pointer to the buffer containing the key values.
   */
  void mifareLoadKey(uint8_t *key);

  /**
   * Authenticates the selected card using the previously supplied key/
   *
   * @param key_type  Whether to use KEYA or KEYB for authentication.
   * @param blocknum  The block number to authenticate.
   * @param uid       The UID of the card to authenticate.
   *
   * @return True if init succeeded, otherwise false.
   */
  bool mifareAuth(uint8_t key_type, uint8_t blocknum, uint8_t *uid);

  /**
   * Reads the contents of the specified (and previously authenticated)
   * memory block.
   *
   * @param blocknum  The block number to read.
   * @param buf       The buffer the data should be written into.
   *
   * @return The number of bytes read.
   */
  uint16_t mifareReadBlock(uint8_t blocknum, uint8_t *buf);

  /**
   * Writes the supplied data to the previously authenticated
   * memory block.
   *
   * @param blocknum  The block number to read.
   * @param buf       The buffer holding the data to write.
   *
   * @return The number of bytes written.
   */
  uint16_t mifareWriteBlock(uint16_t blocknum, uint8_t *buf);

  /**
   * The default key for fresh Mifare cards.
   */
  uint8_t mifareKeyGlobal[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  /**
   * The default key for NDEF formatted cards.
   */
  uint8_t mifareKeyNDEF[6] = {0xD3, 0xF7, 0xD3, 0xF7, 0xD3, 0xF7};

  /* NTAG commands */
  /**
   * Reads the contents of the specified page.
   *
   * @param pagenum   The page number to read.
   * @param buf       The buffer the data should be written into.
   *
   * @return The number of bytes read.
   */
  uint16_t ntagReadPage(uint16_t pagenum, uint8_t *buf);

  /**
   * Writes the supplied content of the specified page.
   *
   * @param pagenum   The page number to write to.
   * @param buf       The data to write to the card.
   *
   * @return The number of bytes written.
   */
  uint16_t ntagWritePage(uint16_t pagenum, uint8_t *buf);

private:
  int8_t _pdown;
  uint8_t _i2c_addr;
  TwoWire *_wire;
  Stream *_serial;
  int8_t _cs;
  enum mfrc630_transport _transport;

  void write8(byte reg, byte value);
  void writeBuffer(byte reg, uint16_t len, uint8_t *buffer);
  byte read8(byte reg);

  void printHex(uint8_t *buf, size_t len);
  void printError(enum mfrc630errors err);

  uint16_t iso14443aCommand(enum iso14443_cmd cmd);
};

#endif
