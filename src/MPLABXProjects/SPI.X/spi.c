//------------------------------------------------------------------------------
// File:          spi.c
// Written By:    E.G. Walters
// Date Created:  7 Oct 15
// Description:   C file for SPI communications
// Compiler:	  XC32 v1.34
// Target:        PIC32MX340F512H (Digilent chipKIT uC32 board)
// Schematic(s):  Digilent schematics for uC32 board
//
// Revision History (date, initials, description)
//   27 Feb 18, egw100, Updated for SP18
//MODIFIED BY: Mike DeLeo
//------------------------------------------------------------------------------

/*
 * The following steps are used to set up the SPI module for the Slave mode of operation:

 * If using interrupts, disable the SPI interrupts in the respective IECx register.

 * Stop and reset the SPI module by clearing the ON bit.

 * Clear the receive buffer.

 * Clear the ENHBUF bit (SPIxCON<16>) if using Standard Buffer mode or set the bit if using Enhanced Buffer mode.

 * If using interrupts, the following additional steps are performed:
a) Clear the SPIx interrupt flags/events in the respective IFSx register.
b) Write the SPIx interrupt priority and subpriority bits in the respective IPCx register.
c) Set the SPIx interrupt enable bits in the respective IECx register.

 * Clear the SPIROV bit (SPIxSTAT<6>).

 * Write the desired settings to the SPIxCON register with MSTEN (SPIxCON<5>) = 0. 
 * 
 * Enable SPI operation by setting the ON bit (SPIxCON<15>).

 * Transmission (and reception) will start as soon as the master provides the serial clock.*/



#include "spi.h"



//------------------------------------------------------------------------------
// Function: SPI_Init()
// Params:   void
// Returns:  void
// This function should be called in the main initialization routine to
// initialize SPI 2.
//------------------------------------------------------------------------------
void SPI_Init(void) {
    
    //the other option is using the external interrupt 
    /*
The following code example will set INT3 to trigger on a high-to-low transition edge. The CPU must be set up for either multi or single vector interrupts to handle external interrupts

IEC0CLR = 0x00008000;
INTCONCLR = 0x00000008;
IFS0CLR = 0x00008000;
IEC0SET = 0x00008000;
// disable INT3
// clear the bit for falling edge trigger
// clear the interrupt flag
// enable INT3*/
    
    //TODO setup tris pins
    /*
    uint8_t rdata = 0;
    SPI1CONbits.ON = 0;
    IEC0CLR=0x03800000;
    SPI1CON = 0;
    rData=SPI1BUF;
    IFS0CLR=0x03800000;
    IPC5CLR=0x1f000000;
    IPC5SET=0x0d000000;
    IEC0SET=0x03800000;
    //sets interrupt for spi1 fault,transfer done, buffer full
    SPI1STATCLR=0x40;
    SPI1CON=0x8000;*/
// disable all interrupts
// Stops and resets the SPI1.
// clears the receive buffer
// clear any existing event
// clear the priority
// Set IPL=3, Subpriority 1
// Enable RX, TX and Error interrupts
// clear the Overflow
// SPI ON, 8 bits transfer, Slave mode
    SPI1BRG = 0; //5MHz with 10MHz PB clock
    SPI1CONbits.SMP = 1; //data sampled at end
    SPI1CONbits.CKP = 0; //clock polarity
    SPI1CONbits.CKE = 1; //clock edge to send
    SPI1CONbits.MSTEN = 0;  //slave mode
    SPI1CONbits.ON = 1; //spi peripheral on
    

    SPI2CON = 0;
    SPI2BRG = 0; // 5Mhz with 10Mhz PB clock
    SPI2STATbits.SPIROV = 0;
    SPI2CONbits.CKP = 0;
    SPI2CONbits.CKE = 1;
    SPI2CONbits.SMP = 1;
    SPI2CONbits.MSTEN = 1;
    SPI2CONbits.ON = 1;

    CS = 0;
    SPI2_TransmitByte(0b01000000);  //opcode for write
    SPI2_TransmitByte(0x00);        //address for IODIR
    SPI2_TransmitByte(0b11111011);  //set all pins to po
    CS = 1;
} // end SPI_Init()



//------------------------------------------------------------------------------
// Function: SPI_TransmitByte()
// Params:   bVal; the byte to transmit
// Returns:  the byte received
// Transmits one byte using the SPI #2 peripheral
//------------------------------------------------------------------------------
uint8_t SPI2_TransmitByte(uint8_t bVal) {

    // Wait for transmit buffer to be empty (ready to send new byte)
    while (SPI2STATbits.SPITBE == 0);

    // Put the byte in the transmit buffer (Transmit the byte)
    SPI2BUF = bVal;
    
    //uint8_t res = SPI1BUF;

    // Wait for receive buffer to be full (new byte has been received)
    while (SPI2STATbits.SPIRBF == 0);

    // Return the received byte
    return SPI2BUF;

} // end SPI_TransmitByte()

//------------------------------------------------------------------------------
// Function: SPI_ReadByte()
// Params:   reg; the register address to select
// Returns:  the byte recieved
//------------------------------------------------------------------------------
uint8_t SPI2_ReadByte(uint8_t reg){
    CS = 0;

    SPI2_TransmitByte(0b01000001);

    SPI2_TransmitByte(reg);

    uint8_t data = SPI2_TransmitByte(0);
    CS = 1;
    
    return data;
}

uint8_t SPI1_ReadByte(){
    //Wait for receive buffer to be full (byte received)
    while(SPI1STATbits.SPIRBF = 0);
    return SPI1BUF;
}