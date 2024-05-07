#include <SPI.h>

enum { REG_LATCH_595 = 9, REG_LATCH_165 = 8 }; 

void setup()
{
    Serial.begin(9600);
    SPI.begin();
    pinMode(REG_LATCH_595, OUTPUT);
    pinMode(REG_LATCH_165, OUTPUT);
    digitalWrite(REG_LATCH_595, HIGH);
    digitalWrite(REG_LATCH_165, HIGH);
}

void loop()
{
  
static uint8_t last_input_states = 0;
    digitalWrite(REG_LATCH_165, LOW); 
    digitalWrite(REG_LATCH_165, HIGH);

   uint8_t states = SPI.transfer(0);

    if (states != last_input_states)
    {
        uint8_t changed = states ^ last_input_states;
        last_input_states = states;

        for (int i = 0; i < 8; ++i)
        {
            if (changed & 1)
            {
                Serial.print("#");
                Serial.print(i+1);
                Serial.print(" -> ");
                Serial.println(states & 1);
            }

            changed >>= 1;
            states >>= 1;
        }
    }
    digitalWrite(REG_LATCH_595, LOW); 
    SPI.transfer(states); 
    digitalWrite(REG_LATCH_595, HIGH);

}