/*!
 * @file Adafruit_MFRC630_regs.h
 */
#ifndef __ADAFRUIT_MFRC630_REGS_H__
#define __ADAFRUIT_MFRC630_REGS_H__

/*!
 * @brief MFRC630 command set
 */
enum mfrc630reg {
  MFRC630_REG_COMMAND = 0x00,
  MFRC630_REG_HOST_CTRL = 0x01,
  MFRC630_REG_FIFO_CONTROL = 0x02,
  MFRC630_REG_WATER_LEVEL = 0x03,
  MFRC630_REG_FIFO_LENGTH = 0x04,
  MFRC630_REG_FIFO_DATA = 0x05,
  MFRC630_REG_IRQ0 = 0x06,
  MFRC630_REG_IRQ1 = 0x07,
  MFRC630_REG_IRQOEN = 0x08,
  MFRC630_REG_IRQ1EN = 0x09,
  MFRC630_REG_ERROR = 0x0A,
  MFRC630_REG_STATUS = 0x0B,
  MFRC630_REG_RX_BIT_CTRL = 0x0C,
  MFRC630_REG_RX_COLL = 0x0D,
  MFRC630_REG_T_CONTROL = 0x0E,
  MFRC630_REG_T0_CONTROL = 0x0F,
  MFRC630_REG_T0_RELOAD_HI = 0x10,
  MFRC630_REG_TO_RELOAD_LO = 0x11,
  MFRC630_REG_T0_COUNTER_VAL_HI = 0x12,
  MFRC630_REG_T0_COUNTER_VAL_LO = 0x13,
  MFRC630_REG_T1_CONTROL = 0x14,
  MFRC630_REG_T1_RELOAD_HI = 0x15,
  MFRC630_REG_T1_RELOAD_LO = 0x16,
  MFRC630_REG_T1_COUNTER_VAL_HI = 0x17,
  MFRC630_REG_T1_COUNTER_VAL_LO = 0x18,
  MFRC630_REG_T2_CONTROL = 0x19,
  MFRC630_REG_T2_RELOAD_HI = 0x1A,
  MFRC630_REG_T2_RELOAD_LO = 0x1B,
  MFRC630_REG_T2_COUNTER_VAL_HI = 0x1C,
  MFRC630_REG_T2_COUNTER_VAL_LO = 0x1D,
  MFRC630_REG_T3_CONTROL = 0x1E,
  MFRC630_REG_T3_RELOAD_HI = 0x1F,
  MFRC630_REG_T3_RELOAD_LO = 0x20,
  MFRC630_REG_T3_COUNTER_VAL_HI = 0x21,
  MFRC630_REG_T3_COUNTER_VAL_LO = 0x22,
  MFRC630_REG_T4_CONTROL = 0x23,
  MFRC630_REG_T4_RELOAD_HI = 0x24,
  MFRC630_REG_T4_RELOAD_LO = 0x25,
  MFRC630_REG_T4_COUNTER_VAL_HI = 0x26,
  MFRC630_REG_T4_COUNTER_VAL_LO = 0x27,

  /* 0x28..0x39 = Antenna Configuration */
  MFRC630_REG_DRV_MOD = 0x28,             /**<  (ISO/IEC14443-A 106 = 0x8E) */
  MFRC630_REG_TX_AMP = 0x29,              /**<  (ISO/IEC14443-A 106 = 0x12) */
  MFRC630_REG_DRV_CON = 0x2A,             /**<  (ISO/IEC14443-A 106 = 0x39) */
  MFRC630_REG_TXL = 0x2B,                 /**<  (ISO/IEC14443-A 106 = 0x0A) */
  MFRC630_REG_TX_CRC_PRESET = 0x2C,       /**<  (ISO/IEC14443-A 106 = 0x18) */
  MFRC630_REG_RX_CRC_CON = 0x2D,          /**<  (ISO/IEC14443-A 106 = 0x18) */
  MFRC630_REG_TX_DATA_NUM = 0x2E,         /**<  (ISO/IEC14443-A 106 = 0x0F) */
  MFRC630_REG_TX_MOD_WIDTH = 0x2F,        /**<  (ISO/IEC14443-A 106 = 0x21) */
  MFRC630_REG_TX_SYM_10_BURST_LEN = 0x30, /**<  (ISO/IEC14443-A 106 = 0x00) */
  MFRC630_REG_TX_WAIT_CTRL = 0x31,        /**<  (ISO/IEC14443-A 106 = 0xC0) */
  MFRC630_REG_TX_WAIT_LO = 0x32,          /**<  (ISO/IEC14443-A 106 = 0x12) */
  MFRC630_REG_FRAME_CON = 0x33,           /**<  (ISO/IEC14443-A 106 = 0xCF) */
  MFRC630_REG_RX_SOFD = 0x34,             /**<  (ISO/IEC14443-A 106 = 0x00) */
  MFRC630_REG_RX_CTRL = 0x35,             /**<  (ISO/IEC14443-A 106 = 0x04) */
  MFRC630_REG_RX_WAIT = 0x36,             /**<  (ISO/IEC14443-A 106 = 0x90) */
  MFRC630_REG_RX_THRESHOLD = 0x37,        /**<  (ISO/IEC14443-A 106 = 0x5C) */
  MFRC630_REG_RCV = 0x38,                 /**<  (ISO/IEC14443-A 106 = 0x12) */
  MFRC630_REG_RX_ANA = 0x39,              /**<  (ISO/IEC14443-A 106 = 0x0A) */

  MFRC630_REG_RFU_LPCD = 0x3A,
  MFRC630_REG_SERIAL_SPEED = 0x3B,
  MFRC630_REG_LFO_TRIMM = 0x3C,
  MFRC630_REG_PLL_CTRL = 0x3D,
  MFRC630_REG_PLL_DIVOUT = 0x3E,
  MFRC630_REG_LPCD_QMIN = 0x3F,
  MFRC630_REG_LPCD_QMAX = 0x40,
  MFRC630_REG_LPCD_IMIN = 0x41,
  MFRC630_REG_LPCD_I_RESULT = 0x42,
  MFRC630_REG_LPCD_Q_RESULT = 0x43,
  MFRC630_REG_PADEN = 0x44,
  MFRC630_REG_PADOUT = 0x45,
  MFRC630_REG_PADIN = 0x46,
  MFRC630_REG_SIGOUT = 0x47,
  MFRC630_REG_VERSION = 0x7F
};

/*! See Table 7.10.2: Command Set */
enum mfrc630cmd {
  MFRC630_CMD_IDLE = 0x00, /**< Cancels current command */
  MFRC630_CMD_LPCD = 0x01, /**< Low power card detection */
  MFRC630_CMD_LOADKEY =
      0x02, /**< Reads a 6 byte MIFARE key and puts it into KEY BUFFER */
  MFRC630_CMD_MFAUTHENT = 0x03, /**< Performs Mifare Classic authentication */
  MFRC630_CMD_RECEIVE = 0x05,   /**< Activates the receive circuit */
  MFRC630_CMD_TRANSMIT = 0x06,  /**< Transmits data from the FIFO buffer */
  MFRC630_CMD_TRANSCEIVE =
      0x07, /**< Transmits data from the FIFO buffer and automatically activates
               the receive buffer when finished */
  MFRC630_CMD_WRITEE2 = 0x08, /**< Gets 1 byte from FIFO and writes to EEPROM */
  MFRC630_CMD_WRITEE2PAGE =
      0x09, /**< Gets up to 64 bytes from FIFO and writes to EEPROM */
  MFRC630_CMD_READE2 =
      0x0A, /**< Reads data from EEPROM and copies it into the FIFO buffer */
  MFRC630_CMD_LOADREG =
      0x0C, /**< Reads data from the internal EEPROM and initializes the MFRC630
               registers. EEPROM address needs to be within EEPROM sector 2 */
  MFRC630_CMD_LOADPROTOCOL =
      0x0D, /**< Reads data from the internal EEPROM and initializes the MFRC630
               registers needed for a protocol change. */
  MFRC630_CMD_LOADKEYE2 =
      0x0E, /**< Copies a key from EEPROM into the key buffer */
  MFRC630_CMD_STOREKEYE2 =
      0x0F,                   /**< Stores a MIFARE key (6 bytes) into EEPROM */
  MFRC630_CMD_READRNR = 0x1C, /**< Copies bytes from the random number generator
                                 into the FIFO buffer until the FIFO is full */
  MFRC630_CMD_SOFTRESET = 0x1F /**< SW resets the MFRC630 */
};

/*! ISO14443 Commands (see ISO-14443-3) */
enum iso14443_cmd {
  ISO14443_CMD_REQA = 0x26,    /**< Request command. */
  ISO14443_CMD_WUPA = 0x52,    /**< Wakeup command. */
  ISO14443_CAS_LEVEL_1 = 0x93, /**< Anticollision cascade level 1. */
  ISO14443_CAS_LEVEL_2 = 0x95, /**< Anticollision cascade level 2. */
  ISO14443_CAS_LEVEL_3 = 0x97  /**< Anticollision cascade level 3. */
};

/*! Mifare Commands */
enum mifare_cmd {
  MIFARE_CMD_AUTH_A = 0x60,
  MIFARE_CMD_AUTH_B = 0x61,
  MIFARE_CMD_READ = 0x30,
  MIFARE_CMD_WRITE = 0xA0,
  MIFARE_CMD_TRANSFER = 0xB0,
  MIFARE_CMD_DECREMENT = 0xC0,
  MIFARE_CMD_INCREMENT = 0xC1,
  MIFARE_CMD_STORE = 0xC2,
  MIFARE_ULTRALIGHT_CMD_WRITE = 0xA2
};

/*! NTAG Commands */
enum ntag_cmd {
  NTAG_CMD_READ = 0x30,      /**> NTAG page read. */
  NTAG_CMD_WRITE = 0xA2,     /**< NTAG-specfiic 4 byte write. */
  NTAG_CMD_COMP_WRITE = 0xA0 /**< Mifare Classic 16-byte compat. write. */
};

/*! 'ComState' values for for the MFRC630_REG_STATUS register (0x0B) */
enum mfrc630comstat {
  MFRC630_COMSTAT_IDLE = 0b000,         /**< IDLE */
  MFRC630_COMSTAT_TXWAIT = 0b001,       /**< TX Wait */
  MFRC630_COMSTAT_TRANSMITTING = 0b011, /**< Transmitting */
  MFRC630_COMSTAT_RXWAIT = 0b101,       /**< RX Wait */
  MFRC630_COMSTAT_WAITFORDATA = 0b110,  /**< Waiting for DATA */
  MFRC630_COMSTAT_RECEIVING = 0b111     /**< Receiving */
};

/*! Radio config modes */
enum mfrc630radiocfg {
  MFRC630_RADIOCFG_ISO1443A_106 = 1, /**< ISO1443A 106 Mode */
  MFRC630_LAST
};

/*! MFRC360 errors */
enum mfrc630errors {
  MFRC630_ERROR_EEPROM = (1 << 7),   /**< EEPROM error. */
  MFRC630_ERROR_FIFOWR = (1 << 6),   /**< FIFO write error. */
  MFRC630_ERROR_FIFOOVL = (1 << 5),  /**< FIFO already full! */
  MFRC630_ERROR_MINFRAME = (1 << 4), /**< Not enough data in frame. */
  MFRC630_ERROR_NODATA = (1 << 3),   /**< FIFO empty! */
  MFRC630_ERROR_COLLDET = (1 << 2),  /**< Collision detection, see RxColl. */
  MFRC630_ERROR_PROT = (1 << 1),     /**< Protocol error. */
  MFRC630_ERROR_INTEG = (1 << 0)     /**< Data integrity error. */
};

/*! MFRC630 interrupt requests 0 */
enum mfrc630irq0 {
  MFRC630IRQ0_SET = (1 << 7),        /**< Sets/Clears interrupt. */
  MFRC630IRQ0_HIALERTIRQ = (1 << 6), /**< FIFO has reached top level. */
  MFRC630IRQ0_LOALERTIRQ = (1 << 5), /**< FIFO has reached bottom level. */
  MFRC630IRQ0_IDLEIRQ = (1 << 4),    /**< Command terminated by itself. */
  MFRC630IRQ0_TXIRQ = (1 << 3),      /**< Data transmission complete */
  MFRC630IRQ0_RXIRQ = (1 << 2),      /**< Receiver detected end of stream */
  MFRC630IRQ0_ERRIRQ =
      (1 << 1), /**< FifoWrErr, FiFoOvl, ProtErr, NoDataErr, IntegErr. */
  MFRC630IRQ0_RXSOF = (1 << 0) /**< RX start of frame detected. */
};

/*! MFRC630 interrupt requests 1 */
enum mfrc630irq1 {
  MFRC630IRQ1_SET = (1 << 7),       /**< Sets/Clears interrupt. */
  MFRC630IRQ1_GLOBALIRQ = (1 << 6), /**< Set if an enabled IRQ occured */
  MFRC630IRQ1_LPCDIRQ = (1 << 5),   /**< Card detected in low power mode */
  MFRC630IRQ1_TIMER4IRQ = (1 << 4), /**< Timer 4 underflow */
  MFRC630IRQ1_TIMER3IRQ = (1 << 3), /**< Timer 3 underflow */
  MFRC630IRQ1_TIMER2IRQ = (1 << 2), /**< Timer 2 underflow */
  MFRC630IRQ1_TIMER1IRQ = (1 << 1), /**< Timer 1 underflow */
  MFRC630IRQ1_TIMER0IRQ = (1 << 0), /**< Timer 0 underflow */
};

/*! MFRC630 crypto engine status */
enum mfrc630status {
  MFRC630STATUS_CRYPTO1ON = (1 << 5) /**< Mifare Classic Crypto engine on */
};

#endif
