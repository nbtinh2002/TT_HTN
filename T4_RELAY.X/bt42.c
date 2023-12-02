#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
SevenSegDisplayScan()
{
    LED7IDDATA=0xff;
    LED7IDCTR = 0b11110111;
    LED7IDCTR = 0b11111011;
    LED7IDCTR = 0b11111101;
    LED7IDCTR = 0b11111110;
}
void main(void) {
    MCUCR |= 0x80;
    DDRB=0x00;     
    LED7D1 = SegCode[relays.RL0];
    LED7D2 = SegCode[relays.RL1];
    LED7D3 = SegCode[relays.RL2];
    LED7D4 = SegCode[relays.RL3];
while(1)
    {
        SevenSegDisplayScan();
        if(PINB==0x10)
        {
            _delay_ms(120);
            if(PINB==0x10)
            {
                relays.RL0 = ~(relays.RL0);
                RELAY_ACTIVATION;
                LED7D1 = SegCode[relays.RL0];       
            }
        }     
        if(PINB==0x20)
        {
            _delay_ms(120);
            if(PINB==0x20)
            {
                relays.RL1 = ~(relays.RL1);
                RELAY_ACTIVATION;
                LED7D2 = SegCode[relays.RL1];      
            }
        } 
        if(PINB==0x40)
        {
            _delay_ms(120);
            if(PINB==0x40)
            {
                relays.RL2 = ~(relays.RL2);
                RELAY_ACTIVATION;
                LED7D3 = SegCode[relays.RL2];   
            }
        } 
        if(PINB==0x80)
        {
            _delay_ms(120);
            if(PINB==0x80)
            {
                relays.RL3 = ~(relays.RL3);
                RELAY_ACTIVATION;
                LED7D4 = SegCode[relays.RL3];
            }
        }  
    }       
    return;
} 
