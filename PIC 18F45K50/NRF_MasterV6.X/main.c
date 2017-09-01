/*
 * File:   main.c
 * Author: BRNS1
 *
 * Created on May 20, 2017, 12:47 PM
 */


//#define _XTAL_FREQ 16000000UL
#include <xc.h>
#include <stdlib.h>
#include "spi.h"
#include "nRF24L01.h"
#include "wl_module.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"

#pragma config IESO=OFF         // Oscillator Switchover mode disabled
//#pragma config FOSC=HSMP        // external medium power oscillator
//#pragma config PRICLKEN=OFF     // Primary clock can be disabled by software
#pragma config FCMEN=ON         // Fail-Safe Clock Monitor enabled
//#pragma config PLLCFG=OFF       // disable 4xPLL
#pragma config BOREN=SBORDIS    // disable software BOR
#pragma config BORV=190         // Brown-out voltage 1.9V
//#pragma config PWRTEN=ON        // Power up timer enabled
#pragma config WDTEN=OFF        // WDT off
//#pragma config MCLRE=EXTMCLR    // external MCLR pin enabled

//#define MAX_STRLEN 14
//char received_string[MAX_STRLEN+1];

void _delay_10ms(int length){
    while(length){
        __delay_ms(10);
        length--;
    }
}

int main(void){
    
    unsigned char payload[wl_module_PAYLOAD];
    unsigned char maincounter =0;
    unsigned char k=0;
    
    TRISAbits.RA1 = 0; //Set PortA Bit 0 as Output
    
    wl_module_init();  //initialize the nRF24L01+ Module
    _delay_10ms (5);   //wait for nRF24L01+ Module
    
    INTCONbits.PEIE =1; //peripheral interrupts enable
    INTCONbits.GIE =1;  //global interrupt enable
    
    wl_module_tx_config(wl_module_TX_NR_0); //config module
   // wl_module_set_tx_addr(wl_module_TX_NR_0,wl_module_PAYLOAD); //set the TX address in the TX_ADDR register
    //wl_module_set_as_tx(); //set up the 24L01 as a transmitter
    //wl_module_set_TADDR(wl_module_TX_NR_0); //set the transmitting address
    while (1)
    {
        LATAbits.LATA1 = ~LATAbits.LATA1;
        
        //Create a 1 second delay loop
        for (k=0; k<wl_module_PAYLOAD-1; k++)
        {__delay_ms(5);
        payload[k]=k;
        }
    payload[0]=maincounter;
    payload[1]=maincounter+1;
    
    wl_module_send(payload,wl_module_PAYLOAD);
    
    }
   /* while (1)
    {
     convertedValue = 0;
     ADC_StartConversion(channel_AN0);
     while (!ADC_IsConversionDone());
     convertedValue = ADC_GetConversionResult();
     
     for (k=0; k<=wl_module_PAYLOAD-1; k++)
         k=convertedValue*5/1023;   
         hall[k] = k;
     
     wl_module_send(hall,wl_module_PAYLOAD);
    }*/
    
    return 0;
}

void interrupt ISR(void){
    // external interrupt IRQ pin of NRF24L01
    if( INTCON3bits.INT2IF ){
        unsigned char status;

        // Read wl_module status
        wl_module_CSN_lo; // Pull down chip select
        status = spi_fast_shift(NOOP); // Read status register
        wl_module_CSN_hi; // Pull up chip select


        if (status & (1<<TX_DS)){ // IRQ: Package has been sent
                    wl_module_config_register(STATUS, (1<<TX_DS)); //Clear Interrupt Bit
                    PTX=0;
        }

	if (status & (1<<MAX_RT)){ // IRQ: Package has not been sent, send again
		wl_module_config_register(STATUS, (1<<MAX_RT));	// Clear Interrupt Bit
		wl_module_CE_hi; // Start transmission
		__delay_us(10);
		wl_module_CE_lo;
	}

	if (status & (1<<TX_FULL)){ //TX_FIFO Full <-- this is not an IRQ
		wl_module_CSN_lo; // Pull down chip select
		spi_fast_shift(FLUSH_TX); // Flush TX-FIFO
		wl_module_CSN_hi; // Pull up chip select
	}
        // reset INT2 flag
        INTCON3bits.INT2IF = 0;
    }
}
