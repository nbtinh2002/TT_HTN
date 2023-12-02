/*
 * File:   bt54.c
 * Author: nbtin
 *
 * Created on March 1, 2023, 12:58 AM
 */
#include <xc.h>
#include "header.h"
#define F_CPU 1000000
#include <util/delay.h>
unsigned int ttrl,ttdc;
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
    DDRB =0xff;
    DDRF =0x00;
    
    SevenSegOff();
    LcdInit();
    
    PrintL("Relay den: Off",1,0);
    PrintL("Dong co: Off",2,0);
    
    while(1)
    {
        READKEY ;
        if(PINB &= 1)
        {   
            PrintL("Mode: Auto  ",0,5);
            PrintL("CBAsang:",3,0);
            PrintL("CBNhiet:",3,10);
            if(PINB==0x03|PINB==0x07) ttrl=1;
            else ttrl=0;
            if(PINB==0x05|PINB==0x07) ttdc=1;
            else ttdc=0;
        }
        else
        {   
            PrintL("Mode: Manual",0,5);
            PrintL("                   ",3,0);
            if(!Buttons.BTN1)
            {
                while(!Buttons.BTN1) READKEY;
                ttrl=!ttrl;
            }
            if(!Buttons.BTN2)
            {
                while(!Buttons.BTN2) READKEY;
                ttdc=!ttdc;
            }
        }
        if(ttrl==0)
        {
            PrintL("Relay den: Off",1,0);
            if(PINB &= 1)PrintL("CBAsang:0",3,0);
            relays.RL7=0;
            RELAY_ACTIVATION;    
        }
        else
        {
            PrintL("Relay den: On ",1,0);
            if(PINB &= 1)PrintL("CBAsang:1",3,0);
            relays.RL7=1;
            RELAY_ACTIVATION;
        }
        if(ttdc==0)
        {
            PrintL("Dong co: Off",2,0);
            if(PINB &= 1)PrintL("CBNhiet:0",3,10);
            Motors.DC1=STOP;
            MOTOR_ACTIVATION;
        }
        else
        {
            PrintL("Dong co: On ",2,0);
            if(PINB &= 1)PrintL("CBNhiet:1",3,10);
            Motors.DC1=FORWARD;
            MOTOR_ACTIVATION;
        }
    }
    return;
}