// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module

//#include <VirtualWire.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

const byte PIN_BUTTON_SELECT = 8;

const byte PIN_BUTTON_F = 7;
const byte PIN_BUTTON_E = 6;

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 2;
const byte PIN_BUTTON_DOWN = 4;
const byte PIN_BUTTON_LEFT = 5;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

RH_ASK driver;

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_BUTTON_RIGHT, INPUT);
  digitalWrite(PIN_BUTTON_RIGHT, HIGH);

  pinMode(PIN_BUTTON_LEFT, INPUT);
  digitalWrite(PIN_BUTTON_LEFT, HIGH);

  pinMode(PIN_BUTTON_UP, INPUT);
  digitalWrite(PIN_BUTTON_UP, HIGH);

  pinMode(PIN_BUTTON_DOWN, INPUT);
  digitalWrite(PIN_BUTTON_DOWN, HIGH);

  pinMode(PIN_BUTTON_SELECT, INPUT);
  digitalWrite(PIN_BUTTON_SELECT, HIGH);

  pinMode(PIN_BUTTON_E, INPUT);
  digitalWrite(PIN_BUTTON_E, HIGH);

  pinMode(PIN_BUTTON_F, INPUT);
  digitalWrite(PIN_BUTTON_F, HIGH);

  if (!driver.init())
    Serial.println("init failed");

  /*vw_setup(2000);
  vw_set_rx_pin(9);
  vw_set_tx_pin(10);*/
}

void loop()
{
  unsigned long data_ = 0;
  int sum1 = 0, sum2 = 0, check1 = 0, check2 = 0;
  char *str = "000000";

  // assemble joystick data into long integer: 0010 XXXX XXXX XXYY YYYY YYYY RLUD SFE_

 // data_ = long(data_ | long(0b0010) << 28); //start of text
  data_ = long(data_ | long(analogRead(PIN_ANALOG_X)) << 22); //22
  data_ = long(data_ | long(analogRead(PIN_ANALOG_Y)) << 12); //12
  data_ = long(data_ | long(digitalRead(PIN_BUTTON_RIGHT)) << 11); //11
  data_ = long(data_ | long(digitalRead(PIN_BUTTON_LEFT)) << 10);
  data_ = long(data_ | long(digitalRead(PIN_BUTTON_UP)) << 9);
  data_ = long(data_ | long(digitalRead(PIN_BUTTON_DOWN)) << 8);
  data_ = long(data_ | long(digitalRead(PIN_BUTTON_SELECT)) << 7);
  data_ = long(data_ | long(digitalRead(PIN_BUTTON_F)) << 6);
  data_ = long(data_ | long(digitalRead(PIN_BUTTON_E)) << 5); //5

  //checksum

  for (int i = 0; i < 32; i++) {
    sum1 = (sum1 + bitRead(data_, i)) % 255;
    sum2 = (sum2 + sum1) % 255;
  }

  check1 = 255 - ((sum1 + sum2) % 255);
  check2 = 255 - ((check1 + sum1) % 255);
  

  // split long into 4 bytes (4 x 8 bits) for serial transmit
  char first = data_ >> 24;
  char second = (data_ & 0x00FF0000) >> 16;
  char third = (data_ & 0x0000FF00) >> 8;
  char forth = (data_ & 0x000000FF);

  str[0] = first;
  str[1] = second;
  str[2] = third;
  str[3] = forth;
  str[4] = check1;
  str[5] = check2;
  
  for (int i = 31; i > 0; i--)
    Serial.print(bitRead(data_, i), BIN);
  Serial.println(" ");
  Serial.println("XXXXXXXXXXYYYYYYYYYYRLUDSFE_____");

  
  for (int i=0; i< 4; i++){
    for (int j=7; j>=0; j--)
      Serial.print(bitRead(str[i],j),BIN);
  }
  Serial.println("=");
  Serial.println(first,BIN);
  /*vw_send((uint8_t *)str, strlen(str));
  vw_wait_tx(); */
  delay(10);
}
