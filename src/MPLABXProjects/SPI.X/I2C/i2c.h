//------------------------------------------------------------------------------
// File:          i2c.h
// Written By:    E.G. Walters
// Date Created:  14 Jan 15
// Description:   Header file for I2C communications
// Compiler:	  XC32 v1.33
// Target:        PIC32MX320F128H (Digilent chipKIT Uno32 board)
// Schematic(s):  Digilent schematics for Uno32 board
//
// Revision History (date, initials, description)
//   20 Mar 18, egw100, Updated for SP18
//------------------------------------------------------------------------------
#ifndef I2C_H
#define	I2C_H


// Includes
#include <xc.h>
#include <stdint.h>
#include <sys/attribs.h>
//#define _SUPPRESS_PLIB_WARNING
//#include <plib.h>


// Defines


// Function prototypes
void       I2C_Init(void);
//I2C_RESULT I2C1_Start(void);
//void       I2C1_Stop(void);
//I2C_RESULT I2C1_Restart(void);
//I2C_RESULT I2C1_SendByte(uint8_t data);
//uint8_t    I2C1_ReceiveByte(void);
//void       I2C1_WriteRegister(uint8_t slaveAddress, uint8_t registerAddress,
//               uint8_t data);
//uint8_t    I2C1_ReadRegister(uint8_t slaveAddress, uint8_t registerAddress);


#endif	/* I2C_H */

