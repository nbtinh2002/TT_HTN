#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
signed int i=0;

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
    while(1)
    {
        if(i>99) i=0;
        SevenSegDisplay(i);
        _delay_ms(100);
        if(PINB == 0x10)
        {
            _delay_ms(200);
            i++;
        }  
    }
    return;
}
