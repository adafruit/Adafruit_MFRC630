# MFRC630 EEPROM Memory

## Memory Layout

EEPROM memory has **8kB** total memory, divided into **64 byte pages** which
can be programmed in 64 byte chunks. The memory has the following layout:

| Section | Page(s) | Address    | RW | Content                                |
|---------|---------|------------|----|----------------------------------------|
| 0       | 0       | 0..31      | R  | Product information and configuration. |
|         |         | 32..63     | RW | Product configuration.                 |
| 1       | 1..2    | 64..191    | RW | Register reset                         |
| 2       | 3..95   | 192..6143  | RW | **User/free**                          |
| 3       | 96..111 | 6144..7167 | W  | MIFARE classic key                     |
| 4       | 112..128| 7168..8191 | R  | Register set protocol (RSP)            |

* At startup EEPROM sections 1 and 2 are copied to the internal registers.
* The device's behaviour can be changed using the `LoadProtocol` command to
  update the protocol bytes with a new device configuration.

### Key EEPROM Values

Consult the datashet for a full list of EEPROM config values, but key entries
are detailed below.

#### Production Area (Page 0)

| Address   | Contents                                      |
|-----------|-----------------------------------------------|
| 0X01      | Product ID (MFRC630=0xC0)                     |
| 0x03      | EEPROM initialisation data version            |
| 0x04:0x0E | Unique 11 byte numeric code for this device.  |

#### Configuration Area (Page 0)

| Address   | Contents                                         |
|-----------|--------------------------------------------------|
| 0x21      | Interface (0b00 = RS232, 0b01 = I2C, 0b10 = SPI) |
