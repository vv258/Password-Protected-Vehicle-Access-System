int16 x,y,x1,y1;
int16 GetX() {
//reading X

output_high(PIN_C2); 
output_low(PIN_E0);
outpUT_float(PIN_C3);
outpUT_float(PIN_E1);
// DRIVEB = 0 (BOTTOM drive off )
set_adc_channel(0);
Delay_ms(10);
return read_adc(); // reading X value from RA0 (BOTTOM)
}
int16 GetY() {
//reading Y

output_high(PIN_C3); 
output_low(PIN_E1);
outpUT_float(PIN_C2);
outpUT_float(PIN_E0);
set_adc_channel(1);
Delay_ms(10);
return read_adc(); // reading Y value from RA1 (from LEFT)
}

char getval()
{int row,col;
char p;
char val[3][4]={'*', '0', '9', '#', '5', '6', '7', '8', '1', '2', '3', '4'};
setup_adc_ports(RA0_RA1_RA3_ANALOG);
setup_adc(ADC_CLOCK_INTERNAL );
do
{x= GETX();
Delay_ms(10);
y= GETY();
Delay_ms(100);
row=y/330;
col=x/220;
x1= GETX();
Delay_ms(10);
y1= GETY();
Delay_ms(10);
output_high(pin_c1);
delay_ms(100);
output_low(pin_c1);
} while(x<20 || y<20 || (x1/10)!=(x/10) || (y1/10)!=(y/10));
return(val[row][col]);
}

