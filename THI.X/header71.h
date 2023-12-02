#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stddef.h>
#ifdef	__cplusplus
#endif /* __cplusplus */
#ifdef	__cplusplus
#endif /* __cplusplus */
#endif	/* XC_HEADER_TEMPLATE_H */

unsigned char SegCode[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};

#define EXMEM_ADD 0x1100
//CS defination
#define CS0 0
#define CS1 1
#define CS2 2
#define CS3 3
#define CS4 4
#define CS5 5
#define CS6 6
#define CS7 7
#define CS8 8
#define CS9 9
#define CS10 10
#define CS11 11
#define CS12 12
#define CS13 13
#define CS14 14
#define CS15 15
#define CS16 16
#define CS17 17
#define CS18 18
#define CS19 19
//define external device
#define LED0 *(unsigned char *) (EXMEM_ADD+CS0)
#define LED1 *(unsigned char *) (EXMEM_ADD+CS1)
#define LED2 *(unsigned char *) (EXMEM_ADD+CS2)
#define LED3 *(unsigned char *) (EXMEM_ADD+CS3)

#define LED7D1 *(unsigned char *) (EXMEM_ADD+CS4)
#define LED7D2 *(unsigned char *) (EXMEM_ADD+CS5)
#define LED7D3 *(unsigned char *) (EXMEM_ADD+CS6)
#define LED7D4 *(unsigned char *) (EXMEM_ADD+CS7)

#define LED7IDCTR *(unsigned char *) (EXMEM_ADD+CS8)
#define LED7IDDATA *(unsigned char *) (EXMEM_ADD+CS9)

#define RELAYMAP *(unsigned char *) (EXMEM_ADD+CS10)
#define RELAY_ACTIVATION (*(unsigned char *) (EXMEM_ADD+CS10) = *(unsigned char *)(&Relays))
struct bits{
    unsigned char RL0 : 1 ;
    unsigned char RL1 : 1 ;
    unsigned char RL2 : 1 ;
    unsigned char RL3 : 1 ;
    unsigned char RL4 : 1 ;
    unsigned char RL5 : 1 ;
    unsigned char RL6 : 1 ;
    unsigned char RL7 : 1 ;
};
union Relays {
    unsigned char relayall;
    struct bits relay;
};
union Relays Relays;
#define LCD_DATA *(unsigned char *) (EXMEM_ADD+CS11)
#define LCD_INS *(unsigned char *) (EXMEM_ADD+CS12)
#define LCDE_H (PORTG |=  (1<<3))
#define LCDE_L (PORTG &= ~(1<<3))

#define MOTOR_ACTIVATION (*(volatile unsigned char *) (EXMEM_ADD+CS13) = *(unsigned char *)(&Motors))
#define STOP 0
#define FORWARD 1
#define REWARD 2
struct Motor
{
    unsigned char DC1:2; 
    unsigned char DC2:2;
    unsigned char DCfree:4;
};
struct Motor Motors;
#define READKEY (*(unsigned char *)(&Buttons)=*(volatile unsigned char *) (EXMEM_ADD+CS14))
struct Button
{
    unsigned char LEFT : 1 ;
    unsigned char RIGHT  : 1 ;
    unsigned char UP : 1 ;
    unsigned char A : 1 ;
    unsigned char GO : 1 ;
    unsigned char B : 1 ;
    unsigned char C : 1 ;
    unsigned char D : 1 ;
};
struct Button Buttons;

#define ON 1
#define OFF 0
#define Device_Relay 0
#define Device_Motor1 1
#define Device_Motor2 2
#define Device_LED 3

void ActuatorActivation(char Devices, char Status)
{
    switch (Devices)
    {
        case Device_Relay: Relays.relay.RL0 = Status; RELAY_ACTIVATION;
            break;
        case Device_Motor1: Motors.DC1 = Status; MOTOR_ACTIVATION;
            break;
        case Device_Motor2: Motors.DC2 = Status; MOTOR_ACTIVATION;
            break;
        case Device_LED: if(Status==ON) LED3=0xff;
                         else
                             LED3=0;
            break;    
    }

}


// --------------------------------------------------//

typedef struct Linker{                                         //MENU LIST
    char menuID;
    struct Linker *pre;
    char Title[20];
    char List1[20];
    char List2[20];
    char List3[20];
} Menu ;

Menu Mode000,Mode001,Mode010,Mode011;
Menu Mode130;
Menu Mode200,Mode201;
Menu Mode000 = {
    NULL,
    NULL,
    "     MODE 0:       ",
    " MANUAL            ",
    " TT 16LED:0        ",
    " TT RELAY:0        "
};     
Menu Mode001 = {
    NULL,
    NULL,
    "     MODE 0:       ",
    " MANUAL            ",
    " TT 16LED:0        ",
    " TT RELAY:1        "
}; 
Menu Mode010 = {
    NULL,
    NULL,
    "     MODE 0:       ",
    " MANUAL            ",
    " TT 16LED:1        ",
    " TT RELAY:0        "
}; 
Menu Mode011 = {
    NULL,
    NULL,
    "     MODE 0:       ",
    " MANUAL            ",
    " TT 16LED:1        ",
    " TT RELAY:1        "
}; 
Menu Mode130 = {
    NULL,
    NULL,
    "     MODE 1:       ",
    " 8led chop tat     ",
    " TT 16LED:3        ",
    " TT RELAY:0        "
}; 

Menu Mode200 = {
    NULL,
    NULL,
    "     MODE 2:       ",
    " Relay only        ",
    " TT 16LED:0        ",
    " TT RELAY:0        "
}; 
Menu Mode201 = {
    NULL,
    NULL,
    "     MODE 2:       ",
    " Relay only        ",
    " TT 16LED:0        ",
    " TT RELAY:1        "
}; 
//-----------------------------------------------------------------------------//
void SevenSegOff()
{
    LED7IDDATA=0xff;
    LED7IDCTR = 0b11110111;
    LED7IDCTR = 0b11111011;
    LED7IDCTR = 0b11111101;
    LED7IDCTR = 0b11111110;
    LED7D2=LED7D3=LED7D4=0xff;
    LED7D1=0xff;
};