/*
 * File:   spi.c
 * Author: BRNS1
 *
 * Created on May 25, 2017, 2:47 PM
 */


#include <xc.h>
#include "spi.h"

void spi_init(void){
    // disable MSSP
    SSP1CON1bits.SSPEN = 0;
    // SDI1 set
    TRISBbits.TRISB0 = 1; 
    // TRISCbits.TRISC4 = 1; // configure RC4 as input
    //ANSELCbits.ANSC4 = 0; // enable digital input buffer on RC4
    ANSELBbits.ANSB0 =0;  //enable digital input buffer on RC2
    // SS1 set
    TRISAbits.TRISA5 = 1; //Define chip select as output
    // SDO1 cleared
    // SCK1 cleared
    //TRISCbits.TRISC5 = 0; //Define SDO as Output
    TRISCbits.TRISC7 = 0;
    //TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC6 = 0; //Define clock pin as output
    

    // SPI mode 0
    SSP1CON1bits.CKP = 0; // Idle state for clock is a low level
    SSP1STATbits.CKE = 1; // Transmit occurs on transition from active to Idle clock state
    SSP1STATbits.SMP = 1; // Input data sampled at end of data output time (took me 5 friggin' hours)
    SSP1CON1bits.SSPM = 0; // SPI Master mode, SCK = FOSC/4
    SSP1CON1bits.SSPEN = 1; // enable MSSP1
}

void spi_transmit_sync(unsigned char * data, unsigned int length){
    unsigned char tmp;
    while(length){
	SSP1BUF = *data;
	while( !PIR1bits.SSP1IF ); // wait for buffer full
        PIR1bits.SSP1IF = 0; // clear SSP1IF
        tmp = SSP1BUF; // read out data
        length--;
	data++;
    }
}

void spi_transfer_sync(unsigned char * dataout, unsigned char * datain, unsigned int length){
    while(length){
	SSP1BUF = *dataout;
	while( !PIR1bits.SSP1IF ); // wait for buffer full
        PIR1bits.SSP1IF = 0; // clear SSP1IF
        *datain = SSP1BUF; // read out data
        length--;
	dataout++;
        datain++;
    }
}

unsigned char spi_fast_shift(unsigned char data){
    SSP1BUF = data;
    while( !PIR1bits.SSP1IF ); // wait for buffer full
    PIR1bits.SSP1IF = 0; // clear SSP1IF
    return SSP1BUF;
}