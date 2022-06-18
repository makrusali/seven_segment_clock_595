#include <Arduino.h>
#include "SevenSegment595.h"

SevenSegment595::SevenSegment595(uint8_t data_pin,uint8_t clock_pin,uint8_t latch_pin){
    this->data_pin = data_pin;
    this->clock_pin = clock_pin;
    this->latch_pin = latch_pin;
    this->font = (uint8_t*)base_font;

    this->init();
}

SevenSegment595::SevenSegment595(uint8_t data_pin,uint8_t clock_pin,uint8_t latch_Pin,uint8_t* font){
    this->data_pin = data_pin;
    this->clock_pin = clock_pin;
    this->latch_pin = latch_pin;
    this->font = font;

    this->init();
}

void SevenSegment595::init()
{
    pinMode(this->data_pin,OUTPUT);
    pinMode(this->clock_pin,OUTPUT);
    pinMode(this->latch_pin,OUTPUT);

    this->clear();
}

void SevenSegment595::clear()
{
    for(uint8_t i = 0;i <= this->max_col;++i)
    {
        printData(i,0xFF);
    }
}

void SevenSegment595::scan()
{
    this->colOn();
    
    digitalWrite(this->latch_pin, LOW);
    shiftOut(this->data_pin, this->clock_pin,MSBFIRST,this->data_buff[i]);
    shiftOut(this->data_pin, this->clock_pin,MSBFIRST,(1<<i));
    digitalWrite(this->latch_pin, HIGH);

    ++i;
    if(i > this->max_col){
        i = 0;
    }
}

void SevenSegment595::print(int x,const char* text)
{   
    if (x >= 0)
    {
        for (uint8_t i = x; i <= ((strlen(text) -1) < 7 ? (strlen(text)-1) : 7) ; ++i)
        {            
            this->printData(i,this->font[(text[i - x]) - 48]);
        }
    }
    else {
        
        for (uint8_t i = 0; i <= ((strlen(text) - (x * -1) - 1) < 7 ? (strlen(text) - (x * -1) - 1) : 7 ); ++i)
        {
            this->printData(i,this->font[(text[i + (x * -1)]) - 48]);
        }
    }
}

void SevenSegment595::printData(int x,uint8_t custom_char)
{   
    switch(x){
        case 0:
             this->data_buff[4] = custom_char;
             break;
        case 1:
             this->data_buff[5] = custom_char;
             break;
        case 2:
             this->data_buff[6] = custom_char;
             break;
        case 3:
             this->data_buff[7] = custom_char;
             break;
        case 4:
             this->data_buff[0] = custom_char;
             break;
        case 5:
             this->data_buff[1] = custom_char;
             break;
        case 6:
             this->data_buff[2] = custom_char;
             break;
        case 7:
             this->data_buff[3] = custom_char;
             break;
        default:
            break;
    }
    
}

void SevenSegment595::setColOn(uint8_t col_on){
    this->buff_col_on = col_on;
    this->colOn();
}

void SevenSegment595::colOn(){
    if(!(this->buff_col_on & 0x80)){ this->data_buff[4] |= 0x80; } else { this->data_buff[4] &= ~(0x80); }
    if(!(this->buff_col_on & 0x40)){ this->data_buff[5] |= 0x80; } else { this->data_buff[5] &= ~(0x80); }
    if(!(this->buff_col_on & 0x20)){ this->data_buff[6] |= 0x80; } else { this->data_buff[6] &= ~(0x80); }
    if(!(this->buff_col_on & 0x10)){ this->data_buff[7] |= 0x80; } else { this->data_buff[7] &= ~(0x80); }
    if(!(this->buff_col_on & 0x08)){ this->data_buff[0] |= 0x80; } else { this->data_buff[0] &= ~(0x80); }
    if(!(this->buff_col_on & 0x04)){ this->data_buff[1] |= 0x80; } else { this->data_buff[1] &= ~(0x80); }
    if(!(this->buff_col_on & 0x02)){ this->data_buff[2] |= 0x80; } else { this->data_buff[2] &= ~(0x80); }
    if(!(this->buff_col_on & 0x01)){ this->data_buff[3] |= 0x80; } else { this->data_buff[3] &= ~(0x80); }
}