# NTAG213 Cards

NTAG21x cards are arranged in a series of **4 byte 'pages'**, similar to the
earlier Mifare Ultralight tags. They have a **7-byte UID** (compared to the 4
byte UID on most Mifare Classic and Mifare Plus cards).

## Memory Layout

NTAG213 tags have the following memory layout (see the NTAG213 IC datasheet for
further details):

> NOTE: Pages **0x4..0x27 (4..39)** are the **user memory** read/write area,
  although pages 4-5 are pre-programmed on most cards as 'data
  pages' for the capability continer.

| Page  | Function                                         |
|-------|--------------------------------------------------|
| 0..1  | Serial number                                    |
| 2     | Serial number [0], Internal [1], Lock bits [2:3] |
| 3     | Capability container                             |
| 4..39 | **USER MEMORY** (although 4-5 pre-programmed!)   |
| 40    | Dynamic lock bits [0:2], RFUI [3]                |
| 41    | CFG0                                             |
| 42    | CFG1                                             |
| 43    | Password                                         |
| 44    | Pack [0:1], RFUI [2:3]                           |

> Larger members of the NTAG21x family extend the size of the user memory.
  See the IC datasheet for exact layouts.


#### UID/Serial Number

- The 7-byte UID and two 'check' bytes are stored in the first 9
  bytes of memory (pages 0..2). These bytes are READ ONLY.

#### Static Lock Bits

- The two STATIC LOCK BITS in page 2 are used as a read-only locking
  mechanism. Each page from 03h (CC) to 0Fh (3..15) can be individually
  locked by setting the corresponding locking bit Lx to logic 1 to
  prevent further write access. After locking, the corresponding page
  becomes read-only memory.

#### Capability Container

- The Capability Container CC is programmed during the IC production
  according to the NFC Forum Type 2 Tag specification. These bytes may
  be bit-wise modified by a WRITE or COMPATIBILITY_WRITE command.
- Byte 2 in the capability container defines the available memory size
  for NDEF messages, as follows:

  | Tag Type | Value | Size (bytes) |
  |----------|-------|--------------|
  | NTAG213  | 0x12  | 144 bytes    |
  | NTAG215  | 0x3E  | 496 bytes    |
  | NTAG216  | 0x6D  | 872 bytes    |

#### User Memory

- User memory can be restricted to using password verification.
- User memory has the following factory default values for **NTAG213**:

  | Page | Values Within Page (bytes 0..3) |
  |------|---------------------------------|
  | 03   | E1 10 12 00                     |
  | 04   | 01 03 A0 0C                     |
  | 05   | 34 03 00 FE                     |

 - By way of contrast, older **NTAG203** tags have the following default values:

    | Page | Values Within Page (bytes 0..3) |
    |------|---------------------------------|
    | 03   | E1 10 12 00                     |
    | 04   | 01 03 A0 **10**                 |
    | 05   | **44** 03 00 FE                 |

#### Dynamic Lock Bits

- To lock the pages of NTAG21x starting at page address 10h (16) and
  onwards, the so called DYNAMIC LOCK BITS are used. The three lock
  bytes cover the memory area of 96 data bytes for NTAG213, 456 data
  bytes for NTAG215 and 840 data bytes for NTAG216. The granularity is 2
  pages for NTAG213 and 16 pages for NTAG215 and NTAG216.

#### Config Pages

- These pages are used to configure the memory access restrictions and
  to configure the UID ASCII mirror feature. See the NTAG IC
  documentation for implementation details.

###### Noteworthy Feature: Counter Function

NTAG21x features a NFC counter function. This function enables NTAG21x to automatically increase the 24 bit counter value, triggered by the first
valid ...

- **READ** command
- **FAST-READ** command

... after the NTAG21x tag is powered by an RF field.

Once the NFC counter has reached the maximum value of FF FF FF hex, the NFC
counter value will not change any more.

The NFC counter is enabled or disabled with the **NFC_CNT_EN** bit (4) in
CFG1. See Section 8.5.7 of the NTAG213 datasheet for full details.

The actual NFC counter value can be read with:

- **READ_CNT** command or
- NFC counter mirror feature

The reading of the NFC counter (by READ_CNT command or with the NFC counter
mirror) can also be protected with the password authentication. The NFC
counter password protection is enabled or disabled with the NFC_CNT_PWD_PROT
bit (see Section 8.5.7).

#### Password + PACK

- The memory write or read/write access to a configurable part of the memory
  can be constrained by a positive password verification. The 32-bit secret
  password (PWD) and the 16-bit password acknowledge (PACK) response are
  typically programmed into the configuration pages at the tag personalization
  stage.
- In the initial state of NTAG21x, password protection is disabled by a AUTH0
  value of FFh. PWD and PACK are freely writable in this state. Access to the
  configuration pages and any part of the user memory can be restricted by
  setting AUTH0 to a page address within the available memory space. This
  page address is the first one protected.
- The 32-bit PWD and the 16-bit PACK need to be programmed into the
  configuration pages, see Section 8.5.7. The password as well as the password
  acknowledge are written LSByte first. This byte order is the same as the
  byte order used during the PWD_AUTH command and its response.
- The PWD and PACK bytes can never be read out of the memory. Instead of
  transmitting the real value on any valid READ or FAST_READ command, only 00h
  bytes are replied.

##### Brute Force Password Protection

To prevent brute-force attacks on the password, the maximum allowed number of
negative password verification attempts can be set using AUTHLIM. This
mechanism is disabled by setting AUTHLIM to a value of 000b, which is also
the initial state of NTAG21x.

If AUTHLIM is not equal to 000b, each negative authentication verification is
internally counted. The count operation features anti-tearing support. As soon
as this internal counter reaches the number specified in AUTHLIM, any further
negative password verification leads to a permanent locking of the protected
part of the memory for the specified access modes. Specifically, whether the
provided password is correct or not, each subsequent PWD_AUTH fails.

Any successful password verification, before reaching the limit of negative
password verification attempts, resets the internal counter to zero.
