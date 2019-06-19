#include<P18F4550.h>
#include"lcd.h"
#include"uso.h"

int temp,perc;
int q;
char msg[13]="Water Level=",msg1[13]="Valve On",msg2[13]="Valve Off";

void delay_1(unsigned int time)
{

    unsigned int o,p;
    for(o=0;o<time;o++)
        for(p=0;p<5000;p++);

}

void main()
{

ADCON1=0x0f;
TRISAbits.TRISA2=1;//DTMF 3
TRISAbits.TRISA3=1;//DTMF 2
TRISAbits.TRISA4=1;//DTMF 1
TRISAbits.TRISA5=1;//DTMF 0

TRISC=0x00;

TRISAbits.TRISA0=0; //trig
TRISAbits.TRISA1=1; //echo


//TRISCbits.TRISC0=0;
//TRISCbits.TRISC1=0;
//TRISCbits.TRISC2=0;

//LATCbits.LATC0=1;
//LATCbits.LATC2=1;
//LATCbits.LATC1=1;
lcd_init();


while(1)
{

us_trig();

temp=us_echo();

perc=temp/24;
perc=perc*100;
perc=1000-perc;


for(q=0;q<12;q++)
{
lcd_data(msg[q]);
}


perc=perc/10;
lcd_cmd(0x8E);
lcd_data(perc%10 + 48);


perc=perc/10;
lcd_cmd(0x8D);
lcd_data(perc%10 + 48);


lcd_cmd(0x8F);
lcd_data('%');
delay_1(200);
lcd_cmd(0x01);


if(PORTAbits.RA5==0&&PORTAbits.RA4==0&&PORTAbits.RA3==1&&PORTAbits.RA2==0)
{

TRISCbits.TRISC1=0;//valve
LATCbits.LATC1=1;
LATCbits.LATC0=1;
lcd_data('V');
lcd_data('a');
for(q=0;q<8;q++)
{
lcd_data(msg1[q]);
}
delay_1(200);
lcd_cmd(0x01);

}


if(PORTAbits.RA5==1&&PORTAbits.RA4==0&&PORTAbits.RA3==1&&PORTAbits.RA2==0)
{

TRISCbits.TRISC1=1;
TRISCbits.TRISC0=0;
LATCbits.LATC1=0;
LATCbits.LATC0=0;
lcd_data('V');
lcd_data('a');
for(q=0;q<8;q++)
{
lcd_data(msg2[q]);
}
delay_1(200);
lcd_cmd(0x01);
}

if(PORTAbits.RA5==0&&PORTAbits.RA4==1&&PORTAbits.RA3==1&&PORTAbits.RA2==0)
{
TRISCbits.TRISC2=0;
LATCbits.LATC2=1;
}

if(PORTAbits.RA5==1&&PORTAbits.RA4==1&&PORTAbits.RA3==1&&PORTAbits.RA2==0)
{

TRISCbits.TRISC2=0;
LATCbits.LATC2=0;
}


/*
if(perc<=500)
{
TRISCbits.TRISC2=0;
LATCbits.LATC2=1;

}


if(perc==700)
{
//TRISCbits.TRISC2=0;
LATCbits.LATC2=0;

}

*/
}


}


