//------------------------------------------------------------------------------
// File:          spi.h
// Written By:    E.G. Walters
// Date Created:  7 Oct 15
// Description:   Header file for SPI communications
// Compiler:	  XC32 v1.34
// Target:        PIC32MX340F512H (Digilent chipKIT uC32 board)
// Schematic(s):  Digilent schematics for uC32 board
//
// Revision History (date, initials, description)
//   27 Feb 18, egw100, Updated for SP18
//   13 Mar 18, mad6068,Updated for use in lab6 (TFT and SPI)
//MODIFIED BY: Mike DeLeo
//------------------------------------------------------------------------------
#ifndef SPI_H
#define	SPI_H

// Includes
#include <xc.h>
#include <stdint.h>

    #define CS    PORTDbits.RD1    // Chip select pin
    

    // Function prototypes
    void    SPI_Init(void);
    uint8_t SPI2_TransmitByte(uint8_t bVal);
    uint8_t SPI2_ReadByte(uint8_t reg);
    uint8_t SPI1_ReadByte();


#endif	/* SPI_H */

