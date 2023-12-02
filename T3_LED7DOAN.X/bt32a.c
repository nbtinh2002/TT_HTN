#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
signed int i=0;
void SevenSegOff()
{
    LED7IDDATA=0xff;
    LED7IDCTR = 0b11110111;
    LED7IDCTR = 0b11111011;
    LED7IDCTR = 0b11111101;
    LED7IDCTR = 0b11111110;
}
SevenSegDisplay(unsigned int value)
{  
    if(value/1000%10==0) LED7D4 = 0xff;
    else LED7D4 = SegCode[(value/1000)%10];
    if(value/100%10==0) LED7D3 = 0xff;
    else LED7D3 = SegCode[(value/100)%10];
    if(value/10%10==0) LED7D2 = 0xff;
    else LED7D2 = SegCode[(value/10)%10];
    LED7D1 = SegCode[value%10];
}
void main(void) {
    DDRB=0x00;
    MCUCR |= 0x80;
    SevenSegOff();
    while(1)
    {
        for(i=0;i<100;i++)
        {
            SevenSegDisplay(i);  
            _delay_ms(100);
        }
        for(i=99;i>=0;i--)
        {
            SevenSegDisplay(i);  
            _delay_ms(100);
        }
    }    
    return;
}
