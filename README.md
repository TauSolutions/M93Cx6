# M93Cx6

Arduino Library for the Microchip 93Cx6 Family

## Pin-Out
```
                      _____
 Chip Select (cs)  --|1   8|--  (pwr) Vcc
Serial Clock (sk)  --|2   7|--  
     Data In (di)  --|3   6|--  (org) Organization Select
    Data Out (do)  --|4   5|--  (gnd) Vss/Ground
                      -----
```

## Arduino Connection:
```
Vcc          - +5v (or Pin 9 as an option)
Vss          - GND
Chip Select  - Pin 10
Serial Clock - Pin 13
Data In      - Pin 11
Data Out     - Pin 12
Org Select   - Pin 8 (optional)
```

## Initialization:
There are several ways to initialize the Library.
```
M93Cx6 eeprom = M93Cx6(cs, sk, di, do);
M93Cx6 eeprom = M93Cx6(cs, sk, di, do, org);
M93Cx6 eeprom = M93Cx6(pwr, cs, sk, di, do);
M93Cx6 eeprom = M93Cx6(pwr, cs, sk, di, do, org);
```
Once the library is initialized, set both the chip type (M93C46, M93C56...M93C86) and organization (ORG_8 or ORG_16).  If no chip or organization is selected, the library defaults to the M93C46 with ORG_16.
```
eeprom.setChip(M93C56);
eeprom.setOrg(ORG_8);
```

## Usage:
Read is simple:
```
uint16_t r = eeprom.read(address);  // for ORG_16
uint8_t  r = eeprom.read(address);  // for ORG_8
```

Write and Erase require a writeEnable() before the actual write/erase command.  It is best practice to always writeDisable() after write/erase operations.
```
eeprom.writeEnable();
eeprom.write(address, data);
eeprom.writeDisable();
```

## API:
### M93Cx6(pwr, cs, sk, di, do, org);
* pwr - Power Pin (optional)
* cs  - Chip Select Pin
* sk  - Serial Clock Pin
* di  - Data In Pin
* do  - Data Out Pin
* org - Organization Pin (optional, if left unselected the chip defaults to ORG_16)
### setChip(chip);
* chip - can be M93C46, M93C56, M93C66, M93C76, M93C86
* (defaults to M93C46)
### setOrg(org);
* org - either ORG_8 or ORG_16
* (defaults to ORG_16)
### setCheckStatus(1|0);
* TRUE (default) the library waits for a READY status from the chip after write/erase operations.
* FALSE disables the wait for READY.
### powerUp(); powerDown(); restart();
* If power pin (pwr) is connected, the library will powerUp, powerDown, or restart the M93Cx6 chip.
### read(address);
* Reads a byte (ORG_8) or word (ORG_16) from the eeprom address.
* Returns byte or word read.
### write(address, data);
* Writes data to address.
### writeAll(data);
* Writes data to the whole chip.  Can be used to 0 (zero) the chip.
### erase(address);
* Erases specific address.  Erase leaves the value of 0xFF (ORG_8) or 0xFFFF (ORG_16)
### eraseAll();
* Erases the whole chip.
### writeEnable();
* Enables write and erase operations.  Must preceed any write or erase operations, but will stay enabled until disabled or the power is cycled.
### writeDisable();
* Disables write and erase operations.  For best practices, disable after write/erase operations.
