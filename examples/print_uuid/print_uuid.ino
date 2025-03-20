#include <Wire.h>
#include <Adafruit_MFRC630.h>

/* Indicate the pin number where PDOWN is connected. */
#define PDOWN_PIN         (12)

/* Use the default I2C address */
Adafruit_MFRC630 rfid = Adafruit_MFRC630(PDOWN_PIN);

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
/*
 * This more concise loop show the minimim requirements to dump the first 1K
 * of memory from a Mifare Classic or Mifare Plus compatible card. No meaningful
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
    }
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
  Serial.println("-------------------------------");
  Serial.println("Adafruit MFRC630 Mifare 1K Test");
  Serial.println("-------------------------------");

  pinMode(LED_BUILTIN, OUTPUT);

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
}

void loop() {
  radio_mifare1K_dump_minimal();
}
