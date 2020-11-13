#include <mega8.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

// Declare your global variables here

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (0<<ADLAR))

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

void main(void)
{
// Declare your local variables here
float result1;
float result2;

char lcd_buffer[20];
char lcd_buffer2[20];


// ADC initialization
// ADC Clock frequency: 125,000 kHz
// ADC Voltage Reference: AREF pin
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (0<<ADPS0);
SFIOR=(0<<ACME);



lcd_init(8);
       lcd_gotoxy(0,0);
       lcd_puts("v meter"); 
       delay_ms(100);
       lcd_clear();
       lcd_gotoxy(0,1);
       lcd_puts("by");
       delay_ms(100);
       lcd_clear();
       lcd_gotoxy(0,0);
       lcd_puts("viktor");
       delay_ms(100);
       lcd_clear();

while (1)
      {
       
       
        
      
       lcd_gotoxy(0,0);
       result1=((5.00*read_adc(0)* 5.24)/512.00);
       sprintf(lcd_buffer,"U1=%.2fV",result1);
       lcd_puts(lcd_buffer);  
       
       lcd_gotoxy(0,1);
       result2=((5.00*read_adc(1)* 5.24)/512.00);
       sprintf(lcd_buffer2,"U2=%.2fV",result2);
       lcd_puts(lcd_buffer2);
      }
}