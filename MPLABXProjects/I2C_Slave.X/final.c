/***********************************************************************
 * PIC32 I2C Slave Code                
 ***********************************************************************/

//#include "GenericTypeDefs.h"
//#include "Compiler.h"
//#include "HardwareProfile.h"
//#include "plib.h"
#include "final.h"

#define SYSCLK	(80000000)
#define PBCLK  (SYSCLK)

#define Fsck	50000
#define BRG_VAL 	((PBCLK/2/Fsck)-2)

// this is the modules Slave Address
#define SLAVE_ADDRESS 0x40

// volatile variables to hold the switch and led states
volatile unsigned char dataRead = 0;

///////////////////////////////////////////////////////////////////
//
//	InitI2C
//
// 	Perform initialisation of the I2C module to operate as a slave
//
///////////////////////////////////////////////////////////////////
void InitI2C(void)
{
	unsigned char temp;
	
	// Enable the I2C module with clock stretching enabled
	OpenI2C1(I2C_ON | I2C_7BIT_ADD | I2C_STR_EN, BRG_VAL);
	
	// set the address of the slave module, address matching is with bits
	// 7:1 of the message compared with bits 6:0 of the ADD SFR so we
	// need to shift the desired address 1 bit. 
	I2C1ADD = SLAVE_ADDRESS; // >> 1;
	I2C1MSK = 0;
	
	// configure the interrupt priority for the I2C peripheral
	mI2C1SetIntPriority(I2C_INT_PRI_3 | I2C_INT_SLAVE);

	// clear pending interrupts and enable I2C interrupts
	mI2C1SClearIntFlag();
	EnableIntSI2C1;
}

///////////////////////////////////////////////////////////////////
//
//	main routine
// 
//	This code example demonstrates using the PIC32 as an I2C slave
//	
//
///////////////////////////////////////////////////////////////////
int main (void)
{
	// set for 80MHz operation
	SYSTEMConfigPerformance(SYSCLK);
	// set the Pbus to be 40000000
	mOSCSetPBDIV(OSC_PB_DIV_2);
	// disable the JTAG port
	mJTAGPortEnable(0);
	// enable interrupts
	INTEnableSystemMultiVectoredInt();
	
	InitI2C();

	// main loop
	while (1) {
		/* If global variable "dataRead" is set high during interrupt, turn on all LEDs */
		if (dataRead == 0xAA)
		{
		
			
		}
	}
}

///////////////////////////////////////////////////////////////////
//
// Slave I2C interrupt handler
// This handler is called when a qualifying I2C events occurs
// this means that as well as Slave events 
// Master and Bus Collision events will also trigger this handler.
//
///////////////////////////////////////////////////////////////////
void __ISR(_I2C_1_VECTOR, ipl3) _SlaveI2CHandler(void)
{
	unsigned char temp;
	static unsigned int dIndex;
	
	// check for MASTER and Bus events and respond accordingly
	if (IFS0bits.I2C1MIF == 1) {
		mI2C1MClearIntFlag();
		return;		
	}
	if (IFS0bits.I2C1BIF == 1) {
		mI2C1BClearIntFlag();
		return;
	}
	
	// handle the incoming message
	if ((I2C1STATbits.R_W == 0) && (I2C1STATbits.D_A == 0)) {
		// R/W bit = 0 --> indicates data transfer is input to slave
		// D/A bit = 0 --> indicates last byte was address  
		
		// reset any state variables needed by a message sequence	
		// perform a dummy read of the address
		temp = SlaveReadI2C1();
		
		// release the clock to restart I2C
		I2C1CONbits.SCLREL = 1; // release the clock

	} else if ((I2C1STATbits.R_W == 0) && (I2C1STATbits.D_A == 1)) {
		// R/W bit = 0 --> indicates data transfer is input to slave
		// D/A bit = 1 --> indicates last byte was data
		
		// writing data to our module, just store it in adcSample
		dataRead = SlaveReadI2C1();
		
		// release the clock to restart I2C
		I2C1CONbits.SCLREL = 1; // release clock stretch bit

	} else if ((I2C1STATbits.R_W == 1) && (I2C1STATbits.D_A == 0)) {
		// R/W bit = 1 --> indicates data transfer is output from slave
		// D/A bit = 0 --> indicates last byte was address

		// read of the slave device, read the address 
		temp = SlaveReadI2C1();
		dIndex = 0;
		SlaveWriteI2C1(dataRead);
	} else if ((I2C1STATbits.R_W == 1) && (I2C1STATbits.D_A == 1)) {
		// R/W bit = 1 --> indicates data transfer is output from slave
		// D/A bit = 1 --> indicates last byte was data

		
		// output the data until the MASTER terminates the
		// transfer with a NACK, continuing reads return 0
		if (dIndex == 0) {
			SlaveWriteI2C1(dataRead);
			dIndex++;
		} else
			SlaveWriteI2C1(0);
	}
	
	// finally clear the slave interrupt flag
	mI2C1SClearIntFlag();		
}