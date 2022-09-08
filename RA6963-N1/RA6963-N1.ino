//==============================================================================
//
//  CRYSTALFONTZ

//  The controller is a RAiO RA6963-N1
//    https://www.crystalfontz.com/controllers/Raio%20Technology/RA6963/424
//
//  Seeeduino v4.2, an open-source 3.3v capable Arduino clone.
//    https://www.seeedstudio.com/Seeeduino-V4.2-p-2517.html
//    https://github.com/SeeedDocument/SeeeduinoV4/raw/master/resources/Seeeduino_v4.2_sch.pdf
//
//==============================================================================
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
//==============================================================================
// LCD & USD control lines
//   ARD      | Port  | Display pin |  Function - 8080 Parallel   |
//------------+-------+-------------+-----------------------------+
//  5V        |       |             |  POWER                      |
//  GND	      |       |             |  GROUND                     |
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

// Define which family of modules
#define CFAG128128 (1)
#define CFAG160128 (0)

#if CFAG128128
// Set the resolution to match the display being used
#define HRES 128
#define VRES 128
#endif

#if CFAG160128
// Set the resolution to match the display being used
#define HRES 160
#define VRES 128
#endif

//==============================================================================
#define CLR_CS (PORTB &= ~(0x01))    // pin #8  - Chip Enable Signal
#define SET_CS (PORTB |= (0x01))     // pin #8  - Chip Enable Signal
#define CLR_RESET (PORTB &= ~(0x02)) // pin #9  - Reset
#define SET_RESET (PORTB |= (0x02))  // pin #9  - Reset
#define CLR_DC (PORTB &= ~(0x04))    // pin #10 - Data/Instruction
#define SET_DC (PORTB |= (0x04))     // pin #10 - Data/Instruction
#define CLR_WR (PORTB &= ~(0x08))    // pin #11 - Write
#define SET_WR (PORTB |= (0x08))     // pin #11 - Write
#define CLR_RD (PORTB &= ~(0x10))    // pin #12 - Read
#define SET_RD (PORTB |= (0x10))     // pin #12 - Read

// #include <avr/io.h>

//================================================================================
#if CFAG160128
const uint8_t logo[2560] PROGMEM = {
0X00,0X01,0XE0,0X07,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X03,0XF0,0X0F,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0X38,0X1C,0XE0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0E,0X1C,0X38,
0X70,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X1C,0X08,0X70,0X38,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X38,0X00,0XE0,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X78,0X01,0XE0,0X1E,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XF8,0X03,0XE0,
0X1F,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X01,0XF8,0X07,0XE0,0X1F,0X80,0X01,0XF0,0X00,0X00,0X00,0X00,0X80,0X00,0X61,0XE0,
0X00,0X00,0X08,0X00,0X03,0XF8,0X0F,0XE0,0X1F,0XC0,0X07,0XF8,0X00,0X00,0X00,0X01,
0X80,0X00,0X63,0XC0,0X00,0X00,0X18,0X00,0X03,0XF8,0X0F,0XE0,0X1F,0XC0,0X0E,0X0C,
0X00,0X00,0X00,0X03,0X00,0X00,0X63,0X00,0X00,0X00,0X30,0X00,0X00,0X00,0X0F,0XE0,
0X00,0X00,0X1C,0X06,0X00,0X00,0X00,0X03,0X00,0X00,0XC6,0X00,0X00,0X00,0X30,0X00,
0X00,0X00,0X0F,0XE0,0X00,0X00,0X18,0X06,0X37,0XC0,0XC3,0XC7,0XC7,0XC0,0XDF,0X87,
0XC1,0X9E,0X7D,0XFE,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X38,0X00,0X3F,0XC1,0X8F,0XF7,
0XCF,0XF0,0XDF,0X9F,0XE1,0XFF,0X7D,0XFE,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X30,0X00,
0X38,0XC1,0X8C,0X33,0X1C,0X30,0XC6,0X38,0X71,0XC3,0X30,0X0C,0XFF,0XFF,0X8F,0XE0,
0X00,0X00,0X30,0X00,0X70,0X63,0X0E,0X03,0X00,0X30,0XC6,0X30,0X33,0X83,0X30,0X18,
0XFF,0XFF,0X8F,0XE0,0X00,0X00,0X30,0X00,0X60,0X66,0X07,0X03,0X07,0XF1,0X8C,0X60,
0X33,0X86,0X30,0X30,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X30,0X00,0X60,0X66,0X03,0XC6,
0X1F,0XF1,0X8C,0X60,0X33,0X06,0X60,0X60,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X30,0X0C,
0X60,0X6C,0X00,0XE6,0X38,0X61,0X8C,0X60,0X33,0X06,0X60,0XC0,0XFF,0XFF,0X8F,0XE0,
0X00,0X00,0X38,0X18,0X60,0X6C,0X30,0X66,0X30,0X61,0X8C,0X60,0X63,0X06,0X61,0X80,
0XFF,0XFF,0X8F,0XE0,0X00,0X00,0X1C,0X38,0XC0,0X78,0X38,0X66,0X30,0XE1,0X8C,0X70,
0XE7,0X06,0X63,0X00,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X0F,0XF0,0XC0,0X70,0X1F,0XC7,
0XBF,0XE3,0X18,0X3F,0XC6,0X0C,0X7F,0XF8,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X07,0XC0,
0XC0,0X30,0X0F,0X87,0X1F,0X63,0X18,0X1F,0X06,0X0C,0X77,0XF8,0XFF,0XFF,0X8F,0XE0,
0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XFF,0XFF,0X8F,0XE0,0X00,0X00,0X00,0X00,0X00,0X60,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X00,0X00,0X03,0XC0,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X00,0X00,
0X03,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0X8F,0XE0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0XFF,0XFF,0X8F,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XFF,0X8F,0XE7,0XFF,0XFF,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XE0,
0X00,0X00,0X0E,0X7C,0X20,0X70,0X43,0X8E,0X10,0XE3,0X9F,0X03,0XC0,0X02,0X00,0X00,
0X00,0X00,0X0F,0XE0,0X00,0X00,0X11,0X40,0X50,0X88,0XC4,0X51,0X31,0X14,0X50,0X84,
0X20,0X00,0X00,0X00,0X03,0XF8,0X0F,0XE0,0X1F,0XC0,0X20,0X40,0X51,0X05,0X44,0X11,
0X50,0X14,0X50,0X84,0X07,0X2A,0X71,0XC0,0X03,0XF8,0X0F,0XE0,0X1F,0XC0,0X20,0X78,
0X51,0X00,0X47,0X91,0X10,0X13,0X9F,0X83,0X08,0XB2,0X8A,0X20,0X01,0XF8,0X07,0XE0,
0X1F,0X80,0X20,0X40,0X89,0X1C,0X44,0X51,0X10,0X24,0X50,0X80,0XCF,0XA2,0XF9,0X80,
0X00,0XF8,0X03,0XE0,0X1F,0X00,0X20,0X40,0XF9,0X04,0X44,0X51,0X10,0X44,0X50,0X80,
0X28,0X22,0X80,0X40,0X00,0X78,0X01,0XE0,0X1E,0X00,0X11,0X41,0X04,0X88,0X44,0X51,
0X10,0X84,0X50,0X84,0X28,0XA2,0X8A,0X20,0X00,0X38,0X00,0XE0,0X1C,0X00,0X0E,0X41,
0X04,0X70,0X43,0X8E,0X11,0XF3,0X9F,0X03,0XC7,0X22,0X71,0XC0,0X00,0X1C,0X08,0X70,
0X38,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X0E,0X1C,0X38,0X70,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X07,0X38,0X1C,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XF0,0X0F,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XE0,0X07,
0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X0C,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,
0X04,0X94,0X92,0X92,0X52,0X4A,0X49,0X49,0X29,0X24,0XA7,0XE4,0X94,0X92,0X92,0X52,
0X4A,0X49,0X49,0X01,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XF0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X44,0X00,0X00,0X00,0X00,0X00,0X0F,0X00,
0X00,0X00,0X0E,0X20,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X11,0XE4,0X00,0X00,0X00,
0X00,0X00,0X1F,0X80,0X00,0X00,0X0C,0X30,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X39,
0X44,0X00,0X00,0X00,0X00,0X00,0X39,0X80,0X00,0X00,0X1C,0X18,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X11,0X04,0X00,0X00,0X00,0X00,0X00,0X70,0XE0,0X00,0X00,0X18,0X18,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0XE0,0X60,
0X00,0X00,0X30,0X0C,0X00,0X00,0X00,0X3C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0XC0,0X30,0X00,0X00,0X30,0X0E,0X00,0X00,0X00,0X7E,0X00,0X00,0X00,0X00,
0X00,0X94,0XF2,0X92,0X52,0X49,0XC9,0X79,0X29,0X25,0X74,0XA6,0X94,0X92,0X92,0XD7,
0XCA,0X49,0X49,0X00,0X00,0X03,0XFC,0X00,0X00,0X03,0X80,0X10,0X00,0X00,0X60,0X06,
0X00,0X00,0X01,0XC1,0XC0,0X00,0X00,0X00,0X00,0X07,0X1E,0X00,0X00,0X01,0X00,0X38,
0X00,0X00,0X60,0X07,0X00,0X00,0X03,0X80,0XE0,0X00,0X00,0X00,0X00,0X0C,0X07,0X00,
0X00,0X03,0X80,0X18,0X00,0X00,0XC0,0X03,0X00,0X00,0X03,0X00,0X60,0X00,0X00,0X00,
0X00,0X1C,0X03,0X00,0X00,0X02,0X00,0X0C,0X00,0X00,0XC0,0X03,0X80,0X00,0X06,0X00,
0X70,0X00,0X00,0X00,0X18,0X38,0X01,0XC0,0X00,0X07,0X00,0X0C,0X00,0X01,0X80,0X01,
0X80,0X00,0X0E,0X00,0X38,0X00,0X00,0X06,0X24,0X70,0X00,0XC0,0X00,0X04,0X00,0X0E,
0X00,0X00,0XC0,0X01,0XC0,0X00,0X0C,0X00,0X18,0X00,0X00,0X09,0X24,0XC0,0X00,0X60,
0X00,0X0C,0X00,0X06,0X00,0X01,0X80,0X00,0XC0,0X00,0X18,0X00,0X0C,0X00,0X00,0X09,
0X24,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0X09,0X24,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X09,0X24,0X00,0X00,0X30,0X00,0X18,0X00,0X03,
0X00,0X01,0X00,0X00,0X60,0X00,0X30,0X00,0X02,0X00,0X03,0X09,0X24,0X00,0X00,0X18,
0X00,0X30,0X00,0X03,0X80,0X01,0X80,0X00,0X70,0X00,0X60,0X00,0X07,0X00,0X0E,0X09,
0X18,0X00,0X00,0X1C,0X00,0X70,0X00,0X01,0X80,0X03,0X00,0X00,0X30,0X00,0X60,0X00,
0X01,0X80,0X1C,0X06,0X00,0X00,0X00,0X0E,0X00,0X60,0X00,0X01,0XC0,0X03,0X80,0X00,
0X38,0X00,0XC0,0X00,0X01,0XC0,0X38,0X00,0X00,0X00,0X00,0X06,0X00,0XC0,0X00,0X00,
0XC0,0X02,0X00,0X00,0X18,0X00,0XE0,0X00,0X00,0XE0,0X30,0X00,0X00,0X00,0X00,0X07,
0X01,0XC0,0X00,0X00,0XE0,0X07,0X00,0X00,0X18,0X00,0X80,0X00,0X00,0X78,0XE0,0X00,
0X00,0X00,0X00,0X03,0X83,0X80,0X00,0X00,0X60,0X06,0X00,0X00,0X0C,0X01,0XC0,0X00,
0X00,0X3F,0X80,0X00,0X00,0X94,0X92,0X93,0XEB,0X4A,0X49,0X49,0X69,0X2D,0X24,0XA4,
0X9C,0X93,0X92,0X52,0X4A,0X4F,0X69,0X00,0X00,0X00,0X00,0X00,0X7E,0X00,0X00,0X00,
0X70,0X0C,0X00,0X00,0X06,0X03,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X3C,0X00,0X00,0X00,0X20,0X0C,0X00,0X00,0X06,0X07,0X00,0X00,0X00,0X00,0X00,0X00,
0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X18,0X00,0X00,0X07,0X0E,0X00,0X00,
0X00,0X00,0X00,0X01,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X18,0X38,0X00,0X00,
0X03,0X9C,0X00,0X00,0X00,0X00,0X00,0X03,0X14,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X0C,0X30,0X00,0X00,0X01,0XF8,0X00,0X00,0X00,0X00,0X00,0X05,0X04,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X0C,0X70,0X00,0X00,0X00,0XF0,0X00,0X00,0X00,0X00,0X00,0X01,
0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0XE4,0X94,0X92,0X92,0X52,0X4A,0X49,0X49,0X2F,0XE4,0XA4,0XA4,
0X94,0X92,0X92,0X52,0X4A,0X49,0X49,0X39,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X04,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XC0,0X1F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XF8,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X0F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X01,0XF8,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X38,0X10,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X08,0X07,0X70,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X04,0X08,0X88,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X11,0XFE,0XE8,0X88,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X10,0X04,0X08,0X88,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X10,0X08,0X07,0X70,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0C,0X10,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0X01,0X40,0X40,0X0E,0X07,0X81,0X00,
0X00,0X02,0X30,0X50,0X00,0X00,0X00,0XC6,0X00,0X40,0X00,0X00,0X04,0X80,0X50,0X00,
0X08,0X00,0X82,0X00,0X10,0X06,0X48,0X40,0X00,0X00,0X01,0X29,0X00,0X40,0X00,0X00,
0X04,0XA5,0X78,0X5C,0X1C,0X91,0X07,0X33,0XB8,0X02,0X70,0X57,0X18,0XE1,0X20,0X29,
0X06,0X73,0XDD,0XC0,0X07,0XA5,0X50,0X52,0X12,0X61,0X02,0X4A,0X50,0X02,0X48,0X54,
0XA5,0X00,0XC0,0X49,0X09,0X48,0X52,0X00,0X04,0XA5,0X50,0X52,0X02,0X62,0X02,0X4A,
0X50,0X02,0X48,0X54,0XBC,0XC0,0XC0,0X49,0X08,0X49,0XD1,0X80,0X04,0XA5,0X50,0X52,
0X12,0X62,0X02,0X4A,0X50,0X02,0X48,0X54,0XA0,0X20,0XC0,0X89,0X09,0X4A,0X50,0X40,
0X07,0X1D,0X58,0X52,0X0C,0X92,0X02,0X32,0X59,0X02,0X30,0X54,0X9D,0XC1,0X21,0XEE,
0X06,0X4B,0XD3,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X0F,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X00,
0X00,0X00,0X00,0X00,0X02,0X00,0X00,0X00,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X04,0X00,0X80,0X00,0X08,0X00,0X08,0X00,0X02,0X67,0XE7,0X19,0XFF,0XA5,0XD8,0X18,
0XCF,0XCE,0X33,0X8E,0XFE,0X63,0X83,0X19,0XDD,0XFC,0XFC,0X00,0X02,0X94,0X94,0XA5,
0X05,0X25,0X24,0X25,0X29,0X29,0X4A,0X50,0X14,0X94,0X84,0XA5,0X29,0X05,0X08,0X00,
0X02,0XF4,0X94,0XBD,0X1D,0X25,0X3C,0X21,0X29,0X29,0X7A,0X4C,0X74,0XF4,0X84,0X25,
0X29,0X1C,0XC8,0X00,0X02,0X84,0X94,0XA1,0X25,0X25,0X20,0X25,0X29,0X29,0X42,0X42,
0X94,0X84,0X84,0XA5,0X29,0X24,0X28,0X00,0X02,0X74,0X97,0X1D,0X3D,0X9D,0X1C,0X18,
0XC9,0X2E,0X3A,0X5C,0XF6,0X73,0X83,0X19,0X2D,0X3D,0XCC,0X00,0X00,0X00,0X04,0X00,
0X00,0X00,0X00,0X00,0X00,0X08,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X04,0X00,0X00,0X00,0X00,0X00,0X00,0X08,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

#endif

#if CFAG128128
const uint8_t logo[2048] PROGMEM = {
    0x00, 0x1C, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3E, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x77, 0x0E, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xE3, 0x9C, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0xC1, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0xC0, 0x70, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0xC0, 0xF0, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xC1, 0xF0, 0x3F, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1C, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0xC1, 0xF0, 0x3F, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x20, 0x03, 0x3C, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x01, 0xF0, 0x00, 0x01, 0xC7, 0x00, 0x00, 0x00, 0x60, 0x03, 0x30, 0x00, 0x00, 0x60, 0x00,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF1, 0x83, 0x37, 0x86, 0x79, 0xF3, 0xC6, 0xF9, 0xE1, 0xB9, 0xFF, 0xE0,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF3, 0x00, 0x3F, 0x8C, 0xFD, 0xF7, 0xE6, 0xFB, 0xF1, 0xFD, 0xFF, 0xE0,
    0xFF, 0xF9, 0xF0, 0x00, 0x03, 0x00, 0x38, 0xCC, 0xC0, 0xC0, 0x66, 0x67, 0x19, 0xCC, 0xC0, 0xC0,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF3, 0x00, 0x30, 0xD8, 0xF0, 0xC7, 0xE6, 0x66, 0x19, 0x8C, 0xC3, 0x80,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF3, 0x03, 0x30, 0xD8, 0x79, 0xCC, 0xC6, 0x66, 0x19, 0x8D, 0xC7, 0x00,
    0xFF, 0xF9, 0xF0, 0x00, 0x03, 0x86, 0x60, 0xF0, 0x19, 0x8C, 0xCC, 0xC6, 0x3B, 0x19, 0x8C, 0x00,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF1, 0xFE, 0x60, 0x71, 0xF9, 0xEF, 0xCC, 0xC3, 0xF3, 0x19, 0xFF, 0xC0,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF0, 0xF8, 0x60, 0x60, 0xF1, 0xE6, 0xCC, 0xC1, 0xE3, 0x19, 0xFF, 0xC0,
    0xFF, 0xF9, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF0, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF0, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xF9, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xFF, 0xF9, 0xF3, 0xFF, 0xF3, 0x8F, 0x10, 0xE1, 0x18, 0xC2, 0x31, 0x84, 0x21, 0x80, 0x08, 0x00,
    0x00, 0x01, 0xF0, 0x00, 0x04, 0x48, 0x29, 0x13, 0x25, 0x26, 0x4A, 0x4A, 0x62, 0x40, 0x00, 0x00,
    0x0F, 0xC1, 0xF0, 0x3F, 0x04, 0x08, 0x29, 0x05, 0x05, 0x2A, 0x0A, 0x4A, 0xA2, 0x0C, 0xE8, 0xC7,
    0x0F, 0xC1, 0xF0, 0x3F, 0x04, 0x0F, 0x29, 0x31, 0x08, 0xC2, 0x11, 0x8A, 0x21, 0x92, 0x89, 0x28,
    0x07, 0xC0, 0xF0, 0x3E, 0x04, 0x08, 0x39, 0x11, 0x11, 0x22, 0x22, 0x4E, 0x20, 0x5E, 0x89, 0xE6,
    0x03, 0xC0, 0x70, 0x3C, 0x04, 0x48, 0x45, 0x11, 0x21, 0x22, 0x42, 0x51, 0x22, 0x50, 0x89, 0x01,
    0x01, 0xC1, 0x38, 0x38, 0x03, 0x88, 0x44, 0xE1, 0x3C, 0xC2, 0x79, 0x91, 0x21, 0x8E, 0x88, 0xEE,
    0x00, 0xE3, 0x9C, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x77, 0x0E, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3E, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1C, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x44, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xEA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x91,
    0xE4, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x18, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39,
    0x44, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11,
    0x04, 0x00, 0x00, 0x00, 0x01, 0x86, 0x00, 0x00, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x20, 0x30, 0x00, 0x00, 0x6C, 0x00, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x60, 0x10, 0x00, 0x00, 0xC6, 0x00, 0x00, 0x00,
    0x00, 0xAF, 0xEA, 0xAA, 0xAA, 0xAB, 0xAA, 0xAA, 0xEA, 0xBA, 0xAA, 0xAA, 0xAB, 0xAA, 0xAA, 0x80,
    0x00, 0x18, 0xC0, 0x00, 0x02, 0x01, 0x80, 0x00, 0x40, 0x18, 0x00, 0x01, 0x81, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x60, 0x00, 0x06, 0x00, 0x80, 0x00, 0x40, 0x08, 0x00, 0x03, 0x01, 0x80, 0x00, 0x00,
    0x00, 0x60, 0x20, 0x00, 0x04, 0x00, 0xC0, 0x00, 0x40, 0x08, 0x00, 0x03, 0x00, 0x80, 0x00, 0x00,
    0x18, 0xC0, 0x30, 0x00, 0x04, 0x00, 0x40, 0x00, 0x40, 0x0C, 0x00, 0x06, 0x00, 0xC0, 0x00, 0x06,
    0x25, 0x80, 0x18, 0x00, 0x0C, 0x00, 0x40, 0x00, 0xC0, 0x04, 0x00, 0x06, 0x00, 0x40, 0x00, 0x09,
    0x25, 0x00, 0x0C, 0x00, 0x08, 0x00, 0x60, 0x00, 0x80, 0x06, 0x00, 0x0C, 0x00, 0x60, 0x00, 0x09,
    0x25, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC9,
    0x25, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC9,
    0x24, 0x00, 0x02, 0x00, 0x18, 0x00, 0x20, 0x00, 0x80, 0x02, 0x00, 0x18, 0x00, 0x18, 0x00, 0xC9,
    0x24, 0x00, 0x03, 0x00, 0x10, 0x00, 0x20, 0x01, 0x80, 0x02, 0x00, 0x18, 0x00, 0x08, 0x01, 0x89,
    0x18, 0x00, 0x01, 0x80, 0x30, 0x00, 0x30, 0x01, 0x00, 0x03, 0x00, 0x30, 0x00, 0x0C, 0x01, 0x86,
    0x00, 0x00, 0x00, 0x80, 0x20, 0x00, 0x10, 0x01, 0x00, 0x01, 0x00, 0x30, 0x00, 0x04, 0x03, 0x00,
    0x00, 0x00, 0x00, 0xC0, 0x60, 0x00, 0x18, 0x01, 0x00, 0x01, 0x80, 0x20, 0x00, 0x06, 0x06, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x08, 0x03, 0x00, 0x00, 0x80, 0x60, 0x00, 0x03, 0x0C, 0x00,
    0x00, 0xAA, 0xAA, 0xEA, 0xEA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xEA, 0xAA, 0xAB, 0x9A, 0x80,
    0x00, 0x00, 0x00, 0x30, 0x80, 0x00, 0x0C, 0x02, 0x00, 0x00, 0xC0, 0x60, 0x00, 0x00, 0xF0, 0x00,
    0x00, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x04, 0x02, 0x00, 0x00, 0x40, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x06, 0x02, 0x00, 0x00, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x00, 0x00, 0x31, 0x80, 0x00, 0x00, 0x00, 0x01,
    0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x03,
    0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0C, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x05,
    0x04, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x81,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0xE4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x20, 0x00,
    0x20, 0x81, 0xB0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x08, 0x10, 0x36,
    0x70, 0x42, 0x48, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x1C, 0x08, 0x49,
    0x2F, 0xE2, 0x49, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x89, 0xFC, 0x49,
    0x20, 0x42, 0x48, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x08, 0x08, 0x49,
    0x20, 0x81, 0xB0, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x08, 0x10, 0x36,
    0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x92, 0x08, 0x01, 0xE1, 0x0E, 0x38, 0xE3, 0x83, 0x80, 0x01, 0x00, 0x09, 0x00, 0x00,
    0x08, 0x80, 0x12, 0x00, 0x01, 0x12, 0x90, 0x45, 0x04, 0x44, 0x40, 0x01, 0x00, 0x09, 0x00, 0x00,
    0x08, 0xA2, 0x97, 0x09, 0xE1, 0x12, 0x90, 0x45, 0x00, 0x44, 0x0E, 0x7B, 0xB9, 0xC9, 0x1C, 0xE0,
    0x0F, 0x22, 0x92, 0x09, 0x11, 0xE7, 0xDE, 0x3D, 0xE3, 0x84, 0x11, 0x45, 0x22, 0x29, 0x22, 0x80,
    0x08, 0xA2, 0x92, 0x69, 0x11, 0x44, 0x51, 0x05, 0x10, 0x44, 0x11, 0x45, 0x22, 0x29, 0x3E, 0x80,
    0x08, 0xA2, 0x92, 0x09, 0x11, 0x24, 0x51, 0x05, 0x14, 0x44, 0x51, 0x45, 0x22, 0x29, 0x20, 0x80,
    0x0F, 0x1E, 0x93, 0x09, 0x11, 0x14, 0x4E, 0x38, 0xE3, 0x83, 0x8E, 0x45, 0xA1, 0xC9, 0x1E, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x1C, 0x70, 0x3C, 0x80, 0x07, 0x00, 0x00, 0x00, 0x04, 0x80, 0x40, 0x1E, 0x78, 0xE0, 0x00,
    0x00, 0x22, 0x88, 0x22, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0x80, 0x40, 0x10, 0x41, 0x10, 0x00,
    0x00, 0x02, 0x88, 0x22, 0x9E, 0x00, 0x9D, 0x8E, 0xC1, 0xE5, 0xCE, 0x78, 0x10, 0x41, 0x00, 0x00,
    0x00, 0x04, 0x88, 0x3C, 0x91, 0x01, 0x12, 0x49, 0x21, 0x14, 0x91, 0x44, 0x1E, 0x79, 0x00, 0x00,
    0x00, 0x08, 0x88, 0x20, 0x91, 0x02, 0x12, 0x49, 0x21, 0x14, 0x90, 0x44, 0x10, 0x41, 0x00, 0x00,
    0x00, 0x10, 0x88, 0x20, 0x91, 0x04, 0x12, 0x49, 0x21, 0x14, 0x91, 0x44, 0x10, 0x41, 0x10, 0x00,
    0x00, 0x3E, 0x70, 0x20, 0x91, 0x0F, 0x92, 0x49, 0x21, 0xE4, 0xCE, 0x44, 0x10, 0x40, 0xE0, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x07, 0x80, 0x49, 0x04, 0x00, 0x3C, 0x07, 0xC0, 0xE1, 0xE3, 0xC3, 0xC4, 0x10, 0x78, 0x00, 0x20,
    0x04, 0x40, 0x09, 0x00, 0x00, 0x20, 0x00, 0x41, 0x12, 0x12, 0x24, 0x26, 0x30, 0x40, 0x00, 0x20,
    0x04, 0x51, 0x4B, 0x84, 0xF0, 0x79, 0x10, 0x81, 0x02, 0x02, 0x24, 0x26, 0x30, 0x41, 0xCF, 0x70,
    0x07, 0x91, 0x49, 0x04, 0x88, 0x44, 0xA0, 0x81, 0x02, 0x73, 0xC4, 0x25, 0x50, 0x7A, 0x28, 0xA0,
    0x04, 0x51, 0x49, 0x04, 0x88, 0x04, 0x41, 0x01, 0x02, 0x12, 0x84, 0x25, 0x50, 0x42, 0x28, 0xA0,
    0x04, 0x51, 0x49, 0x04, 0x88, 0x44, 0xA1, 0x01, 0x12, 0x12, 0x44, 0x24, 0x90, 0x42, 0x28, 0xA0,
    0x07, 0x8F, 0x49, 0x84, 0x88, 0x39, 0x11, 0x00, 0xE1, 0xE2, 0x23, 0xC4, 0x90, 0x41, 0xC8, 0xB0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
#endif

void write_command(uint8_t command)
{
  // select the LCD's command register
  SET_DC;
  // select the LCD controller
  CLR_CS;
  // send the data via parallel
  PORTD = command;
  // clear the write register
  CLR_WR;
  // set the write register
  SET_WR;
  // deselct the LCD controller
  SET_CS;
}
//================================================================================
void write_data(uint8_t data)
{
  // select the LCD's data register
  CLR_DC;
  // select the LCD controller
  CLR_CS;
  // send the data via parallel
  PORTD = data;
  // clear the write register
  CLR_WR;
  // set the write register
  SET_WR;
  // deselct the LCD controller
  SET_CS;
}
//================================================================================

// ************************************************************************* //
void cleardisplay()
{
  int i = HRES * VRES / 8;

  write_data(0x00);
  write_data(0x08);
  write_command(0x24);

  write_command(0xB0); // auto write

  while (i--)
  {
    write_data(0x00);
  }

  write_command(0xB2); // auto write reset
}
// ************************************************************************* //
void cleartext()
{
  write_data(0x00);
  write_data(0x00);
  write_command(0x24);

  write_command(0xB0); // auto write

  for (int row = 0; row < VRES; row++)
  {
    for (int col = 0; col < HRES / 8; col++)
    {
      write_data(0x00);
    }
  }
  write_command(0xB2); // auto write reset
}
// ************************************************************************* //
void display_bitmap(const uint8_t *display)
{

  write_data(0x00);
  write_data(0x08);
  write_command(0x24);

  write_command(0x98); // display mode - graphic on, text off
  write_command(0xB0); // auto write
  int x = 0;

  for (int row = 0; row < VRES; row++)
  {
    for (int col = 0; col < HRES / 8; col++)
    {
      write_data(pgm_read_byte(&display[x]));
      x++;
      delay(0);
    }
  }
  write_command(0xB2); // auto write reset
}
// ************************************************************************* //
void initialize_display()
{
  SET_RESET;
  _delay_ms(10);
  CLR_RESET;
  _delay_ms(100);
  SET_RESET;
  _delay_ms(500);

  write_data(0x00);
  write_data(0x00);
  write_command(0x40); // set text home address

  write_data(0x14); // 240/8
  write_data(0x00);
  write_command(0x41); // set text area

  write_data(0x00);
  write_data(0x08);    // address 0x0800
  write_command(0x42); // set graphic home address

  write_data(HRES / 8);
  write_data(0x00);
  write_command(0x43); // set graphic area

  write_command(0xA0); // 1 line cursor
  write_command(0x81); // mode set - exor mode
  write_command(0x9C); // display mode - graphic on, text on

  write_data(0x00);
  write_data(0x00);
  write_command(0x21); // set cursor position
}
//================================================================================
void setup()
{
  // Set up port directions
  DDRD = 0xff;
  DDRC = 0xff;
  DDRB = 0x3f;
  // Idle the lines in a reasonable state
  PORTD = 0xff;
  SET_RD;
  SET_WR;
  SET_CS;
  delay(1);

  // Initialize the display
  initialize_display();
}
//================================================================================
void loop()
{

  cleartext();
  cleardisplay();
  display_bitmap(logo);
  while (1)
    ;
}
//================================================================================
