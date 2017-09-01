/*
 * File:   main.c
 * Author: BRNS1
 *
 * Created on May 25, 2017, 2:47 PM
 */


//#define _XTAL_FREQ 16000000UL
#include <xc.h>
#include <stdlib.h>
#include "spi.h"
#include "nRF24L01.h"
#include "wl_module.h"
//#include "lcd.h"
#include <stdio.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"

#pragma config IESO=OFF         // Oscillator Switchover mode disabled
//#pragma config FOSC=HSMP        // external medium power oscillator
//#pragma config PRICLKEN=OFF     // Primary clock can be disabled by software
#pragma config FCMEN=ON         // Fail-Safe Clock Monitor enabled
//#pragma config PLLCFG=OFF       // disable 4xPLL
//#pragma config BOREN=SBORDIS    // disable software BOR
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
    unsigned char nRF_status;
    unsigned char data =0;
    wl_module_init(); //init nRF module
    _delay_10ms(5);  //wait for module
    
   INTCONbits.PEIE =1; //peripheral interrupts enable
   INTCONbits.GIE =1;  //global interrupt enable
   
   wl_module_config(); //config nRF as RX Module
   //wl_module_set_rx_addr(wl_module_TX_NR_0,wl_module_PAYLOAD, 0);
   //wl_module_get_rx_addr(wl_module_TX_NR_0,wl_module_PAYLOAD, 0);
   //wl_module_set_RADDR(wl_module_TX_NR_0); //set the receiving address
   
   while(1)
   {
       while(!wl_module_data_ready());  //wait for RX_DR flag in status
       nRF_status = wl_module_get_data(payload);   //read the incomming data to array payload
       data =payload[0];
   }
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
