
// INCLUDE FILES
#include <system.h>
#include <memory.h>

// PIC CONFIG
#pragma DATA _CONFIG1, _FOSC_INTOSC & _WDTE_OFF & _MCLRE_OFF &_CLKOUTEN_OFF
#pragma DATA _CONFIG2, _WRT_OFF & _PLLEN_OFF & _STVREN_ON & _BORV_19 & _LVP_OFF
#pragma CLOCK_FREQ 8000000

// Define pins
#define P_LED 			portc.2
#define P_CLK			portc.4
#define P_DAT			portc.3
#define P_ENA			porta.5

void writeShift(unsigned int d)
{
	P_ENA = 0;
	P_CLK = 0;
	P_DAT = 1;
	P_CLK = 1;
	P_DAT = 0;
	
	unsigned int m = 0x8000;
	while(m)
	{
		P_ENA = 0;
		P_CLK = 0;
		P_CLK = 1;
		P_ENA = !!(m&d);
		m>>=1;
		delay_ms(1);
	}
}


////////////////////////////////////////////////////////////
//
// ENTRY POINT
//
////////////////////////////////////////////////////////////
void main()
{ 
	// osc control / 8MHz / internal
	osccon = 0b01110010;

	// weak pull up on A0 and C5
//	wpua = 0b00000001;
//	wpuc = 0b00100000;
//	option_reg.7 = 0;
	
	
	// configure io
			//76543210
	trisa = 0b00000000;              	
    trisc = 0b00000000;              
    
	ansela = 0b00000000;
	anselc = 0b00000000;

	unsigned int p = 0;
	unsigned int q = 0;
	for(;;)
	{
		writeShift(q);		
		if(!p)
		{
			P_LED = !P_LED;
			if(!q) q=0x8000; else q>>=1;
			p=20;
		}
		p--;
	}
}



