#include <Arduino.h>
#include "SevenSegment595.h"
#include <TimerOne.h>

/**
 * SevenSegment595(DATA PIN ,CLOCK PIN ,LATCH PIN)
 * */
SevenSegment595 display = SevenSegment595(2,3,4);

void scan(){
  display.scan();
}

void welcomeAnimation(){
  display.setColOn(0b10000001);
  delay(200);
  display.setColOn(0b01000010);
  delay(200);
  display.setColOn(0b00100100);
  delay(200);
  display.setColOn(0b00011000);
  delay(200);

  display.setColOn(0b10000001);
  delay(200);
  display.setColOn(0b01000010);
  delay(200);
  display.setColOn(0b00100100);
  delay(200);
  display.setColOn(0b00011000);
  delay(200);

  //off all col
  display.setColOn(0x00);
  
}

void setup() {
  Serial.begin(9600);
  //display.init();
  Timer1.initialize(500);
  Timer1.attachInterrupt(scan);
  
  welcomeAnimation();

  display.printData(0,0x00);
  delay(2000);

  display.clear();
}

unsigned long pvTime = 0;
int x_pos = 9;

void loop() {
  //for space using @
  //untuk membeeri spasi gunakan sysmbol @
  const char* msg = "SELAMAT@DATANG@TEMAN@TEMAN@@@@@@@@";

  if(millis() - pvTime >= 200){
    pvTime = millis();

    --x_pos;
    if(x_pos == (int)(strlen(msg) * -1)){
      x_pos = 9;
    }
  }

  display.print(x_pos,msg);
}

