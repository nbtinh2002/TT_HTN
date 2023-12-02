/*
 * File:   b61.c
 * Author: nbtin
 *
 * Created on March 2, 2023, 2:31 AM
 */
#include <xc.h>
#include "header71.h"
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
void MenuDisplay(Menu *menu)
{
    PrintL(menu->Title,0,0);
    PrintL(menu->List1,1,0);
    PrintL(menu->List2,2,0);
    PrintL(menu->List3,3,0);   
}

void main(void) {
//    unsigned char select=1;
    unsigned char mode397=0,ttled397=0,ttrl397=0;
    Menu *menu;
    MCUCR |=0x80;
    XMCRA = 0;
    DDRG = 0x0f;
   
    LcdInit();
    SevenSegOff();
   
    while(1)
    {
        menu = &Mode000;
        switch (mode397)
        {
            case 0:
            {
                if(ttled397==1)
                {
                    if(ttrl397==1) menu=&Mode011;
                    else menu=&Mode010; 
                }
                else
                {
                    if(ttrl397==1) menu=&Mode001;
                    else menu=&Mode000; 
                }
                MenuDisplay(menu);
            }
                break;
            case 1:
            {
                menu=&Mode130;
                MenuDisplay(menu);
            }
                break;
            case 2: 
            {
                if(ttrl397==1) menu=&Mode201;
                else menu=&Mode200;
            }
                break;
        }
        MenuDisplay(menu);
        READKEY;
        if(!Buttons.A)
        {
            while(!Buttons.A) READKEY;
            mode397++;
        }
        if(mode397==3) mode397=0;
        //LED7D1=SegCode[mode397];
        if(mode397==0)
        {
            if(!Buttons.B)
            {
                while(!Buttons.B) READKEY;
                ttled397=!ttled397;
            }
            if(!Buttons.C)
            {
                while(!Buttons.C) READKEY;
                ttrl397=!ttrl397;
            }
        }
        if(ttled397==1) LED0=0xff;
        else LED0=0;
        if(ttrl397==1) {Relays.relay.RL0 = 1; RELAY_ACTIVATION;}
        else {Relays.relay.RL0 = 0; RELAY_ACTIVATION;}
        if(mode397==1)
        {
            ttrl397=0;
            Relays.relay.RL0 = 0; RELAY_ACTIVATION;
            LED1=LED0=0xff;
            for(unsigned long i=0;i<1000;i++){READKEY;}
            LED1=LED0=0x0;for(unsigned long i=0;i<1000;i++){READKEY;}
        }
        if(mode397==2)
        {
            LED0=LED1=0;
            if(!Buttons.D)
            {
                while(!Buttons.D) READKEY;
                ttrl397=!ttrl397;
            }
        }
    }
    return;
}
