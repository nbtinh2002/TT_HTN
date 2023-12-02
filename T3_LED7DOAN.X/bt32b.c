#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
signed int i=0;
SevenSegDisplayScan(unsigned int value)
{
    
    if(value/1000%10==0) LED7IDCTR = 0xff;
    else 
    {
        LED7IDDATA = SegCode[(value/1000)%10];
        LED7IDCTR = 0b11110111;
        _delay_ms(50);
        LED7IDCTR = 0xff;
    }
    
    if(value/100%10==0) LED7IDCTR = 0xff;
    else 
    {
        LED7IDDATA = SegCode[(value/100)%10];
        LED7IDCTR = 0b11111011;
        _delay_ms(50);
        LED7IDCTR = 0xff;   
    }
    
    if(value/10%10==0) LED7IDCTR = 0xff;
    else 
    {
        LED7IDDATA = SegCode[value/10%10];
        LED7IDCTR = 0b11111101;
        _delay_ms(50);
        LED7IDCTR = 0xff;
    }
    
    LED7IDDATA = SegCode[value%10];
    LED7IDCTR = 0b11111110;
    _delay_ms(50);
    LED7IDCTR = 0xff;
}
void main(void) {
    DDRB=0x00;
    MCUCR |= 0x80;
    LED7D1=LED7D2=LED7D3=LED7D4=0xff;
    while(1)
    {
        for(i=0;i<100;i++)
        {
            SevenSegDisplayScan(i);  
            _delay_ms(10);
        }
        for(i=99;i>=0;i--)
        {
            SevenSegDisplayScan(i);  
            _delay_ms(10);
        }
    } 
    return;
}
