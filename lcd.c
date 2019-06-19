#include <p18f4550.h>
#include "lcd.h"



void delay(unsigned int time)
{
unsigned int i,j;
for(j=0;j<time;j++)
{
for(i=0;i<5;i++);
}

}

void lcd_data(unsigned char data)
{
PORTB=data;
PORTDbits.RD6=1;
PORTDbits.RD7=1;
delay(50);
PORTDbits.RD7=0;
}

void lcd_cmd(unsigned char cmd)
{
PORTB=cmd;
PORTDbits.RD6=0;
PORTDbits.RD7=1;
delay(50);
PORTDbits.RD7=0;
}

void lcd_init()
{
TRISB=0x00;
TRISDbits.TRISD6=0;
TRISDbits.TRISD7=0;
//en=0;

lcd_cmd(0x38);

//lcd_cmd(0x01);

lcd_cmd(0x0c);

//lcd_cmd(0x06);

lcd_cmd(0x80);
} 