#include <SPI.h>
enum { REG_SELECT = 8 }; 
void setup()
{

 SPI.begin();
 pinMode(REG_SELECT, OUTPUT);
 digitalWrite(REG_SELECT, LOW); 
 SPI.transfer(0); 

 digitalWrite(REG_SELECT, HIGH);
}

void rotateLeft(uint8_t &bits)
{
 uint8_t high_bit = bits & (1 << 7) ? 1 : 0;
 bits = (bits << 1) | high_bit;
}
void loop()
{
 static uint8_t nomad = 1; 

 digitalWrite(REG_SELECT, LOW);
 SPI.transfer(nomad);
 digitalWrite(REG_SELECT, HIGH);
 
 rotateLeft(nomad);
 delay(1000 / 8);
}