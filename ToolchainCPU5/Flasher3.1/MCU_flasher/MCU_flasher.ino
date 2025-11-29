#include "MX25L.h"
#include "transfert.h"

void setup() {
  pinMode(CSn, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(SI, OUTPUT);
  pinMode(SO, INPUT);
  
  digitalWrite(CSn, HIGH);    // Disable the flash
  Serial.begin(115200);
  EEPROMsetup();
  while (!Serial) { ; }  // Wait for Serial
}

void loop() {
  execCmd();
}

