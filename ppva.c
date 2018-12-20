#include <16f877a.h> 
#device adc=10
#include <stdio.h>
#fuses HS,NOLVP,NOWDT,NOPROTECT
#use delay(clock=20000000) 
#define use_portb_kbd TRUE
#include <lcd.c>
#include <kbd.c> 
#include "touchcode.c"
#use rs232(baud=9600,parity=N,xmit=PIN_c6,rcv=PIN_c7,bits=8,stream=GSM)
int c[4];
int count=0;
int j;
void gsm_ini()
{
   delay_ms(1000);
   fprintf(GSM,"AT\r\n");
   fputc(0x0D,GSM);
   fputc(0x0A,GSM);
   delay_ms(3000);
   fprintf(GSM,"AT+CMGF=1\r\n");
   fputc(0x0D,GSM);
   fputc(0x0A,GSM);
   delay_ms(3000);
   
}   
void send_sms()
{
   delay_ms(1000);
   fputc(0x19,GSM);
   delay_ms(3000);
   fputc(0x1A,GSM);
}
void send_sms_num()
{
     fprintf(GSM,"AT+CMGS=");
      fputc(0x22,GSM);
      fprintf(GSM,"+919947236590");
     fputc(0x22,GSM);
     fprintf(GSM,"\r\n");
   fputc(0x0D,GSM);
   fputc(0x0A,GSM);
   delay_ms(3000);
   fprintf(GSM,"theft alert!!! ");
   send_sms();
}

int readin()
{int val;
if(input(PIN_C4))
val=getval();
else 
val=kbd_getc();
return val;
}

void get_code()
{int k=0;
int i=0;
lcd_putc('\f');
lcd_gotoxy(1,1);
 lcd_putc("ENTER KEY");
 lcd_gotoxy(1,2);
while(i<4)
  {k = readin();           
      if(k!=0)                    
      { c[i]=k;
         i++;
         lcd_putc(k);            
         k=0;                    
         delay_ms(250);         
      } 
      delay_ms(1);
  }
}

void main() 
{int s[4]={'1','2','3','4'};
int32 x;
char n;
setup_timer_0(RTCC_EXT_L_TO_H|RTCC_DIV_1|RTCC_8_bit);
 output_high(PIN_C5);
    
   delay_ms(50); 
  
   lcd_init();                   // Turn LCD ON, along with other initialization commands
   kbd_init();    // Initialize Keypad
 delay_ms(100);
  while(1)
   {
   if(count<3)
   {
      get_code();
   count++;
   if(c[0]==s[0]&&c[1]==s[1]&&c[2]==s[2]&&c[3]==s[3])
   {
   output_high(PIN_C0);
    break;
   }
   
   else
   {
   lcd_putc('\f');
lcd_gotoxy(1,1);
 lcd_putc("CODE ERROR");
  delay_ms(1000);  
    }
   }
else
 { gsm_ini();
  send_sms_num();
  for(j=0;j<10;j++)
 {output_high(PIN_C1);
delay_ms(500);
 output_low(PIN_C1);
delay_ms(500);
}
   for(j=0;j<120;j++)
 delay_ms(1000);
 count=0;
 }
      
   } lcd_putc('\f');
lcd_gotoxy(1,1);
 lcd_putc("CODE ACCEPTED");
delay_ms(100);
lcd_putc('\f');

while(1)
{ set_timer0(0); 
delay_ms(1000);
x = GET_TIMER0();
lcd_putc("\fSpeed : ");
n=x/10 + '0';
lcd_putc(n);
n=x%10 + '0';
lcd_putc(n);
lcd_putc("kmph");
}   
}



