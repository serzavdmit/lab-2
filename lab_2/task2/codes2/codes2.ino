#include <SPI.h>

enum { REG_SELECT = 8 };

void writeShiftRegister16(int ss_pin, uint16_t value)
{
  digitalWrite(ss_pin, LOW);
  SPI.transfer(highByte(value));
  SPI.transfer(lowByte(value));
  digitalWrite(ss_pin, HIGH);
}

void rotateLeft(uint16_t &bits)
{
  uint16_t high_bit = bits & (1 << 15) ? 1 : 0;
  bits = (bits << 1) | high_bit;
}

void setup()
{
  SPI.begin();
  pinMode(REG_SELECT, OUTPUT);
  writeShiftRegister16(REG_SELECT, 0);
}

void loop()
{
  static uint16_t nomad = 1;
  writeShiftRegister16(REG_SELECT, nomad);
  rotateLeft(nomad);
  delay(500);
}
