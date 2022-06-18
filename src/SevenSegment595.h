#include <Arduino.h>

#ifndef  SEVSEG595_H
#define SEVSEG595_H

/**
 * Only number and capital letters
 * */
const uint8_t base_font[] = {
  0xC0,//0
  0xF9,//1
  0xA4,//2
  0xB0,//3
  0x99,//4
  0x92,//5
  0x82,//6
  0xF8,//7
  0x80,//8
  0x90,//9
  0,
  0,
  0,
  0,
  0,
  0,
  0xFF,//OFF
  0x88,//A
  0x83,//B
  0xC6,//C
  0xA1,//D
  0x86,//E
  0x8E,//F
  0x90,//G
  0x89,//H
  0xF9,//I
  0xF1,//J
  0x8A,//K
  0xC7,//L
  0xEA,//M
  0xAB,//N
  0xC0,//O
  0x8C,//P
  0x98,//Q
  0xAF,//R
  0x92,//S
  0x87,//T
  0xE3,//U
  0xC1,//V
  0xD5,//W
  0x89,//X
  0x91,//Y
  0xA4 //Z
};

class SevenSegment595
{
private:
    uint8_t data_buff[8];
    uint8_t* font;
    uint8_t clock_pin;
    uint8_t latch_pin;
    uint8_t data_pin;
    uint8_t i = 0;
    const uint8_t max_col = 7;
    uint8_t buff_col_on;

    void init();
    void colOn();

public:
    SevenSegment595(uint8_t data_pin,uint8_t clock_pin,uint8_t latch_pin);

    SevenSegment595(uint8_t data_pin,uint8_t clock_pin,uint8_t latch_Pin,uint8_t* font);

    void clear();

    void scan();

    void print(int x,const char* text);

    void printData(int x,uint8_t custom_char);

    void setColOn(uint8_t col_on);

    
};





#endif