#include <Wire.h>
#include <Adafruit_MFRC630.h>

/* Use the default I2C address */
Adafruit_MFRC630 rfid = Adafruit_MFRC630(27);

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
}

void loop() {
  for (int i = 0; i < 2; i++)
  {
    digitalToggle(LED_BLUE);
    delay(1000);
  }
}
