/*
 * File:   bt53.c
 * Author: nbtin
 *
 * Created on March 1, 2023, 12:56 AM
 */
#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
unsigned int i=0;
void main(void) {
    MCUCR |= 0x80;
    SevenSegOff();
    while(1)
    {
        READKEY;
        LED7D1=SegCode[i];
        if(i>0) 
        {
            if(!Buttons.DOWN)
            {
                while(!Buttons.DOWN) READKEY;
                i--;
            }   
        }
        if(i<9)
        {
            if(!Buttons.UP)
            {
                while(!Buttons.UP) READKEY;
                i++;
            }
        }
        if(!Buttons.LEFT) i=0;       
        if(!Buttons.RIGHT)i=9;  
    }
    return;
}
