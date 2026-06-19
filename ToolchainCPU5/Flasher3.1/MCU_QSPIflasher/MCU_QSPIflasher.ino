#include "MX25L.h"
#include "transfert.h"

uint8_t data[1024];
void setup() {
  pinMode(CSn, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(SIO0, OUTPUT);
  pinMode(SIO1, OUTPUT);
  pinMode(SIO2, OUTPUT);
  pinMode(SIO3, OUTPUT);
  digitalWrite(CSn, HIGH);    // Disable the flash
  
  Serial.begin(115200);

  EEPROMsetup();
  while (!Serial) { ; }  // Wait for Serial
  EEPROMread(0x1000, data, 1024);
  printHexData(data, 1024, 0x1000);
  EEPROMread(0x1B00, data, 1024);
  printHexData(data, 1024, 0x1B00);
  EEPROMread(0x1FFF, data, 1024);
  printHexData(data, 1024, 0x1FFF);
}

void loop() {
  //execCmd();
}

