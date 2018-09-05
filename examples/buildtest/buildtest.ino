#include <Wire.h>
#include <Adafruit_MFRC630.h>

#define PDOWN_PIN     (27)

/* Use the default I2C address */
Adafruit_MFRC630 rfid = Adafruit_MFRC630(PDOWN_PIN);

/* This functions sends a command to fill the FIFO with random numbers and then */
/* reads the entire FIFO contents in 16 byte chunks */
void fifo_read_test(void)
{
  Serial.println("Reading randomly generated numbers from FIFO buffer");

  /* Generate random numbers into the FIFO */
  rfid.writeCommand(MFRC630_CMD_READRNR);

  /* Dump the FIFO 16 bytes at a time to stay within 32 byte I2C transaction limit */
  uint8_t buff[16];
  int16_t len = rfid.readFIFOLen();
  while (len)
  {
    memset(buff, 0, sizeof(buff));
    int16_t readlen = rfid.readFIFO(len > 16 ? 16 : len, buff);
    len -= readlen;
    /* Print the data in 16 byte chunks */
    for (uint8_t i = 0; i < readlen; i++)
    {
      Serial.print("0x");
      if (buff[i] < 16)
      {
        Serial.print("0");
      }
      Serial.print(buff[i], HEX);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
}

/* This function writes data to the FIFO and then tries to read it back */
void fifo_write_test(void)
{
  uint8_t buff[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

  /* Write data into the FIFO buffer */
  Serial.println("Writing 16 bytes into FIFO buffer");
  int16_t writelen = rfid.writeFIFO(sizeof(buff), buff);

  /* Read data back and display it*/
  memset(buff, 0, sizeof(buff));
  int16_t readlen = rfid.readFIFO(sizeof(buff), buff);
  for (uint8_t i = 0; i < readlen; i++)
  {
    Serial.print("0x");
    if (buff[i] < 16)
    {
      Serial.print("0");
    }
    Serial.print(buff[i], HEX);
    Serial.print(" ");
  }
  Serial.println(" ");
}

/* This function clears the FIFO contents */
void fifo_clear_test(void)
{
  uint8_t buff[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

  /* Write data into the FIFO buffer */
  Serial.println("Writing 16 bytes into FIFO buffer");
  int16_t writelen = rfid.writeFIFO(sizeof(buff), buff);
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

/* Configure the radio for ISO14443A-106 type tags */
void radio_cfg_iso1443A_106()
{
  Serial.println("Configuring radio for ISO14443A-106 tags");
  rfid.configRadio(MFRC630_RADIOCFG_ISO1443A_106);

  /* Request a tag */
  uint16_t atqa = rfid.iso14443aRequest();
}

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("-----------------------------");
  Serial.println("Adafruit MFRC630 RFID HW Test");
  Serial.println("-----------------------------");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  /* Try to initialize the IC */
  if (!(rfid.begin())) {
    Serial.println("Unable to initialize the MFRC630. Check wiring?");
    while(1) {
      digitalToggle(LED_BUILTIN);
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
  radio_cfg_iso1443A_106();
}

void loop() {
  for (int i = 0; i < 2; i++)
  {
    digitalToggle(PIN_LED2);
    delay(1000);
  }
}
