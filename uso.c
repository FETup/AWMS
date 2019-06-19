#include <p18f4550.h>
#include "uso.h"
#include "lcd.h"

void timer_delay()
{
T1CON=0x00;
TMR1H=0xFF;
TMR1L=0xD1;
T1CONbits.TMR1ON=1;
while(PIR1bits.TMR1IF==0);
T1CONbits.TMR1ON=0;


TMR1H=0x00;
TMR1L=0x00;
PIR1bits.TMR1IF=0;
}

void us_trig()
{
T1CON=0x00;
LATAbits.LATA0=1;
timer_delay();
LATAbits.LATA0=0;


}


int us_echo()
{

int h,l;
float i;
while(!PORTAbits.RA1);
T1CONbits.TMR1ON=1;
while(PORTAbits.RA1);
T1CONbits.TMR1ON=0;

h=TMR1H;
l=TMR1L;


h=h<<8;
i=l | h;
i=i/58;
return i;
}

void us_disp(unsigned int dist)
{

lcd_cmd(0x01);


lcd_cmd(0x82);
lcd_data(dist%10 + 48);


dist=dist/10;
lcd_cmd(0x81);
lcd_data(dist%10 + 48);

dist=dist/10;
lcd_cmd(0x80);
lcd_data(dist%10 + 48);

dist=0;

}
