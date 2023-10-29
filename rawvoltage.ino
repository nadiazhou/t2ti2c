/*
  Reading raw voltage from the ADS122C04 AIN1 and AIN0 pins.
  Using the Sparkfun Arduino ADS122c04 Library

  The function readRawVoltage:
  - disables the IDAC current source
  - sets the gain to 1
  - configures the chip to use the internal 2.048V reference

  readRawVoltage returns a int32_t. The LSB is 2.048 / 2^23 = 0.24414 uV (0.24414 microvolts).

  1. Make sure the PCB is configured for 4-wire mode (split pads A, B and C are open).
  2. Feed the differential voltage you want to measure onto terminals 2 & 3. +/-2.048V maximum!
  3. Terminal 2 is positive. Terminal 3 is negative (connect to 0V if required).
*/

#include <Wire.h>

#include <SparkFun_ADS122C04_ADC_Arduino_Library.h> 
SFE_ADS122C04 mySensor;

void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println(F("Raw Voltage Test"));

  Wire.begin();

  //mySensor.enableDebugging(); 

  if (mySensor.begin() == false) // Default: Address 0x45 and the Wire port
  {
    Serial.println(F("No input detected at the address. Please check wiring. Freezing."));
    while (1)
      ;
  }
  int ledPin = 13;
  Serial.println(ADS122C04_RAW_MODE, HEX); //0x4
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  mySensor.configureADCmode(ADS122C04_RAW_MODE); 
 
}

void loop()
{
  // Get the raw voltage as int32_t
  int32_t raw_v = mySensor.readRawVoltage();
  

  // Convert to Volts (method 1)
  float volts_1 = ((float)raw_v) * 244.14e-9;

  // Convert to Volts (method 2)
  float volts_2 = ((float)raw_v) / 4096000;

  // Print the temperature and voltage
  Serial.print(F("The raw voltage is 0x"));
  Serial.print(raw_v, HEX);
  Serial.print(F("\t"));
  Serial.print(volts_1, 7); // Print the voltage with 7 decimal places
  Serial.print(F("V\t"));
  Serial.print(volts_2, 7); // Print the voltage with 7 decimal places
  Serial.println(F("V"));

  delay(250); 
}
