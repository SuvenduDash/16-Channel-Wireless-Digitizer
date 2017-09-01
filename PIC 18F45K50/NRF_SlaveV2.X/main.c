/*
 * File:   main.c
 * Author: BRNS1
 *
 * Created on May 25, 2017, 2:47 PM
 */


#define _XTAL_FREQ 16000000UL
#include <xc.h>
#include <stdlib.h>
#include "spi.h"
#include "nRF24L01.h"
#include "wl_module.h"
#include "lcd.h"
#include <stdio.h>
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

#define MAX_STRLEN 14
char received_string[MAX_STRLEN+1];

void _delay_10ms(int length){
    while(length){
        __delay_ms(10);
        length--;
    }
}

int main(void){
    //unsigned char payload[wl_module_PAYLOAD]; //holds the payload
    unsigned char hall[wl_module_PAYLOAD];
    unsigned char nRF_status; //STATUS information of nRF24L01+
    unsigned char zaehler = 0;
    char Buffer[20];
    // Initialize the device
    SYSTEM_Initialize();
    
    wl_module_init(); //Init nRF Module
    _delay_10ms(5); //wait for Module
    
    //initialize the LCD
    LCD_Initialize();
    
    LCDPutCmd(LCD_CURSOR_OFF);   //LCD Cursor off
        
    // configure output port
    //TRISD &= ~(0x0F);
    //LATD |= 0x0F;

    INTCONbits.PEIE = 1; // peripheral interrupts enabled
    INTCONbits.GIE = 1;  // global interrupt enable

    wl_module_config();	//config nRF as RX Module, simple Version

    while(1){
        while (!wl_module_data_ready()); //waits for RX_DR Flag in STATUS
        nRF_status = wl_module_get_data(hall); //reads the incomming Data to Array payload
	zaehler = hall[0];
    LCDPutStr("Hall Value. = ");
     sprintf(Buffer, "%.3g", zaehler);
     LCDPutStr(Buffer);
     LCDGoto(0,0);
        //LATD |= 0x0F;
        //LATD &= ~(payload[0]);
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
