/* 
 * File:   lab08.c
 * Author: MAD6068
 *
 * Created on March 21, 2018, 7:21 PM
 */


#include "lab082.h"

uint8_t GPI0_B1 = 0;
uint8_t GPI0_B2 = 0;

//------------------------------------------------------------------------------
// Function: main()
//------------------------------------------------------------------------------
void main(void) {

    MCU_initialize();
    DrawMenu();
    MCP23008_INIT();
    // config CTRL_REG 1
    I2C1_WriteRegister(0x19,0x20, 0b01000111);
    // config CTRL_REG 4 to use block update
    I2C1_WriteRegister(0x19, 0x23, 0b10000000);
    // set range to +/- 2g range, done above^^

    uint8_t who = I2C1_ReadRegister(0x19,0x0F);

    while(1) {
       if (!TOUCH_BufferIsEmpty()){
           TOUCH_GetTouchPoints();

           // Go to main screen
           if((touch_x >= 21 && touch_x <= 86) && (touch_y >= 244 && touch_y <= 293)){
               GoToMain();
           }

           // Go to 23008 Screen
           else if((touch_x >= 90 && touch_x <= 152) && (touch_y >= 244 && touch_y <= 293)){

               GoTo23008();
           }

           //Go to LIS3DH screen
           else if((touch_x >= 158 && touch_x <= 227) && (touch_y >= 244 && touch_y <= 293)){

               GoToLIS3DH();
          }
       }
    }

} // end main()


//------------------------------------------------------------------------------
// Function: MCU_initialize()
// Params:   void
// Returns:  void
// Initialization code for the application
//------------------------------------------------------------------------------
void MCU_initialize(void) {
    // Use multi-vector interrupt mode
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    // Configure oscillators
    OSCCONbits.PBDIV = 0b11;  // PBCLK is SYSCLK/8 = 10 MHz

    // Init UART 1 to communicate with PC
    U1MODEbits.UEN = 0b00;
    U1MODEbits.PDSEL = 0b00;  // 8-bit data, no parity
    U1MODEbits.STSEL = 0;  // 1 stop bit
    U1BRG = 10;  // PBCLK = 10 MHz so Baud rate = 9600
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;  // Turn on UART
    printf("\n\n---------------\nUART Configured\n  Hello TTY!\n---------------\n");


    // Configure Timer1 to interrupt every 1 ms
    T1CON = 0x00; // Disable timer, prescale = 1:1, source = PBCLK
    TMR1 = 0;     // Clear timer count
    PR1 = 10000;  // PBCLK is 10 MHz, so 10 000 counts = 1 kHz
    IPC1bits.T1IP = 7; // Interrupt priority = 7 (highest priority)
    IPC1bits.T1IS = 3; // Subpriority = 3 (highest)
    IFS0bits.T1IF = 0; // Clear interrupt flag
    IEC0bits.T1IE = 1; // Enable interrupt
    T1CONbits.ON = 1;  // Enable timer

   // Configure tristates
    TRISF |= 0b1111011;      //set to input
   // TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 1;
    TRISFbits.TRISF1 = 1;
    TRISDbits.TRISD0 = 1;
    LD5_TRIS = TRIS_OUTPUT; // Set pin to output
    //TIMER 4
    T4CON = 0x00;           // Disable timer, prescale = 1:1, source =PBCLK
    T4CONbits.ON = 1;       // enable timer
    AD1PCFG = 0xffff;       //Tristates
    SPI_Init();             // initialize SPI
    I2C_Init();
    TOUCH_Init();           // initialize TOUCH
    TFT_Init();             // initialize tft

    INTEnableInterrupts();
}  // end MCU_initialize()


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

void MCP23008_INIT(){
    I2C1_WriteRegister(MCP_ADDR, 0x00, 0xF3);   //sets the gp ports; last bit for led output, next 2 for button inputs
    return;
}

uint8_t MCP23008_GetValues(){
    return I2C1_ReadRegister(MCP_ADDR, 0x09);
}

void MCP23008_WriteValues(uint8_t data){
    I2C1_WriteRegister(MCP_ADDR, 0x0A, data);
    return;
}

void LIS3DH_INIT(){
    //TODO
}

uint8_t LIS3DH_GetValues(){
    //return IC1_WriteRegister(ACC_ADDR,)
    //TODO
    return 0;
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function: displays a main page with MENU SELECTION,
//----------------------------------------------------------------------------
void DrawMenu(){

    uint8_t leave = 0;

    TFT_FillRectangle(0, 0, 250, 350, TFT_BLACK);

    TFT_FillRectangle(0, 260, 78, 60, TFT_WHITE);
    TFT_FillRectangle(80, 260, 78, 60, TFT_WHITE);
    TFT_FillRectangle(160, 260, 78, 60, TFT_WHITE);

    TFT_DrawString(10,280,"MAIN",TFT_BLACK,TFT_WHITE,2);
    TFT_DrawString(90,280,"23008",TFT_BLACK,TFT_WHITE,2);
    TFT_DrawString(165,280,"LIS3DH",TFT_BLACK,TFT_WHITE,2);

}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function: displays a main page with course name,
//          and name of each member
//----------------------------------------------------------------------------
void GoToMain(){

   TFT_FillRectangle(0, 0, 255, 254, TFT_RED);

   uint8_t leave = 0;

   while(leave == 0){

       TOUCH_GetTouchPoints();
       TFT_DrawString(40,50,"CMPEN 352",TFT_YELLOW,TFT_RED,3);
       TFT_DrawString(40,80,"LAB 7",TFT_YELLOW,TFT_RED,3);
       TFT_DrawString(40,120,"Mike DeLeo",TFT_YELLOW,TFT_RED,2);
       TFT_DrawString(40,140,"Morayo Ogunsina",TFT_YELLOW,TFT_RED,2);

       // exit the MAIN screen
       if((touch_x >= 90 && touch_x <= 152) && (touch_y >= 244 && touch_y <= 293)){
           leave = 1;
           GoTo23008();
       }
       else if ((touch_x >= 158 && touch_x <= 227) && (touch_y >= 244 && touch_y <= 293)){
           leave = 1;
           GoToLIS3DH();
       }
   }
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function: displays a screen for switching on LED graphics and LED on circuit board
//----------------------------------------------------------------------------
void GoTo23008(){

    TFT_FillRectangle(0, 0, 255, 254, TFT_BLUE);
    TFT_DrawString(50,150,"TIMES ON: ",TFT_WHITE,TFT_BLUE,2);

    TFT_FillCircle(40,200,27,TFT_DARKGREY);
    TFT_DrawString(30,191,"ON ",TFT_BLACK,TFT_DARKGREY,2);

    TFT_FillCircle(200,200,27,TFT_DARKGREY);
    TFT_DrawString(179,191,"OFF ",TFT_BLACK,TFT_DARKGREY,2);

    uint8_t state = 0;
    uint8_t lastState = 0;
    uint8_t leave = 0;
    uint8_t led_on = 0;
    uint8_t values = 0;
   

    while(leave == 0){

        TOUCH_GetTouchPoints();
        values = MCP23008_GetValues();
        uint8_t B1 = values & 0b00000001;
        uint8_t B2 = (values & 0b00000010) >> 1;

        // TURN ON LED
        if ((B2 == 1 || (B2 == 1 && B1 == 1)) || (touch_x >= 21 && touch_x <= 61) && (touch_y >= 155 && touch_y <= 209)){
           if (lastState == state){}
                else{
                    led_on++;
                }
                lastState = state;
                TurnOnLED();
                if (led_on == 100){
                    led_on = 0;
                }
            TFT_DrawChar(160,150,(led_on - led_on %10)/10 + 48, TFT_WHITE, TFT_BLUE,2);
            TFT_DrawChar(180,150, led_on %10 + 48, TFT_WHITE, TFT_BLUE,2);
            state = 1;
            MCP23008_WriteValues(0b00000000);
        }

        // TURN OFF LED
        else if ((B1 == 1) || (touch_x >= 177 && touch_x <= 216) && (touch_y >= 160 && touch_y <= 206)){
            lastState = state;
            TurnOffLED();
            state = 0;
            MCP23008_WriteValues(0b00001111);
            values = MCP23008_GetValues();
        }

       // exit the 23008 screen
       if((touch_x >= 21 && touch_x <= 86) && (touch_y >= 244 && touch_y <= 293)){
             leave = 1;
             DrawMenu();
        }
       else if ((touch_x >= 158 && touch_x <= 227) && (touch_y >= 244 && touch_y <= 293)){
           leave = 1;
           GoToLIS3DH();
       }
    }
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function:  displays the values of x, y and z components of the accelerometer,
//----------------------------------------------------------------------------
void GoToLIS3DH(){

    uint8_t leave = 0;
    TFT_FillRectangle(0, 0, 255, 254, TFT_BLACK);

    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
    float twog_divider = 16380 ;   //for 2 g, use divider 16380

    float x_g = 0;
    float y_g = 0;
    float z_g = 0;

    char x_s[17];
    char y_s[17];
    char z_s[17];
    char m_s[17];
    while(leave == 0){

        TOUCH_GetTouchPoints();
        
        x = I2C1_ReadRegister(0x19,0x28);
        y = I2C1_ReadRegister(0x19,0x2A);
        z = I2C1_ReadRegister(0x19,0x2C);

//        x |= (~( I2C1_ReadRegister(0x19, 0x28) - 1 ));
//        y |= (~( I2C1_ReadRegister(0x19, 0x2A) - 1 ));
//        z |= (~( I2C1_ReadRegister(0x19, 0x2C) - 1 ));

//        x = ~( x - 1);
//        y = ~( y - 1);
//        z = ~( z - 1);
        

        //new 8 bits, pushes them ahead of the bits and remove two's complement
        // concatenate the new byte to give a LS byte and MSbyte
        x |= (( I2C1_ReadRegister(0x19, 0x29)  ))<< 8;
        y |= (( I2C1_ReadRegister(0x19, 0x2B)  ))<< 8;
        z |= (( I2C1_ReadRegister(0x19, 0x2D)  ))<< 8;


        // gets magnitude of first 8 bits of each
         

         x_g = x/twog_divider;
         y_g = y/twog_divider;
         z_g = z/twog_divider;
        //before they were %d.03d and uint16_t
        printf("x:  %.03f ", x_g);
        printf("y: %.03f ", y_g);
        printf("z:  %.03f \n", z_g);
        //printf("magnitude: %d.%03d \n", mag);
        float mag = sqrt(x_g * x_g + y_g * y_g + z_g * z_g);
        sprintf(x_s, " %.3f",x_g);
        sprintf(y_s, " %.3f",y_g);
        sprintf(z_s, " %.3f",z_g);
        sprintf(m_s, " %.3f",mag);

        // x acceleration component
        TFT_DrawString(50,100,"x: ",TFT_WHITE, TFT_BLACK,2);
        TFT_DrawString(100,100, x_s, TFT_WHITE, TFT_BLACK, 2);


        //y acceleration component
        TFT_DrawString(50,140,"y: ",TFT_WHITE, TFT_BLACK,2);
        TFT_DrawString(100,140, y_s, TFT_WHITE, TFT_BLACK, 2);

        // z acceleration component
        TFT_DrawString(50,180,"z: ",TFT_WHITE, TFT_BLACK,2);
        TFT_DrawString(100,180, z_s, TFT_WHITE, TFT_BLACK, 2);

        TFT_DrawString(50,200,"mag: ",TFT_WHITE, TFT_BLACK,2);
        TFT_DrawString(100,200, m_s, TFT_WHITE, TFT_BLACK, 2);
//        x_LC = x;
//        y_LC = y;
//        z_LC = z;      

       // exit the LIS3DH screen
       if((touch_x >= 21 && touch_x <= 86) && (touch_y >= 244 && touch_y <= 293)){
             leave = 1;
             DrawMenu();
       }
       else if((touch_x >= 90 && touch_x <= 152) && (touch_y >= 244 && touch_y <= 293) ){
           leave = 1;
           GoTo23008();
       }
    }
}



//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function:  draws an led turned on
//----------------------------------------------------------------------------
void TurnOnLED(){

    TFT_FillCircle(120,80,40,TFT_GREENYELLOW);
    LED_OUT = 1;
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function:  draws an led turned off
//----------------------------------------------------------------------------
void TurnOffLED(){

    TFT_FillCircle(120,80,40,TFT_DARKGREEN);
    LED_OUT = 0;

}

uint8_t ms = 0;
//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition:
//function:  Interrupt service
//
//----------------------------------------------------------------------------
void __ISR(_TIMER_1_VECTOR, IPL7SOFT) Timer1Handler(void) {

    // Clear interrupt flag
    IFS0bits.T1IF = 0;

//    TMR1 = 0;
//    CHA = ROT_A;
//    CHB = ROT_B;
//    ms = 0;
//
//       state = (CHA << 1) | CHB;
//       switch(state){
//            case 0b00:
//               if (lastState == 0b01){pos++;dir=0;}
//               if (lastState == 0b10){pos--;dir=1;}
//               break;
//            case 0b01:
//               if (lastState == 0b11){pos++;dir=0;}
//               if (lastState == 0b00){pos--;dir=1;}
//               break;
//            case 0b11:
//               if (lastState == 0b10){pos++;dir=0;}
//               if (lastState == 0b01){pos--;dir=1;}
//               break;
//            case 0b10:
//               if (lastState == 0b00){pos++;dir=0;}
//               if (lastState == 0b11){pos--;dir=1;}
//               break;
//        }
//        if (SW == 0){
//            pos = 0;
//        }
//
//        lastState = state;
//
//        if (pos > 39){
//            pos = 0;
//        }

}

