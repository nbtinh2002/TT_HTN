/*
 * File:   bt51.c
 * Author: nbtin
 *
 * Created on March 1, 2023, 12:47 AM
 */
#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
void LcdInit()
{
    LCD_INS = 0x38; LCDE_H ;_delay_us(1); LCDE_L ;_delay_us(1); 
    _delay_us(200);
    LCD_INS = 0x0C; LCDE_H ;_delay_us(1); LCDE_L ;_delay_us(1); 
    _delay_us(200);
    LCD_INS = 0x06; LCDE_H ;_delay_us(1); LCDE_L ;_delay_us(1); 
    _delay_us(200);
    LCD_INS = 0x01; LCDE_H ;_delay_us(1); LCDE_L ;_delay_us(1); 
    _delay_ms(20);
}
void PrintL(const char *str, unsigned line, unsigned col)
{
    unsigned char add;
    switch (line)
    {
        case 0 : add= 0x80;break;
        case 1 : add= 0xC0;break;
        case 2 : add= 0x94;break;
        case 3 : add= 0xD4;break;  
    }
    LCD_INS = add + col; LCDE_H; _delay_us(1);LCDE_L; _delay_us(50);
    while(*(str)!='\0')
    {
        LCD_DATA = *str++; LCDE_H; _delay_us(1);LCDE_L; _delay_us(10);
    }
}
void main(void) {
    MCUCR |= 0x80;
    DDRG =0x0f;
    SevenSegOff();
    Motors.DC1= STOP;
    Motors.DC2= STOP;
    MOTOR_ACTIVATION;
    LcdInit();
    PrintL("Hello",0,5);
    while(1)
    {
        READKEY;
        if(!Buttons.LEFT)
        {
            while(!Buttons.LEFT) READKEY;
            Motors.DC1 = FORWARD;
        }
        if(!Buttons.RIGHT)
        {
            while(!Buttons.RIGHT) READKEY;
            Motors.DC1 = REWARD;
        }   
        MOTOR_ACTIVATION;
    }
    return;
}
