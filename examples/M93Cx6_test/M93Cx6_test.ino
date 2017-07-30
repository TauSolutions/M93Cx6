#include <M93Cx6.h>

/******************************************************************************
 **  
 **  M93Cx6 Test Program
 **  
 **  Pin-Out:
 **                       _____
 **  Chip Select (cs)  --|1   8|--  (pwr) Vcc
 ** Serial Clock (sk)  --|2   7|--  
 **      Data In (di)  --|3   6|--  (org) Organization Select
 **     Data Out (do)  --|4   5|--  (gnd) Vss/Ground
 **                       -----
 **
 **  Arduino Connection:
 **    Vcc          - +5v (or Pin 9 as an option)
 **    Vss          - GND
 **    Chip Select  - Pin 10
 **    Serial Clock - Pin 13
 **    Data In      - Pin 11
 **    Data Out     - Pin 12
 **    Org Select   - Pin 8
 **
 *****************************************************************************/


#define PWR_PIN   7
#define CS_PIN    10
#define SK_PIN    13
#define DO_PIN    12
#define DI_PIN    11
#define ORG_PIN   8
#define ORG       16
#define CHIP      56

M93Cx6 eeprom = M93Cx6(PWR_PIN, CS_PIN, SK_PIN, DO_PIN, DI_PIN, ORG_PIN);

void setup() {
  int i = 0;
  char r;
  char hello[12] = "Hello World!";
  Serial.begin(9600);

  eeprom.setChip(56);    // set chip 93C56
  eeprom.setOrg(ORG_8);  // 8-bit data organization

//  write string to eeprom
  eeprom.writeEnable();
  for (i = 0; i < 12; i++) {
    eeprom.write(i, hello[i]);
  }
  eeprom.writeDisable();

//  read string from eeprom
  for (i = 0; i < 12; i++) {
    r = eeprom.read(i);
    Serial.print(r);
  }

//  clear eeprom
  eeprom.writeEnable();
  eeprom.eraseAll();
  eeprom.writeDisable();
}

void loop() {
  // put your main code here, to run repeatedly:

}