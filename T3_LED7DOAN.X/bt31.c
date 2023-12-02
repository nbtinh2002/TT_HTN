#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>

SevenSegDisplay(unsigned int value)
{
    LED7D1 = SegCode[value%10];
    LED7D2 = SegCode[(value/10)%10];
    LED7D3 = SegCode[(value/100)%10];
    LED7D4 = SegCode[(value/1000)%10];
}

SevenSegDisplayScan(unsigned int value)
{
    LED7IDDATA = SegCode[value%10];
    LED7IDCTR = 0b11111110;
    _delay_ms(50);
    LED7IDCTR = 0xff;
    LED7IDDATA = SegCode[(value/10)%10];
    LED7IDCTR = 0b11111101;
    _delay_ms(50);
    LED7IDCTR = 0xff;
    LED7IDDATA = SegCode[(value/100)%10];
    LED7IDCTR = 0b11111011;
    _delay_ms(50);
    LED7IDCTR = 0xff;
    LED7IDDATA = SegCode[(value/1000)%10];
    LED7IDCTR = 0b11110111;
    _delay_ms(50);
    LED7IDCTR = 0xff;
}
void main(void) {
 
    MCUCR |= 0x80;
    SevenSegDisplay(3124);
    while(1)SevenSegDisplayScan(3124);
    return;
}