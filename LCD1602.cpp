#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#define LCD_CHR  1
#define LCD_CMD  0

#define LINE1  0x80
#define LINE2  0xC0
#define LCD_BACKLIGHT   0x08
// LCD_BACKLIGHT = 0x00

#define ENABLE  0b00000100

int lcdSetup(const int I2C_ADDR);
void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line);
void ClrLcd(void);
void typeln(const char *s);
void typeChar(char val);
int fd;

int lcdSetup(const int I2C_ADDR)   {

  if (wiringPiSetup () == -1) exit (1);
  fd = wiringPiI2CSetup(I2C_ADDR);
  lcd_init();
  return 0;
}

void typeFloat(float myFloat)   {
  char buffer[20];
  sprintf(buffer, "%4.2f",  myFloat);
  typeln(buffer);
}

void typeInt(int i)   {
  char array1[20];
  sprintf(array1, "%d",  i);
  typeln(array1);
}

void ClrLcd(void)   {
  lcd_byte(0x01, LCD_CMD);
  lcd_byte(0x02, LCD_CMD);
}

void lcdLine(int line){
switch(line){
  case 1:
  lcdLoc(LINE1);
  break;
  case 2:
  lcdLoc(LINE2);
  break;
}
}

void lcdLoc(int line)   {
  lcd_byte(line, LCD_CMD);
}

void typeChar(char val)   {
  lcd_byte(val, LCD_CHR);
}

void typeln(const char *s)   {
  while ( *s ) lcd_byte(*(s++), LCD_CHR);
}

void lcd_byte(int bits, int mode)   {
  int bits_high;
  int bits_low;

  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
  bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

  wiringPiI2CReadReg8(fd, bits_high);
  lcd_toggle_enable(bits_high);

  wiringPiI2CReadReg8(fd, bits_low);
  lcd_toggle_enable(bits_low);
}

void lcd_toggle_enable(int bits)   {
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits | ENABLE));
  delayMicroseconds(500);
  wiringPiI2CReadReg8(fd, (bits & ~ENABLE));
  delayMicroseconds(500);
}


void lcd_init()   {
  lcd_byte(0x33, LCD_CMD); 
  lcd_byte(0x32, LCD_CMD); 
  lcd_byte(0x06, LCD_CMD); 
  lcd_byte(0x0C, LCD_CMD); 
  lcd_byte(0x28, LCD_CMD); 
  lcd_byte(0x01, LCD_CMD);
  delayMicroseconds(500);
}