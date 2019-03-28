#include "GY906.h"

GY906::GY906(uint8_t i2caddr) 
{
  _addr = i2caddr;
}

boolean GY906::begin(void) 
{
  Wire.begin();
   return true;
}

double GY906::readObjectTempC(void) 
{
  return readTemp(MLX90614_TOBJ1);
}


double GY906::readAmbientTempC(void) 
{
  return readTemp(MLX90614_TA);
}

float GY906::readTemp(uint8_t reg) 
{
  float temp; 
  
  temp = read16(reg);
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

uint16_t GY906::read16(uint8_t a) 
{
  uint16_t ret;

  Wire.beginTransmission(_addr);                  // start transmission to device 
  Wire.write(a);                                  // sends register address to read from
  Wire.endTransmission(false);                    // end transmission
  
  Wire.requestFrom(_addr, (uint8_t)3);            // send data n-bytes read
  ret = Wire.read();                              // receive DATA
  ret |= Wire.read() << 8;                        // receive DATA

  uint8_t pec = Wire.read();

  return ret;
}
