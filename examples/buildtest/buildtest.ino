#include <Wire.h>
#include <Adafruit_MFRC630.h>

/* Indicate the pin number where PDOWN is connected. */
#if defined(ESP8266)
#define PDOWN_PIN         (A0)
#else
#define PDOWN_PIN         (A2)
#endif

/* Show me some mojic! */
#define MOJIC_TRICK       (0)

/* Use the default I2C address */
Adafruit_MFRC630 rfid = Adafruit_MFRC630(MFRC630_I2C_ADDR, PDOWN_PIN);

/* Prints out len bytes of hex data in table format. */
static void print_buf_hex(uint8_t *buf, size_t len)
{
  for (uint8_t i = 0; i < len; i++)
  {
    Serial.print("0x");
    if (buf[i] < 16)
    {
      Serial.print("0");
    }
    Serial.print(buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println(" ");
}

/* This functions sends a command to fill the FIFO with random numbers and */
/* then reads the entire FIFO contents in 16 byte chunks */
void fifo_read_test(void)
{
  Serial.println("Reading randomly generated numbers from FIFO buffer");

  /* Generate random numbers into the FIFO */
  rfid.writeCommand(MFRC630_CMD_READRNR);
  /* Note, this command requires a 10ms delay to fill the buffer! */
  delay(10);

  /* Dump the FIFO 16 bytes at a time to stay within 32 byte I2C limit */
  uint8_t buff[16];
  int16_t len = rfid.readFIFOLen();
  while (len)
  {
    memset(buff, 0, sizeof(buff));
    int16_t readlen = rfid.readFIFO(len > 16 ? 16 : len, buff);
    len -= readlen;
    /* Display the buffer in 16 byte chunks. */
    print_buf_hex(buff, readlen);
  }
}

/* This function writes data to the FIFO and then tries to read it back */
void fifo_write_test(void)
{
  uint8_t buff[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

  /* Write data into the FIFO buffer */
  Serial.println("Writing 16 bytes into FIFO buffer");
  int16_t writelen = rfid.writeFIFO(sizeof(buff), buff);
  (void)writelen;

  /* Read data back and display it*/
  memset(buff, 0, sizeof(buff));
  int16_t readlen = rfid.readFIFO(sizeof(buff), buff);
  print_buf_hex(buff, readlen);
}

/* This function clears the FIFO contents */
void fifo_clear_test(void)
{
  uint8_t buff[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

  /* Write data into the FIFO buffer */
  Serial.println("Writing 16 bytes into FIFO buffer");
  int16_t writelen = rfid.writeFIFO(sizeof(buff), buff);
  (void)writelen;
  int16_t len = rfid.readFIFOLen();
  Serial.print("FIFO len = "),
  Serial.println(len);

  /* Clear the FIFO */
  Serial.println("Clearing FIFO");
  rfid.clearFIFO();
  len = rfid.readFIFOLen();
  Serial.print("FIFO len = "),
  Serial.println(len);
}

/* This function displays the status of the MFRC's state machine */
void status_test(void)
{
  Serial.println("Reading COM Status");
  uint8_t stat = rfid.getComStatus();

  switch (stat)
  {
    case MFRC630_COMSTAT_IDLE:
      Serial.println("IDLE");
      break;
    case MFRC630_COMSTAT_TXWAIT:
      Serial.println("TX WAIT");
      break;
    case MFRC630_COMSTAT_TRANSMITTING:
      Serial.println("TRANSMITTING");
      break;
    case MFRC630_COMSTAT_RXWAIT:
      Serial.println("RX WAIT");
      break;
    case MFRC630_COMSTAT_WAITFORDATA :
      Serial.println("WAITING FOR DATA");
      break;
    case MFRC630_COMSTAT_RECEIVING:
      Serial.println("RECEIVING");
      break;
    default:
      Serial.println("UKNOWN!");
      break;
  }
}

void radio_mifare_dump_sector(uint8_t sector_num)
{
  uint8_t readbuf[16] = { 0 };
  /* Try to read four blocks inside the sector. */
  for (uint8_t b = 0; b < 4 ; b++) {
    uint8_t len = 0;
    len = rfid.mifareReadBlock(sector_num * 4 + b, readbuf);
    if (len == 0) {
      /* No data returned! */
      Serial.print("What!?! No data returned for block ");
      Serial.print(sector_num * 4 + b);
      Serial.println("!");
      #if MOJIC_TRICK
      Serial.println("(ノ ゜Д゜)ノ ︵ ┻━┻");
      #endif
      return;
    } else {
      /* Display the block contents. */
      Serial.print(sector_num * 4 + b); Serial.print(": ");
      print_buf_hex(readbuf, len);
    }
  }
}

/* Read the tag contents (assumes scan has been successfully called!). */
void radio_mifare_read(uint8_t *uid, uint8_t uidlen)
{
  if (uidlen != 4) {
    Serial.println("Not a Mifare tag!");
    #if MOJIC_TRICK
    Serial.println("(ノ ゜Д゜)ノ ︵ ┻━┻");
    #endif
    return;
  }

  /* Use the default key for fresh Mifare cards. */
  // uint8_t keyb[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

  /* Set the key. */
  rfid.mifareLoadKey(rfid.mifareKeyGlobal);

  /* Try to authenticate sectors 0..15 (all Mifare cards should have these!). */
  for (uint8_t s = 0; s < 16; s++) {
    Serial.print("Trying to authenticate sector "); Serial.print(s);
    Serial.println(" with KEYA.");

    /* Authenticate. */
    if(rfid.mifareAuth(MIFARE_CMD_AUTH_A, s*4, uid)) {
        #if MOJIC_TRICK
        Serial.println(" ᕙ(`▽´)ᕗ");
        #endif
        /* Dump the first sector. */
        radio_mifare_dump_sector(s);
    } else {
        Serial.print("AUTH_A failed with ");
        for (uint8_t k = 0; k < 6; k++){
          Serial.print("0x");
          if (HEX < 0x10) {
            Serial.print("0");
          }
          Serial.print(rfid.mifareKeyGlobal[k], HEX);
          Serial.print(" ");
        }
        Serial.println("");
        #if MOJIC_TRICK
        Serial.println("(ノ ゜Д゜)ノ ︵ ┻━┻");
        #endif
    }
  }
}

/* Configure the radio for ISO14443A-106 type tags and scan for the UID. */
void radio_iso1443A_106_scan()
{
  Serial.println("Configuring radio for ISO14443A-106 tags");
  rfid.configRadio(MFRC630_RADIOCFG_ISO1443A_106);

  /* Request a tag */
  Serial.println("Checking for ISO14443A-106 tags");
  #if MOJIC_TRICK
  Serial.println("┬─┬ ノ( ゜-゜ノ)");
  #endif
  uint16_t atqa = rfid.iso14443aRequest();

  /* Select the tag if we found something */
  if (atqa)
  {
    uint8_t uid[10] = { 0 };
    uint8_t uidlen;
    uint8_t sak;

    Serial.print("Found ISO14443A-106 tag with ATQA 0x");
    Serial.println(atqa, HEX);
    #if MOJIC_TRICK
    Serial.println("ᕙ(`▽´)ᕗ");
    #endif

    Serial.println("Selecting the tag");
    #if MOJIC_TRICK
    Serial.println("(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧");
    #endif
    uidlen = rfid.iso14443aSelect(uid, &sak);
    if (uidlen) {
      Serial.print("Got a UID! --> ");
      for (uint8_t i=0; i<uidlen; i++) {
        Serial.print(uid[i], HEX);
        Serial.print(" ");
      }
      Serial.println("");
      #if MOJIC_TRICK
      Serial.println("ᕙ(`▽´)ᕗ");
      #endif
      /* Try to read and dump the card's contents. */
      radio_mifare_read(uid, uidlen);
    } else {
      Serial.println("What, no UID found! Did someone steal my tag!!");
      #if MOJIC_TRICK
      Serial.println("(ノ ゜Д゜)ノ ︵ ┻━┻");
      #endif
    }
  }
  else
  {
    Serial.println("No ISO14443A-106 tag found!");
    #if MOJIC_TRICK
    Serial.println("(ノ ゜Д゜)ノ ︵ ┻━┻");
    #endif
  }
}

bool radio_ntag156b_write(void)
{
    bool rc;

    /* Put the IC in a known-state. */
    rfid.softReset();

    /* Configure the radio for ISO14443A-106. */
    rfid.configRadio(MFRC630_RADIOCFG_ISO1443A_106);

    /* Request a tag (activates the near field, etc.). */
    uint16_t atqa = rfid.iso14443aRequest();

    /* Looks like we found a tag, move on to selection. */
    if (atqa)
    {
        /* NTAG has a ATQA of 00 44 (Ultralight does as well!). */
        if (atqa == 0x44) {
            uint8_t uid[10] = { 0 };
            uint8_t uidlen;
            uint8_t sak;

            /* Retrieve the UID and SAK values. */
            uidlen = rfid.iso14443aSelect(uid, &sak);
            Serial.print("Found a tag with UUID ");
            for (uint8_t i = 0; i < uidlen; i++) {
                Serial.print(uid[i], HEX);
                Serial.print(" ");
            }
            Serial.println("");
            if (uidlen == 7) {
                /* Write something distinct to page 7. */
                Serial.println("Writing data to page 7.");
                uint8_t pagebuf[4] = { 0x12, 0x34, 0x56, 0x78 };
                uint8_t len = rfid.ntagWritePage(7, pagebuf);
                /* Make sure we successfully wrote 4 bytes! */
                rc = len == 4 ? true : false;
            } else {
                /* Should be 7, not sure what kind of tag we have. */
                Serial.print("Unexpected UID length: "); Serial.println(uidlen);
                rc = false;
            }
        } else {
            /* Found a tag, but it isn't NTAG */
            Serial.print("Unexpected ATQA value: "); Serial.println(atqa, HEX);
            rc = false;
        }
    } else {
        /* No tag found! */
        rc = false;
    }

    return rc;
}

/*
 * This more concise loop show the minimim requirements to dump the first 39
 * 4 byte blocks of memory from an NTAG2xx card. No meaningful error-handling
 * or debug output is present here, so this code is intended as a simple
 * starting point for further work.
 */
bool radio_ntag156b_dump_minimal(void)
{
    bool rc;

    /* Put the IC in a known-state. */
    rfid.softReset();

    /* Configure the radio for ISO14443A-106. */
    rfid.configRadio(MFRC630_RADIOCFG_ISO1443A_106);

    /* Request a tag (activates the near field, etc.). */
    uint16_t atqa = rfid.iso14443aRequest();

    /* Looks like we found a tag, move on to selection. */
    if (atqa)
    {
        /* NTAG has a ATQA of 00 44 (Ultralight does as well!). */
        if (atqa == 0x44) {
            uint8_t uid[10] = { 0 };
            uint8_t uidlen;
            uint8_t sak;

            /* Retrieve the UID and SAK values. */
            uidlen = rfid.iso14443aSelect(uid, &sak);
            Serial.print("Found a tag with UUID ");
            for (uint8_t i = 0; i < uidlen; i++) {
                Serial.print(uid[i], HEX);
                Serial.print(" ");
            }
            Serial.println("");
            if (uidlen == 7) {
                /* Try to read the first 42 pages from the card. */
                for (uint8_t i = 0; i < 42; i++) {
                    /* We should be able to read the page contents now. */
                    uint8_t pagebuf[4] = { 0, 0, 0, 0 };
                    uint8_t len = rfid.ntagReadPage(i, pagebuf);
                    Serial.print(i);
                    Serial.print(": ");
                    print_buf_hex(pagebuf, len);
                }
                rc = true;
            } else {
                /* Should be 7, not sure what kind of tag we have. */
                Serial.print("Unexpected UID length: "); Serial.println(uidlen);
                rc = false;
            }
        } else {
            /* Found a tag, but it isn't NTAG */
            Serial.print("Unexpected ATQA value: "); Serial.println(atqa, HEX);
            rc = false;
        }
    } else {
        /* No tag found! */
        rc = false;
    }

    return rc;
}

/*
 * This more concise loop show the minimim requirements to dump the first 1K
 * of memory from a Mifare 1K or Mifare Plus compatible card. No meaningful
 * error-handling or debug output is present here, so this code is intended
 * as a simple starting point for further work.
 */
bool radio_mifare1K_dump_minimal(void)
{
    bool rc;

    /* Put the IC in a known-state. */
    rfid.softReset();

    /* Configure the radio for ISO14443A-106. */
    rfid.configRadio(MFRC630_RADIOCFG_ISO1443A_106);

    /* Request a tag (activates the near field, etc.). */
    uint16_t atqa = rfid.iso14443aRequest();

    /* Looks like we found a tag, move on to selection. */
    if (atqa)
    {
        uint8_t uid[10] = { 0 };
        uint8_t uidlen;
        uint8_t sak;

        /* Retrieve the UID and SAK values. */
        uidlen = rfid.iso14443aSelect(uid, &sak);
        Serial.print("Found a tag with UUID ");
        for (uint8_t i = 0; i < uidlen; i++) {
            Serial.print(uid[i], HEX);
            Serial.print(" ");
        }
        Serial.println("");
        if (uidlen == 4) {
            /* Assume Mifare Classic/Plus and set the global/default key. */
            rfid.mifareLoadKey(rfid.mifareKeyGlobal);
            /* Try to authenticate sectors 0..15. */
            for (uint8_t s = 0; s < 16; s++) {
                /* Try to authenticate this sector. */
                Serial.print("Sector "); Serial.println(s);
                if(rfid.mifareAuth(MIFARE_CMD_AUTH_A, s*4, uid)) {
                    /* We should be able to read the sector contents now. */
                    radio_mifare_dump_sector(s);
                } else {
                    Serial.print("AUTH_A failed for sector ");
                    Serial.println(s);
                }
            }
            rc = true;
        } else {
            Serial.print("Unexpected UID length: "); Serial.println(uidlen);
            rc = false;
        }
    } else {
        rc = false;     /* No tag found, return false. */
    }

    return rc;
}

/**
 *
 */
void setup() {
  Serial.begin(115200);

  while (!Serial) {
    delay(1);
  }

  Serial.println("");
  Serial.println("-----------------------------");
  Serial.println("Adafruit MFRC630 RFID HW Test");
  Serial.println("-----------------------------");

  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(PIN_LED2, OUTPUT);

  /* Try to initialize the IC */
  if (!(rfid.begin())) {
    Serial.println("Unable to initialize the MFRC630. Check wiring?");
    while(1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }
  }

  /* FIFO tests */
  // fifo_read_test();
  // fifo_write_test();
  // fifo_clear_test();

  /* General HW tests */
  // status_test();

  /* Radio tests */
  // radio_iso1443A_106_scan();

  if(!radio_ntag156b_write()) {
    Serial.println("Failed writing data to block 7!");
  }

  /*
   * This will be INCREDIBLY chatty on the I2C bus, but can be used as a
   * quick test to wait until a card enters the near field.
   */
  Serial.println("Waiting for an ISO14443-A compatible card ...");
  //while (!radio_mifare1K_dump_minimal())
  while (!radio_ntag156b_dump_minimal())
  {
    delay(50);
  }
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
