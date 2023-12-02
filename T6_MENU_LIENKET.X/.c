/*
 * File:   nextmain.c
 * Author: nbtin
 *
 * Created on March 2, 2023, 2:31 AM
 */
#include <xc.h>
#include "nextheader.h"
#define F_CPU 1000000
#include <util/delay.h>
SevenSegDisplay(unsigned int value)
{  
    if(value/1000%10==0) LED7D4 = 0xff;
    else LED7D4 = SegCode[(value/1000)%10];
    if(value/100%10==0) LED7D3 = 0xff;
    else LED7D3 = SegCode[(value/100)%10];
    if(value/10%10==0) LED7D2 = 0xff;
    else LED7D2 = SegCode[(value/10)%10];
    LED7D1 = SegCode[value%10];
}
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
char OneWireReset(void)
{
    char Presence;
    OneWire_Master;
    OneWire_Low;
    _delay_us(480);
    OneWire_Free;
    Presence = OneWire_State;
    _delay_us(60);  
}
OneWireWriteByte(unsigned char Byte)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        OneWire_Master;
        if(Byte&0x01)
        {
            OneWire_Low;
            _delay_us(15);
            OneWire_Free;
            _delay_us(45);
            _delay_us(50);
        }
        else
         {
            OneWire_Low;
            _delay_us(15);
            _delay_us(45);
            OneWire_Free;
            _delay_us(30);            
        }      
    }
}
unsigned char OneWireReadByte(void)
{
    unsigned char i;
    unsigned Byte=0;
    for(i=0;i<8;i++)
    {
        OneWire_Master;
        OneWire_Low;
        _delay_us(15);
        OneWire_Free;
        _delay_us(15);
        Byte=Byte>>1;
        Byte=Byte|(OneWire_State<<7);
        _delay_us(30);
    }
    return Byte;
}
void main(void) {
    unsigned int Temp;
    unsigned char data;
    MCUCR |= 0x80;
    XMCRA = 0 ;
    DDRF =0xff;
    LcdInit();
    if(!OneWireReset())
        PrintL("DS18B20 is found",1,0);
    else
        PrintL("DS18B20 is not found",1,0);
    OneWireWriteByte(0x33);
    data = OneWireReadByte();
    

    
    while(1){SevenSegDisplay(data);}
    return;
}
