#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
unsigned long led = 0x55555555;
unsigned int i;
void LedDisplay(unsigned long led)
{
    LED0 = led&0x000000ff; 
    LED1 = (led>>8)&0x000000ff;
    LED2 = (led>>16)&0x000000ff;
    LED3 = (led>>24)&0x000000ff;
}
void main(void) {
    MCUCR |= 0x80;
    SevenSegOff();
    for(i=0;i<32;i++)
    {
        led=(unsigned long)1<<i;
        LedDisplay(led);
        _delay_ms(200);
    }
    return;
}