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
void MenuDisplay(Menu *menu,unsigned char select)
{
    PrintL(menu->Title,0,0);
    PrintL(menu->List1,1,0);
    PrintL(menu->List2,2,0);
    PrintL(menu->List3,3,0);   
    PrintL(">",select,0);
}

void main(void) {
    unsigned char select=1;
    Menu *menu;
    MCUCR |=0x80;
    XMCRA = 0;
    DDRG = 0x0f;
    
    menu = &Main;
    LcdInit();
    MenuDisplay(menu,select);
    SevenSegOff();
    while(1)
    {
        READKEY;
        if(PINB&0x01)
        {
            if(PINB&0x02)
            {
                Relays.relay.RL0=1; 
                RELAY_ACTIVATION;
            }
            else 
            {
                Relays.relay.RL0=0;
                RELAY_ACTIVATION;
            }
            if(PINB&0x04)
            {
                Motors.DC1=1;
                MOTOR_ACTIVATION;
            }
            else 
            {
                Motors.DC1=0;
                MOTOR_ACTIVATION;
            }
        }
        if(!Buttons.DOWN)
        {
            while(!Buttons.DOWN)READKEY;
            select = (select==3) ? 1 : select+1;
            MenuDisplay(menu,select);
        }
        
        if(!Buttons.UP)
        {
            while(!Buttons.UP)READKEY;
            select = (select==1) ? 3 : select-1;
            MenuDisplay(menu,select);
        }
        if(!Buttons.LEFT)
        {
            while(!Buttons.LEFT)READKEY;
            menu = (menu->pre == NULL) ? menu: menu->pre;
            MenuDisplay(menu,select);
        }
        if(!Buttons.RIGHT)
        {
            while(!Buttons.RIGHT)READKEY;
            if(PINB&0x01)
            {
                if(PINB&0x02)
                {
                    switch (select)
                    {
                        case 1: menu = (menu->Menulist11 == NULL) ?menu: menu->Menulist11;break;
                        case 2: menu = (menu->Menulist22 == NULL) ?menu: menu->Menulist22;break;
                    }
                    MenuDisplay(menu,select); 
                }
                else
                {
                    switch (select)
                    {
                        case 1: menu = (menu->Menulist11 == NULL) ?menu: menu->Menulist11;break;
                        case 2: menu = (menu->Menulist222 == NULL) ?menu: menu->Menulist222;break;
                    }
                    MenuDisplay(menu,select);
                }
                if(PINB&0x04)
                {
                    switch (select)
                    {
                        case 1: menu = (menu->Menulist11 == NULL) ?menu: menu->Menulist11;break;
                        case 3: menu = (menu->Menulist33 == NULL) ?menu: menu->Menulist33;break;
                    }
                    MenuDisplay(menu,select); 
                }
                else
                {
                    switch (select)
                    {
                        case 1: menu = (menu->Menulist11 == NULL) ?menu: menu->Menulist11;break;
                        case 3: menu = (menu->Menulist333 == NULL) ?menu: menu->Menulist333;break;
                    }
                    MenuDisplay(menu,select);
                }
            }
            else
            {
                switch (select)
                {
                    case 1: menu = (menu->Menulist1 == NULL) ?menu: menu->Menulist1;break;
                    case 2: menu = (menu->Menulist2 == NULL) ?menu: menu->Menulist2;break;
                    case 3: menu = (menu->Menulist3 == NULL) ?menu: menu->Menulist3;break;
                }
                MenuDisplay(menu,select);
            }
        }
        if(!Buttons.GO)
        {
            while(!Buttons.GO)READKEY;
            switch (select)
            {
                case 1:
                    if(menu->ActivationON!=NULL) menu->ActivationON(menu->menuID,ON);
                    break;
                    
                case 2:
                    if(menu->ActivationOFF!=NULL) menu->ActivationOFF(menu->menuID,OFF);
                    break;
                case 3:
                    menu = (menu->pre == NULL) ? menu: menu->pre;
                    MenuDisplay(menu,select);
                    break;
            }
            
        }
    
    }
    
    return;
}
