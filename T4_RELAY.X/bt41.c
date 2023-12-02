
#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>

void main(void) {
    DDRB=0x00;
    MCUCR |= 0x80;
    SevenSegOff();
    while(1)
    {
        relays.RL0 = 1;
        relays.RL7 = 1;
        RELAY_ACTIVATION;
    }
    return;
}