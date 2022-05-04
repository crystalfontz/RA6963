# RA6963 Demonstration Code
This is Arduino sample code for any display that uses the RA6963-N/N1 controller.

These displays are able to operate in Character mode as well as Graphical mode.
In addition to their functional flexibility, they can also be operated at either 3.3V or 5V allowing a wider MCU usage and no requirements for a logic voltage shifter. 




## Connection Guide
```
  ARD      | Port  | Display pin |  Function - 8080 Parallel   |
-----------+-------+-------------+-----------------------------+
 3.3V/5V   |       |             |  POWER 3.3V                 |
 GND       |       |             |  GROUND                     |
-----------+-------+-------------+-----------------------------+
 D8        | PORTB |             |  Chip Enable Signal  (CS)   |
 D9        | PORTB |             |  Reset            (RESET)   |
 D10       | PORTB |             |  Data/Command        (DC)   |
 D11       | PORTB |             |  Write               (WR)   |
 D12       | PORTB |             |  Read                (RD)   |
-----------+-------+-------------+-----------------------------+
Data Lines
-----------+-------+-------------+-----------------------------+
 D0        | PORTD |             |  LCD_D10 (DB0)              |
 D1        | PORTD |             |  LCD_D11 (DB1)              |
 D2        | PORTD |             |  LCD_D12 (DB2)              |
 D3        | PORTD |             |  LCD_D13 (DB3)              |
 D4        | PORTD |             |  LCD_D14 (DB4)              |
 D5        | PORTD |             |  LCD_D15 (DB5)              |
 D6        | PORTD |             |  LCD_D16 (DB6)              |
 D7        | PORTD |             |  LCD_D17 (DB7)              |
-----------+-------+-------------+-----------------------------+
```


Crystalfontz Part Numbers:
CFAG128128I1TMIVZ
CFAG160128BYYHTZ
CFAG160128BTMITZ
CFAG128128AYYHTZ
CFAG24064AYYHTZ
CFAG160128EYYHTZ
CFAG12864DYYHTZ
CFAG240128BTFHTZ
CFAG240128BTMITZ
CFAG240128BTTITZ
CFAG240128BYYHTZ
CFAG16080C1TFHTZ
CFAG16080C1TMITZ
CFAG16080C1YYHTZ
CFAG24064ATTITZ
CFAG24064ATMITZ
CFAG160128E1STITZ

For PNs: CFAG160128EYYHTZ, CFAG160128E1STITZ
see: https://github.com/crystalfontz/CFAG160128E
