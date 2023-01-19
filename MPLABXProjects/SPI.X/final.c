
//------------------------------------------------------------------------

// File:          final.c
// Written By:    Mike Deleo
// Date Created:  03 March 18
// Description:   Interfacing a TFT graphics screen to an MCU using an SPI
// Compiler:       XC32 v1.34
// Target:        PIC32MX340F512H
// Schematic(s):  Drawing L06-01
//
// Revision History (date, initials, description)
//   NONE
//   
//   
//------------------------------------------------------------------------------

/*INTERRUPt NOTES*/
/*The Interrupts module consists of the following Special Function Registers (SFRs):
? INTCON:InterruptControlRegister
? PRISS:PriorityShadowSelectRegister
? INTSTAT:InterruptStatusRegister
? IPTMR:InterruptProximityTimerRegister
? IFSx:InterruptFlagStatusRegister
? IECx:InterruptEnableControlRegister
? IPCx:InterruptPriorityControlRegister
? OFFx:InterruptVectorAddressOffsetRegister*/

#include "final.h"
//#include "plib.h"

//uint8_t GPIO_B1 = 0;
//uint8_t GPIO_B2 = 0;

//Array of data that is written to
uint16_t Analog_In[4] = {5000, 5005, 250, 500}; //implied decimal of 1000. most it can be is 4 decimals
uint16_t Analog_Out[8] = {1000, 5000, 250, 500,1000, 5005, 250, 500}; //implied decimal of 1000
uint8_t Digital_In[2] = {0b00000000, 0b00000000};
uint8_t Digital_Out[2] = {0b0000000, 0b00000000};

//------------------------------------------------------------------------------
// Function: main()
//------------------------------------------------------------------------------
void main(void) {

    MCU_initialize();
    
    
    //essentially here is what's going on. 
    //A. There is the main thread, which goes in a loop. It executes four things,
    //there are four locks. one lock per group. And a temporary set of each data
    //This thread is in charge of SPI 1 which is a master. Waits if any lock is already locked
        //1. ADC
        //2. DAC
        //3. first i/o expander
        //4. second i/o expander
    //B. There is a child of the main thread. This is in charge of SPI 2 which
    //is a slave to the PI. Whenever the pi requests the data, this thread gives
    //anything that is currently not being written to. Then if something is being
    //written to, then it takes the temporary variable. It will also update the
    //temporary variable of each.
    


    
    //There are keys that are sent for the specific values
    while(1){
        SPIStuff();
        Send_Analog_In();
        //printf("A");
        //printf("%d",data[0]);
        //printf("%d",data[1]);
    }
    uint8_t buffer;
    //check_status(pthread_create(&slave,NULL,slave_routine,NULL));
    I2C1CONbits.ON = 1;
    while(1){
        I2C1TRN = 0b11001100;
        I2C1CONbits.SCLREL = 1;    /* Release the clock */
    }
    while(1){
        IFS0 = 0;
        SPIStuff();
        
        I2C1CONbits.ON = 1;
        //Turn on the I2C module to check if it is being communicated to
        while(I2C1STATbits.S == 0){} //While the SDA line is pulled down for any reason
        //printf("Start condition");
        
        // 1. Turn on the I2C module by setting the ON bit (I2CxCON<15>) to ?1?.
        //I2C1CONbits.ON = 1; // I2C Enable bit                               -> Enables the I2C module and configures the SDAx and SCLx pins as serial port pins

        
//        b =  smBus.SMBus(1);
//        b.readByte(addr);
        
        //I2C1CONbits.i = 1;
        //------------- WRITE begins here ------------
        // 2. Assert a Start condition on SDAx and SCLx.
        //I2C1CONbits.PEN = 0; // Stop Condition Enable Bit                    -> Stop Condition Idle 
        //I2C1CONbits.SEN = 1; // Start Condition Enable bit                   -> Initiate Start condition on SDAx and SCLx pins; cleared by module
        //while (I2C1CONbits.SEN == 1); // SEN is to be cleared when I2C Start procedure has been completed 

        
        while (I2C1STATbits.R_W == 1 && I2C1STATbits.D_A == 1){};
        I2C1CONbits.ACKEN = 1;
        //buffer = I2C1RCV;
        buffer = I2C1ADD;
        if (buffer != 0){
            buffer;
        }
        if (buffer == I2C1ADD){
            //printf("Match %X", I2C1ADD);
            I2C1CONbits.ACKEN = 1;
        }
        else{
            printf("Not a match %X != %X",buffer,I2C1ADD);
        }
        
        // 3. Load the Data on the bus
        /*I2C1TRN = 0b10100000; // Write the slave address to the transmit register for I2C WRITE 
        while (I2C1STATbits.TRSTAT == 1); // MASTER Transmit still in progress
        while (I2C1STATbits.ACKSTAT == 1); // Master should receive the ACK from Slave, which will clear the I2C1STAT<ACKSTAT> bit. 

        I2C1TRN = 0xCE; // Register Address 
        while (I2C1STATbits.TRSTAT == 1);
        while (I2C1STATbits.ACKSTAT == 1);

        I2C1TRN = 0xCF; // Register Value 
        while (I2C1STATbits.TRSTAT == 1);
        while (I2C1STATbits.ACKSTAT == 1);
        I2C1CONbits.PEN = 1; // Stop Condition Enable Bit                    -> Initiate Stop condition on SDAx and SCLx pins; cleared by module
*/
        //-------------- WRITE ends here -----------
    }
    
    

    //TFT_FillRectangle(0, 0, 255, 350, TFT_BLUE);
    /*while(1) {

        GPIO_B1 = 0;
        GPIO_B2 = 0;
        uint8_t data = SPI2_ReadByte(0x09);
        GPIO_B1 = 0b00000001 & data;
        if (GPIO_B1 == 0){  //invert the first bit of the button 1
            GPIO_B1 = 1;
        }
        else{
            GPIO_B1 = 0;
        }
        GPIO_B2 = 0b00000010 & data;
        if (GPIO_B2 == 0){ //invert the first bit of the button 2
            GPIO_B2 = 1;
        }
        else{
            GPIO_B2 = 0;
        }
        // if both buttons are pressed, turn on LED
        if (GPIO_B1 == 1 && GPIO_B2 == 1){
            CS = 0;
            SPI2_TransmitByte(0b01000000);
            SPI2_TransmitByte(0x09);
            SPI2_TransmitByte(0b11111111);
            CS = 1;
            //TFT_DrawRectangle(65, 170, 80, 40, TFT_RED);
            //TFT_DrawString(68,172,"^o^",TFT_YELLOW, TFT_BLUE,4);
            //TFT_DrawString(70,175,"^_^",TFT_YELLOW, TFT_BLUE,4);
            //TFT_DrawString(16,215,"lil led - 'I LIVE!'", TFT_YELLOW, TFT_BLUE, 2);
        }
        // else, turn it off
        else{
            CS = 0;
            SPI2_TransmitByte(0b01000000);
            SPI2_TransmitByte(0x09);
            SPI2_TransmitByte(0b00000000);
            CS = 1;
            //TFT_DrawRectangle(65, 170, 80, 40, TFT_BLACK);
            //TFT_DrawString(70,175,"X_X",TFT_BLACK, TFT_BLUE,4);
            //TFT_DrawString(16,215,"lil led - *DED*     ", TFT_YELLOW, TFT_BLUE, 2);
        }

        //names
        //TFT_DrawString(5, 34, "CMPEN 352 - Lab 6", TFT_YELLOW, TFT_BLUE, 2);
        //TFT_DrawString(5, 50, "Mike DeLeo", TFT_YELLOW, TFT_BLUE, 2);
        //TFT_DrawString(5, 66, "Morayo Ogunsina", TFT_YELLOW, TFT_BLUE, 2);



    }
*/
} // end main()


//------------------------------------------------------------------------------
// Function: MCU_initialize()
// Params:   void
// Returns:  void
// Initialization code for the application
//------------------------------------------------------------------------------
void MCU_initialize(void) {
     //unsigned int val;
    // set the CP0 cause IV bit high
     
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));
    
    unsigned int status = 0;

    asm volatile("ei    %0" : "=r"(status));
    INTCONSET = _INTCON_MVEC_MASK;
    // set the CP0 status IE bit high to turn on interrupts

//    dataCursor = 0;
    //INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    //tels cpu to enter multi-vector mode, and sets intcon(12)
    // Configure oscillators
    OSCCONbits.PBDIV = 0b11;  // PBCLK is SYSCLK/8 = 10 MHz
    // Init UART 1 to communicate with PC
    U1MODEbits.UEN = 0b00;
    U1MODEbits.PDSEL = 0b00;  // 8-bit data, no parity
    U1MODEbits.STSEL = 0;  // 1 stop bit
    U1BRG = 64;  // PBCLK = 10 MHz so Baud rate = 9600
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;  // Turn on UART
    printf("\n\n---------------\nUART Configured\n  Hello TTY!\n---------------\n");
    
    // Use multi-vector interrupt mode
    INTCONbits.MVEC = 1; //multi-vector configuration bit
    
    //sets intcon bit 12 to high
    //might still have to set vector mode
    
    /*
        The following code example will set INT3 to trigger on a high-to-low 
     * transition edge. The CPU must be set up for either multi or single vector
     * interrupts to handle external interrupts
    */
    INTCONbits.INT1EP = 0;  //set external priority of interrupt 1 to rising edge
    
    //IEC0CLR = 0x00000080;    // disable INT1
    //INTCONCLR = 0x00000008;    // clear the bit for falling edge trigger
    //IFS0CLR = 0x00008000;    // clear the interrupt flag
    //IEC0SET = 0x00008000;    // enable INT3


    // Configure tristates
    TRISF |= 0b1111011;      //set to input
    TRISGbits.TRISG6 = 0;
    TRISGbits.TRISG7 = 1;
    TRISGbits.TRISG8 = 0;
    TRISDbits.TRISD1 = 0;
    TRISGbits.TRISG2 = 1;
    TRISGbits.TRISG3 = 1;

        //TIMER 4
    T4CON = 0x00; // Disable timer, prescale = 1:1, source =PBCLK
    T4CONbits.ON = 1; // enable timer

    AD1PCFG = 0xffff; //Tristates

    //SPI_Init();      // initialize SPI
    LCD_initialize();
    I2C_Init();
    //TFT_Init();      // initialize tft
    
    __builtin_enable_interrupts(); 

} // end MCU_initialize()

//------------------------------------------------------------------------------
// Function: _mon_putc()
// Params:   c; character to send to stdout
// Returns:  void
// Redfine _mon_putc so stdout goes to UART
//------------------------------------------------------------------------------
/*void *slave_routine(void *args){
    //wait for the SS to go low. Then send data
    //do service for the pi
    
    //CAUTION: This thread may be called with the interrupt handler...maybe fix that
    while(1){}
}*/

//------------------------------------------------------------------------------
// Function: _mon_putc()
// Params:   c; character to send to stdout
// Returns:  void
// Redfine _mon_putc so stdout goes to UART
//------------------------------------------------------------------------------
void _mon_putc (char c) {

    while(U1STAbits.UTXBF);  // wait for transmit buffer to be available
        U1TXREG = c;
} // end _mon_putc()


//-----------------------------------------------------------------------------
//Precondition: milliseconds up to 1000ms
//Postcondition: nothing
//Function: delays for number of milliseconds
//----------------------------------------------------------------------------
void msDelay(uint16_t delay){
    uint16_t i = 0;
    while (i < delay){
        delay_one_ms();
        i++;
    }
    return;
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function: delays one millisecond
//----------------------------------------------------------------------------
void delay_one_ms(){
    TMR4 = 0; // Initialize Timer4 value
    while (TMR4 < 1000); // Wait until Timer4 has counted 10000 times
    return;//will return upon 1ms
}

/*void __ISR(_Timer_1_Vector, IPL7SOFT){
    //Check flags and call appropriate handlers
    if (TMR0IE && TIMER0_FLAG)
    {
        //CAll time 0 handler
        Timer0Handler();
    }
    else if (TMR0IE && TIMER1_FLAG){
        Timer1Handler();
    }
    return;
}

void Timer0Handler(){
    
}

void Timer1Handler(){
    
}
//Vector is the vector number referenced in the IRQ table
void __ISR(_I2C1_SLAVE_IRQ, IPL7SRS) handler(){
    if (IFS0bits.I2C1SIF == 1 && IEC0bits.I2C1SIE == 1){
        I2CSlaveSender();
        //_CORE_TIMER_VECTOR;
    }
}

void __ISR(_I2C_1_VECTOR, IPL6AUTO) handler2(){
    printf("second interrupt");
}

void I2CSlaveSender(){
        //Interrupt is for sending
    I2C1STATbits.S = 0; //reset start bit flag
    IFS0bits.I2C1SIF = 0; // reset slave interrupt
    I2C1CONbits.SCLREL = 0;
    I2C1TRN = data[dataCursor]; //write data to output register
    dataCursor++;
    if (dataCursor >= 2){
        dataCursor = 0;
    }
    msDelay(10);
    //    bufferFull = 1;
    I2C1CONbits.SCLREL = 1;
}
*/
void SPIStuff(){
    return;
}

//Format for sending messages. 
//1. The first byte is the key for which data line is being sent
//a: Analog to the MCU - 4 channels (16 bit integer, 1000 implied decimal, 4 digits at most)
//A: Analog to the PLC - 8 channels (16 bit integer, 1000 implied decimal, 4 digits at most)
//d: Digital to MCU - 16 channels (binary)
//D: Digital to PLC - 16 channels  (binary)

//2. If it is analog then the pi is expecting four bytes for each number


void Send_Analog_In(){
    printf("a");    //key for the analog
    uint8_t i = 0;

    
    while(i < 4){
        uint8_t zeros = Digits(Analog_In[i]);
        //buffer in the zeros for the uart
        while (zeros > 0){
            printf("0");
            zeros--;
        }
        //send the number
        printf("%d",Analog_In[i]);
        i++;
    }
    
    
    return;
}

uint8_t Digits(uint16_t num){
    if (num < 10){
        return 1;
    }
    if (num < 100){
        return 2;
    }
    if (num < 1000){
        return 3;
    }
    if (num < 10000){
        return 4;
    }
    else{
        return 0;
    }
}