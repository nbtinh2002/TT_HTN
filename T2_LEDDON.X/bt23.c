#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>

void main(void) {
    MCUCR |= 0x80;
    DDRB = 0x00;
    while(1)
    {
        if(PINB &=(1<<0))LED0 = 0xff;
        else LED0 = 0;
        if(PINB &=(1<<1))LED1 = 0xff;
        else LED1 = 0;
        if(PINB &=(1<<2))LED2 = 0xff;
        else LED2 = 0;
        if(PINB &=(1<<3))LED3 = 0xff;
        else LED3 = 0;
    }
    return;
}