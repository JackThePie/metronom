/* Simple metronome using ATMega 328P with Arduino bootloaded.
Buttons for controlling frequency. Buzzer for playing. Display for displaying.
by Jacek Bera */


#include <SPI.h>                          //SPI library
#include <OneButton.h>                    //Contact oscillation library
#define CS 10                             //Shift register on pin 10
OneButton buttonPin(2, true);             //Button 1 on pin 2
OneButton buttonPin2(3, true);            //Button 2 on pin 3

int Cur_tone = 0;
int tones[]={1136, 440};
int a_tone = 7;
int a_tone_state = 0;

int buz = 1;                              //Buzzer on pin 1
int f = 120;                              //Starting frequency 120 bit/s
byte displayArray [10] = {  
  B11000000,    // 0  
  B10100100,    // 2
  B10110000,    // 3
  B10011001,    // 4
  B10010010,    // 5
  B10000010,    // 6
  B11111000,    // 7
  B10000000,    // 8
  B10011000  }; // 9
int first = 4;                         //First digit on pin 4
int second = 5;                            //Second digit on pin 5
int third = 6;                          //Third digit on pin 6       
byte iter1 = 0;                           //Displaying veriable
byte iter2 = 0;
byte iter3 = 0;
long beep_break;                             //Time between beeps
unsigned long nexttick;                   //OneButton library
unsigned char tickstate;

void setup() {    
  pinMode(buz, OUTPUT);                   //In/Out definitions
  pinMode(CS, OUTPUT);
  pinMode(first, OUTPUT);
  pinMode(second, OUTPUT);
  pinMode(third, OUTPUT);
  pinMode(a_tone, INPUT);
  buttonPin.setClickTicks(5);
  buttonPin.attachClick(button_pressed);
  buttonPin2.setClickTicks(5);
  buttonPin2.attachClick(button_pressed2);
  SPI.begin(); 
}

void button_pressed() {                  //Increase speed
  f = f + 2;
  if (f >= 250) {
    f = 250;
  }
}

void button_pressed2() {                //Decrease speed
  f = f - 2;
  if (f <= 40) {
    f = 40;
  }
}

void loop() {
  buttonPin.tick();                     //Waiting for buttons
  buttonPin2.tick();
  
  
  a_tone_state = digitalRead(a_tone);
  if (a_tone_state == HIGH) { Cur_tone = tones[0];}
  digitalWrite(buz, HIGH);
  delayMicroseconds(Cur_tone);
  digitalWrite(buz, LOW);
  delayMicroseconds(Cur_tone);
  
  {
  if (millis() >= nexttick) {            //Beeping
    if (tickstate == LOW) {  
      digitalWrite(buz, HIGH);
      tickstate = HIGH;
    } 
    else {
      digitalWrite(buz, LOW);
      tickstate = LOW;
    }
    nexttick += przerwa;
  }

  przerwa = 30000/f;

  //*********************Display**************************  

  iter1=f/100;
  iter2=(f%100)/10;
  iter3=(f%100)%10;

  digitalWrite(CS, LOW);
  digitalWrite(pierwsza, HIGH);
  SPI.transfer (displayArray[iter2]);
  delay(1);
  digitalWrite(pierwsza, LOW);
  digitalWrite(CS, HIGH);

  digitalWrite(CS, LOW);
  digitalWrite(druga, HIGH);
  SPI.transfer (displayArray[iter3]);
  delay(1);
  digitalWrite(druga, LOW);
  digitalWrite(CS, HIGH);

  digitalWrite(CS, LOW);
  digitalWrite(trzecia, HIGH);
  SPI.transfer (displayArray[iter1]);
  delay(1);
  digitalWrite(trzecia, LOW);
  digitalWrite(CS, HIGH);
}








