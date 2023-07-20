# RA6963 Demonstration Code
This is Arduino sample code for any display that uses the RA6963-N/N1 controller.

These displays are able to operate in Character mode as well as Graphical mode.
In addition to their functional flexibility, they can also be operated at either 3.3V or 5V allowing a wider MCU usage and no requirements for a logic voltage shifter. To easily bring up these displays, we recommend using our [LCD starter kit](https://www.crystalfontz.com/product/devkit001-lcd-starter-kit-with-potentiometer) which has all the components required to do so.




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
[CFAG128128I1TMIVZ](https://www.crystalfontz.com/product/cfag128128i1tmivz-128x128-stn-blue-graphic-lcd-display), 
[CFAG160128BYYHTZ](https://www.crystalfontz.com/product/cfag160128byyhtz-sunlight-readable-160x128-lcd), 
[CFAG160128BTMITZ](https://www.crystalfontz.com/product/cfag160128btmitz-graphical-160x128-display-module-lcd), 
[CFAG128128AYYHTZ](https://www.crystalfontz.com/product/cfag128128ayyhtz-128x128-graphic-lcd), 
[CFAG24064AYYHTZ](https://www.crystalfontz.com/product/cfag24064ayyhtz-240x64-lcd-module-graphical), 
[CFAG160128EYYHTZ](https://www.crystalfontz.com/product/cfag160128eyyhtz-lcd-160x128-display-module), 
[CFAG12864D1YYHTZ](https://www.crystalfontz.com/product/cfag12864d1yyhtz-sunlight-readable-graphic-lcd), 
[CFAG240128BTFHTZ](https://www.crystalfontz.com/product/cfag240128btfhtz-graphic-lcd-240x128-display-module), 
[CFAG240128BTMITZ](https://www.crystalfontz.com/product/cfag240128btmitz-lcd-module-graphical-240x128), 
[CFAG240128BTTITZ](https://www.crystalfontz.com/product/cfag240128bttitz-240x128-graphic-lcd), 
[CFAG240128BYYHTZ](https://www.crystalfontz.com/product/cfag240128byyhtz-lcd-module-graphical-240x128), 
[CFAG16080C1TFHTZ](https://www.crystalfontz.com/product/cfag16080c1tfhtz-160x80-graphic-lcd-module), 
[CFAG16080C1TMITZ](https://www.crystalfontz.com/product/cfag16080c1tfhtz-160x80-graphic-lcd-module), 
[CFAG16080C1YYHTZ](https://www.crystalfontz.com/product/cfag16080c1yyhtz-160x80-lcd-graphical), 
[CFAG24064ATTITZ](https://www.crystalfontz.com/product/cfag24064attitz-240x64-display-module-graphic), 
[CFAG24064ATMITZ](https://www.crystalfontz.com/product/cfag24064atmitz-240x64-graphic-lcd), 
[CFAG160128E1STITZ](https://www.crystalfontz.com/product/cfag160128e1stitz-white-on-dark-blue-160x128-graphic-lcd)

For PNs: [CFAG160128EYYHTZ](https://www.crystalfontz.com/product/cfag160128eyyhtz-lcd-160x128-display-module), [CFAG160128E1STITZ](https://www.crystalfontz.com/product/cfag160128e1stitz-white-on-dark-blue-160x128-graphic-lcd)
see: https://github.com/crystalfontz/CFAG160128E
