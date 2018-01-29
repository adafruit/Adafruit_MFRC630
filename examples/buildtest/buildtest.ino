#include <Wire.h>
#include <Adafruit_MFRC630.h>

#define PDOWN_PIN     (27)

/* Use the default I2C address */
Adafruit_MFRC630 rfid = Adafruit_MFRC630(PDOWN_PIN);

void fifo_test(void)
{
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

void setup() {
  Serial.begin(115200);
  Serial.println(F("Adafruit MFRC630 RFID HW Test"));

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  /* Try to initialize the IC */
  if (!(rfid.begin())) {
    Serial.println("Unable to initialize the MFRC630. Check wiring?");
    while(1) {
      digitalToggle(LED_BUILTIN);
      delay(50);
    }
  }

  /* Do a random number FIFO test */
  fifo_test();
}

void loop() {
  for (int i = 0; i < 2; i++)
  {
    digitalToggle(LED_BLUE);
    delay(1000);
  }
}
