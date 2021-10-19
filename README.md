# RA6963 Demonstration Code
This is Arduino sample code for any display that uses the RA6963-N/N1 controller.

These displays are able to operate in Character mode as well as Graphical mode. In addition to their functional flexibility, they can also be operated at either 3.3V or 5V allowing a wider MCU usage and no requirements for a logic voltage shifter. 


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

