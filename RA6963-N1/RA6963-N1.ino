//==============================================================================
//
//  CRYSTALFONTZ
//
//  This code drives the 
//  https://www.crystalfontz.com/product/
//
//  The controller is a RAiO RA6963-N1
//    https://www.crystalfontz.com/controllers/Raio%20Technology/RA6963/424
//
//  Seeeduino v4.2, an open-source 3.3v capable Arduino clone.
//    https://www.seeedstudio.com/Seeeduino-V4.2-p-2517.html
//    https://github.com/SeeedDocument/SeeeduinoV4/raw/master/resources/Seeeduino_v4.2_sch.pdf
//
//==============================================================================
//This is free and unencumbered software released into the public domain.
//
//Anyone is free to copy, modify, publish, use, compile, sell, or
//distribute this software, either in source code form or as a compiled
//binary, for any purpose, commercial or non-commercial, and by any
//means.
//
//In jurisdictions that recognize copyright laws, the author or authors
//of this software dedicate any and all copyright interest in the
//software to the public domain. We make this dedication for the benefit
//of the public at large and to the detriment of our heirs and
//successors. We intend this dedication to be an overt act of
//relinquishment in perpetuity of all present and future rights to this
//software under copyright law.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//OTHER DEALINGS IN THE SOFTWARE.
//
//For more information, please refer to <http://unlicense.org/>
//==============================================================================
// LCD & USD control lines
//   ARD      | Port  | Display pin |  Function - 8080 Parallel   |
//------------+-------+-------------+-----------------------------+
//  3.3V      |       |             |  POWER 3.3V                 |
//  GND	      |       |             |  GROUND                     |
// -----------+-------+-------------+-----------------------------+
//  N/A       | N/A   |             |  BS1 - 3.3V                 |
//  N/A       | N/A   |             |  BS2 - 3.3V                 |
// -----------+-------+-------------+-----------------------------+
//  D8        | PORTB |             |  Chip Enable Signal  (CS)   |
//  D9        | PORTB |             |  Reset            (RESET)   |
//  D10       | PORTB |             |  Data/Command        (DC)   |
//  D11       | PORTB |             |  Write               (WR)   |
//  D12       | PORTB |             |  Read                (RD)   |
// -----------+-------+-------------+-----------------------------+
// Data Lines
// -----------+-------+-------------+-----------------------------+
//  D0        | PORTD |             |  LCD_D10 (DB0)              |
//  D1        | PORTD |             |  LCD_D11 (DB1)              |
//  D2        | PORTD |             |  LCD_D12 (DB2)              |
//  D3        | PORTD |             |  LCD_D13 (DB3)              |
//  D4        | PORTD |             |  LCD_D14 (DB4)              |
//  D5        | PORTD |             |  LCD_D15 (DB5)              |
//  D6        | PORTD |             |  LCD_D16 (DB6)              |
//  D7        | PORTD |             |  LCD_D17 (DB7)              |
// -----------+-------+-------------+-----------------------------+

#include <stdint.h>

//==============================================================================
// Set the resolution to match the display being used
#define HRES 128
#define VRES 128

//==============================================================================
#define CLR_CS (PORTB &= ~(0x01))    //pin #8  - Chip Enable Signal
#define SET_CS (PORTB |= (0x01))     //pin #8  - Chip Enable Signal
#define CLR_RESET (PORTB &= ~(0x02)) //pin #9  - Reset
#define SET_RESET (PORTB |= (0x02))  //pin #9  - Reset
#define CLR_DC (PORTB &= ~(0x04))    //pin #10 - Data/Instruction
#define SET_DC (PORTB |= (0x04))     //pin #10 - Data/Instruction
#define CLR_WR (PORTB &= ~(0x08))    //pin #11 - Write
#define SET_WR (PORTB |= (0x08))     //pin #11 - Write
#define CLR_RD (PORTC &= ~(0x10))    //pin #12 - Read
#define SET_RD (PORTC |= (0x10))     //pin #12 - Read

// #include <avr/io.h>

//================================================================================

void writeCommand(uint8_t command)
{
    //select the LCD's command register
    SET_DC;
    //select the LCD controller
    CLR_CS;
    //send the data via parallel
    PORTD = command;
    //clear the write register
    CLR_WR;
    //set the write register
    SET_WR;
    //deselct the LCD controller
    SET_CS;
}
//================================================================================
void writeData(uint8_t data)
{
    //select the LCD's data register
    CLR_DC;
    //select the LCD controller
    CLR_CS;
    //send the data via parallel
    PORTD = data;
    //clear the write register
    CLR_WR;
    //set the write register
    SET_WR;
    //deselct the LCD controller
    SET_CS;
}
//================================================================================
void setXY(uint8_t row, uint8_t column)
{
    writeData(row & 0xff);
    writeData(column & 0xff);
    writeCommand(0x21);
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_RAM(uint8_t Data)
{
    uint8_t
        row;
    uint8_t
        column;

    setXY(0, 0);
    for (row = 0; row < VRES; row++)
    {
        for (column = 0; column < HRES / 8; column++)
        {
            writeData(Data);
        }
    }
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_RAM_CheckerBoard(void)
{
    uint8_t
        row;
    uint8_t
        column;

    setXY(0, 0);
    for (row = 0; row < VRES; row++)
    {
        //start the checker pattern with odd rows
        if (0 == (row & 0x01))
        {
            for (column = 0; column < HRES / 8; column++)
            {
                writeData(0x55);
            }
        }
        //switch if even
        else
        {
            for (column = 0; column < HRES / 8; column++)
            {
                writeData(0xAA);
            }
        }
    }
}
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void dispInit()
{
    //The CFA10105 has a power-on reset circuit,
    //you can use the following code if you are using GPIO for reset
    CLR_RESET;
    delay(1);
    SET_RESET;
    delay(120);

    writeData(0x00);    //write to low 8 bit
    writeData(0x00);    //write to hi 8 bit
    writeCommand(0x40); //text home address control set
                        //write graphic home address=4000h
    writeData(0x00);    //write to low 8 bit
    writeData(0x40);    //write to hi 8 bit
    writeCommand(0x42); //write command
                        //write text area address=001fh
    writeData(0x10);    //             128/8=16    16=0x10
    writeData(0x00);
    writeCommand(0x41); //graphic home address control set
                        //for Graphic mode
    writeData(0x10);    //write graphic home address=4000h       // 128/8=16=0x10
    writeData(0x00);
    writeCommand(0x43); //Graphic area control set
                        //Mode set
    writeCommand(0x80); //Display mode set (Graphic only enable)
    writeCommand(0x98); //Graphic display enable
}
//================================================================================
// showSplash() takes an image out of flash and puts it on the screen. In this case,
// the image stored in flash is the splash screen
//================================================================================
void showImage(const uint8_t image[HRES / 8][VRES])
{

    //TODO: Finish this function

    for (uint8_t y = 0; y < 7; y++)
    {
        for (uint8_t x = 0; x < 128; x++)
        {
            writeData(pgm_read_byte(&image[y][x]));
        }
    }
}
//================================================================================
void setup()
{
    //Set up port directions
    DDRD = 0xff;
    DDRC = 0xff;
    DDRB = 0x3f;
    //Idle the lines in a reasonable state
    PORTD = 0xff;
    SET_RD;
    SET_WR;
    SET_CS;

    //Initialize the display
    dispInit();
}
//================================================================================
void loop()
{


}
//================================================================================
