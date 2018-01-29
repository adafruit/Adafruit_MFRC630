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
#ifndef __ADAFRUIT_MFRC630_REGS_H__
#define __ADAFRUIT_MFRC630_REGS_H__

enum mfrc630reg
{
  MFRC630_REG_COMMAND                 = 0x00,
  MFRC630_REG_HOST_CTRL               = 0x01,
  MFRC630_REG_FIFO_CONTROL            = 0x02,
  MFRC630_REG_WATER_LEVEL             = 0x03,
  MFRC630_REG_FIFO_LENGTH             = 0x04,
  MFRC630_REG_FIFO_DATA               = 0x05,
  MFRC630_REG_IRQ0                    = 0x06,
  MFRC630_REG_IRQ1                    = 0x07,
  MFRC630_REG_IRQOEN                  = 0x08,
  MFRC630_REG_IRQ1EN                  = 0x09,
  MFRC630_REG_ERROR                   = 0x0A,
  MFRC630_REG_STATUS                  = 0x0B,
  MFRC630_REG_RX_BIT_CTRL             = 0x0C,
  MFRC630_REG_RX_COLL                 = 0x0D,
  MFRC630_REG_T_CONTROL               = 0x0E,
  MFRC630_REG_T0_CONTROL              = 0x0F,
  MFRC630_REG_T0_RELOAD_HI            = 0x10,
  MFRC630_REG_TO_RELOAD_LO            = 0x11,
  MFRC630_REG_T0_COUNTER_VAL_HI       = 0x12,
  MFRC630_REG_T0_COUNTER_VAL_LO       = 0x13,
  MFRC630_REG_T1_CONTROL              = 0x14,
  MFRC630_REG_T1_RELOAD_HI            = 0x15,
  MFRC630_REG_T1_RELOAD_LO            = 0x16,
  MFRC630_REG_T1_COUNTER_VAL_HI       = 0x17,
  MFRC630_REG_T1_COUNTER_VAL_LO       = 0x18,
  MFRC630_REG_T2_CONTROL              = 0x19,
  MFRC630_REG_T2_RELOAD_HI            = 0x1A,
  MFRC630_REG_T2_RELOAD_LO            = 0x1B,
  MFRC630_REG_T2_COUNTER_VAL_HI       = 0x1C,
  MFRC630_REG_T2_COUNTER_VAL_LO       = 0x1D,
  MFRC630_REG_T3_CONTROL              = 0x1E,
  MFRC630_REG_T3_RELOAD_HI            = 0x1F,
  MFRC630_REG_T3_RELOAD_LO            = 0x20,
  MFRC630_REG_T3_COUNTER_VAL_HI       = 0x21,
  MFRC630_REG_T3_COUNTER_VAL_LO       = 0x22,
  MFRC630_REG_T4_CONTROL              = 0x23,
  MFRC630_REG_T4_RELOAD_HI            = 0x24,
  MFRC630_REG_T4_RELOAD_LO            = 0x25,
  MFRC630_REG_T4_COUNTER_VAL_HI       = 0x26,
  MFRC630_REG_T4_COUNTER_VAL_LO       = 0x27,
  MFRC630_REG_DRV_MOD                 = 0x28,
  MFRC630_REG_TX_AMP                  = 0x29,
  MFRC630_REG_DRV_CON                 = 0x2A,
  MFRC630_REG_TXL                     = 0x2B,
  MFRC630_REG_TX_CRC_PRESET           = 0x2C,
  MFRC630_REG_RX_CRC_PRESET           = 0x2D,
  MFRC630_REG_TX_DATA_NUM             = 0x2E,
  MFRC630_REG_TX_MOD_WIDTH            = 0x2F,
  MFRC630_REG_TX_SYM_10_BURST_LEN     = 0x30,
  MFRC630_REG_TX_WAIT_CTRL            = 0x31,
  MFRC630_REG_TX_WAIT_LO              = 0x32,
  MFRC630_REG_FRAME_CON               = 0x33,
  MFRC630_REG_RX_SOFD                 = 0x34,
  MFRC630_REG_RX_CTRL                 = 0x35,
  MFRC630_REG_RX_WAIT                 = 0x36,
  MFRC630_REG_RX_THRESHOLD            = 0x37,
  MFRC630_REG_RCV                     = 0x38,
  MFRC630_REG_RX_ANA                  = 0x39,
  MFRC630_REG_RFU_LPCD                = 0x3A,
  MFRC630_REG_SERIAL_SPEED            = 0x3B,
  MFRC630_REG_LFO_TRIMM               = 0x3C,
  MFRC630_REG_PLL_CTRL                = 0x3D,
  MFRC630_REG_PLL_DIVOUT              = 0x3E,
  MFRC630_REG_LPCD_QMIN               = 0x3F,
  MFRC630_REG_LPCD_QMAX               = 0x40,
  MFRC630_REG_LPCD_IMIN               = 0x41,
  MFRC630_REG_LPCD_I_RESULT           = 0x42,
  MFRC630_REG_LPCD_Q_RESULT           = 0x43,
  MFRC630_REG_PADEN                   = 0x44,
  MFRC630_REG_PADOUT                  = 0x45,
  MFRC630_REG_PADIN                   = 0x46,
  MFRC630_REG_SIGOUT                  = 0x47,
  MFRC630_REG_VERSION                 = 0x7F
};

/* See Table 7.10.2: Command Set */
enum mfrc630cmd
{
  MFRC630_CMD_IDLE                    = 0x00, /**< Cancels current command */
  MFRC630_CMD_LPCD                    = 0x01, /**< Low power card detection */
  MFRC630_CMD_LOADKEY                 = 0x02, /**< Reads a 6 byte MIFARE key and puts it into KEY BUFFER */
  MFRC630_CMD_MFAUTHENT               = 0x03, /**< Performs Mifare Classic authentication */
  MFRC630_CMD_RECEIVE                 = 0x05, /**< Activates the receive circuit */
  MFRC630_CMD_TRANSMIT                = 0x06, /**< Transmits data from the FIFO buffer */
  MFRC630_CMD_TRANSCEIVE              = 0x07, /**< Transmits data from the FIFO buffer and automatically activates the receive buffer when finished */
  MFRC630_CMD_WRITEE2                 = 0x08, /**< Gets 1 byte from FIFO and writes to EEPROM */
  MFRC630_CMD_WRITEE2PAGE             = 0x09, /**< Gets up to 64 bytes from FIFO and writes to EEPROM */
  MFRC630_CMD_READE2                  = 0x0A, /**< Reads data from EEPROM and copies it into the FIFO buffer */
  MFRC630_CMD_LOADREG                 = 0x0C, /**< Reads data from the internal EEPROM and initializes the MFRC630 registers. EEPROM address needs to be within EEPROM sector 2 */
  MFRC630_CMD_LOADPROTOCOL            = 0x0D, /**< Reads data from the internal EEPROM and initializes the MFRC630 registers needed for a protocol change. */
  MFRC630_CMD_LOADKEYE2               = 0x0E, /**< Copies a key from EEPROM into the key buffer */
  MFRC630_CMD_STOREKEYE2              = 0x0F, /**< Stores a MIFARE key (6 bytes) into EEPROM */
  MFRC630_CMD_READRNR                 = 0x1C, /**< Copies bytes from the random number generator into the FIFO buffer until the FIFO is full */
  MFRC630_CMD_SOFTRESET               = 0x1F  /**< SW resets the MFRC630 */
};

#endif
