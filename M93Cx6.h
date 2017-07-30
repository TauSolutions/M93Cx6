/******************************************************************************
 **  
 **  Library for the 93Cx6 EEPROM chips
 **  
 **  @author Travis Lesicka
 **  @version  0.1 (Alpha)
 *****************************************************************************/

#ifndef M93Cx6_h
#define M93Cx6_h

//  Uncomment the following line to enable delay between pin toggles
//#define PIN_DELAY_TIME		50

//  Devices Supported
#define M93C46	46
#define M93C56	56
#define M93C66	66
#define M93C76	76
#define M93C86	86

//  8-bit or 16-bit Data Organisation
#define ORG_8	8
#define ORG_16	16

//  EEPROM Operation Codes with Start Bit built in
#define OP_READ		B110
#define OP_WRITE	B101
#define OP_WEN		B10011
#define OP_WDS		B10000
#define OP_ERASE	B111
#define OP_ERAL		B10010
#define OP_WRAL		B10001

//  Time Out (ms) for Write/Erase Check Status
#define CHECK_STATUS_TIMEOUT	50

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class M93Cx6
{
  public:
	M93Cx6(uint8_t csPin, uint8_t skPin, uint8_t diPin, uint8_t doPin, uint8_t orgPin);
	M93Cx6(uint8_t pwrPin, uint8_t csPin, uint8_t skPin, uint8_t diPin, uint8_t doPin, uint8_t orgPin);
	void setChip(uint8_t);         //  Select which chip (M93C46, M93C56, etc)
	void setOrg(uint8_t);          //  Set Data Organisation (ORG_8 or ORG_16)
	void setCheckStatus(uint8_t);  //  Check write status
	uint16_t read(uint8_t);        //  Read value at the address
	void write(uint8_t, uint16_t); //  Write value to address
	void writeAll(uint16_t);       //  Write All address with value
	void erase(uint8_t);           //  Erase address
	void eraseAll();               //  Erase the whole chip
	void writeEnable();            //  Enable Write/Erase operations
	void writeDisable();           //  Disable Write/Erase operations
	void powerUp();                //  Power Up the chip if option is enabled
	void powerDown();
	void restart();

  private:
    uint8_t _dataLength, _addressLength;
	uint8_t _pwrPin, _csPin, _skPin, _diPin, _doPin, _orgPin;
	uint8_t _org, _chip, _checkStatus;
    uint16_t shiftIn(uint8_t length);
	void shiftOut(uint16_t data, uint8_t length);
	uint8_t checkStatus();
	uint8_t pinMask(uint8_t);
	void pinHigh(uint8_t);         //  Faster than digitalWrite
	void pinLow(uint8_t);          //  Faster than digitalWrite
};

#endif    //  M93Cx6_h