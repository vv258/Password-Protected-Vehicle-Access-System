long x,y;
unsigned int GetX() {
//reading X
set_adc_channel(0);
output_high(PIN_C2); // DRIVEA = 1 (LEFT drive on, RIGHT drive on, TOP drive off )
output_low(PIN_C3);// DRIVEB = 0 (BOTTOM drive off )
Delay_ms(15);
return read_adc(); // reading X value from RA0 (BOTTOM)
}
unsigned int GetY() {
//reading Y
set_adc_channel(1);
output_high(PIN_C3); // DRIVEA = 0 (LEFT drive off , RIGHT drive off , TOP drive on)
output_low(PIN_C2); // DRIVEB = 1 (BOTTOM drive on)
Delay_ms(15);
return read_adc(); // reading Y value from RA1 (from LEFT)
}

char getval()
{int row,col;
char p;
char val[3][4]={'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#'};
setup_adc_ports(RA0_RA1_RA3_ANALOG);
setup_adc(ADC_CLOCK_DIV_8 );
do
{x= GETX();
Delay_ms(5);
y= GETY();
Delay_ms(5);
} while(x<20 || x>1000 || y<20 || y>1000);
row=x/85;
col=y/65;
         lcd_putc("x =");
p=x%10+'0';
x=x/10; 
         lcd_putc(p);   
p=x%10+'0';
x=x/10; 
         lcd_putc(p);   
p=x%10+'0';
x=x/10; 
         lcd_putc(p);   
p=x%10+'0';
x=x/10; 
         lcd_putc(p);         
   lcd_putc(" y =");
p=y%10+'0';
y=y/10; 
         lcd_putc(p);   
p=y%10+'0';
y=y/10; 
         lcd_putc(p);   
p=y%10+'0';
y=y/10; 
         lcd_putc(p);   
p=y%10+'0';
y=y/10; 
         lcd_putc(p);         

lcd_putc(" ");
return(val[row][col]);
}

