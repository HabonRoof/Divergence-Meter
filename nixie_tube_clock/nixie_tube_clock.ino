/* This is Nixie Tube frimeware
   Now it can drive eight nixie tube and display random digits
   Use 74238 for eight tubes anode, and use 4028 for the ten cathod.
   Update for 8 nixie tubes
   Update add RTC clock DS1302
   Update add divergen/time/date function and button 2
   Author: Habonroof
   release date: 2020/02/19
   Version:0.5

   Include DS1302 for DS1302 RTC clock
   Resource:https://github.com/msparks/arduino-ds1302
*/

#include <stdio.h>
#include <DS1302.h>

// ============================== namespace ===========================

namespace {

// Set the appropriate digital I/O pin connections. These are the pin
// assignments for the Arduino as well for as the DS1302 chip. See the DS1302
// datasheet:
//
//   http://datasheets.maximintegrated.com/en/ds/DS1302.pdf


const int kCePin   = A4;  // Chip Enable  Pin#27
const int kIoPin   = 2;  // Input/Output  Pin#4
const int kSclkPin = A5;  // Serial Clock Pin#28

int year;
int mon;
int date;
int hour;
int minute;
int second;


// Create a DS1302 object.
DS1302 rtc(kCePin, kIoPin, kSclkPin);

void time_update() {
  // Get the current time and date from the chip.
  Time t = rtc.time();
  year = t.yr - 2000;
  mon = t.mon;
  date = t.date;
  hour = t.hr;
  minute = t.min;
  second = t.sec;
}

}
// ============================== namespace ===========================

/*
   Button1 -- Change the display mode
   Button2 -- Regenerate the divergence number
   Button3 -- Reset button
   Button status
*/
byte button_1 = 7;  //Pin#13
byte button_2 = A3; //Pin#26
boolean bt1_release = true;

byte display_mode = 0;
/*
   tube connect to 74238 MUX
   Datasheet:https://assets.nexperia.com/documents/data-sheet/74HC_HCT238.pdf
*/

byte tube_a = 8;    //Pin#14
byte tube_b = 9;    //Pin#15
byte tube_c = 10;   //Pin#16
byte tube_EN = 13;  //Pin#19

byte PL = 11;   //Pin#17
byte PR = 12;   //Pin#18

/*
   digit byte connect to 4028 MUX
   Datasheet:https://www.ti.com/lit/ds/symlink/cd4028b.pdf
*/

byte digit_a = 3;   //Pin#5
byte digit_b = 4;   //Pin#6
byte digit_c = 5;   //Pin#11
byte digit_d = 6;   //Pin#12


/*
   Define 8 random number for divergence meter
*/
byte random0;
byte random1;
byte random2;
byte random3;
byte random4;
byte random5;
byte random6;
byte random7;

/*
   Define a counter to count how many times the ramdom number had been displayed
   if random_count smaler than random_time, the tube will keep refresh number
   duration is how long the tube keep lighting(in micro second)
*/
int random_count = 0;
int random_time = 400;
int duration = 1000;

/*
   tube counter to know whitch tube is light up now
*/
byte tube = 0;

/*
   Use oldMicros to verify the delay function, but more accurate

*/
unsigned long oldMicros;
unsigned long last_active_time = 0;
int sleep_min = 0;
/*
   Main setup, set the pin into output mode, and Serial baudrate
*/

void nixie_clock_yrdate();
void nixie_clock_time();
void divergence_meter();
void nixie_sleep();


void setup() {
  pinMode(tube_a, OUTPUT);
  pinMode(tube_b, OUTPUT);
  pinMode(tube_c, OUTPUT);
  pinMode(tube_EN, OUTPUT);

  pinMode(digit_a, OUTPUT);
  pinMode(digit_b, OUTPUT);
  pinMode(digit_c, OUTPUT);
  pinMode(digit_d, OUTPUT);
  pinMode(PL, OUTPUT);
  pinMode(PR, OUTPUT);
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  Serial.begin(115200);
  randomSeed(analogRead(A0)); //Use randomSeed to generate real random number
  // Initialize a new chip by turning off write protection and clearing the
  // clock halt flag. These methods needn't always be called. See the DS1302
  // datasheet for details.
  rtc.writeProtect(false);
  rtc.halt(false);
  // Make a new time object to set the date and time.
  //Time t(2020, 2, 25, 23, 38, 50, Time::kFriday);
  // Set the time and date on the chip.
  //rtc.time(t);

}


/*
   Main function
*/

void loop() {
  if (micros() >= oldMicros) {
    oldMicros = micros() + duration;
    if(millis()>=last_active_time+300000)
      display_mode = 3;
    /*
       We have three modes to display, divergence, time and date. Use button 1 to change display mode
    */
    if (digitalRead(button_1) == 0 && bt1_release == true) {
      last_active_time = millis();
      display_mode ++;
      bt1_release = false;
      //Serial.print("Display Mode is :");
      //Serial.println(display_mode);
      if (display_mode > 2)
        display_mode = 0;
    }

    if (digitalRead(button_1) == 1)
      bt1_release = true;

    switch (display_mode) {
      case 2:
        if (digitalRead(button_2) == 0) {
          random_count = 0;
        }
        divergence_meter();
        //Serial.println("Divergence");

        break;
      case 0:
        nixie_clock_time();
        // Serial.println("Time");
        break;
      case 1:
        nixie_clock_yrdate();
        //Serial.println("Date");
        break;
      case 3:
        nixie_sleep();
        break;
      default:
        nixie_clock_time();
        //Serial.println("Default case");
        break;

    }
    tube++;
    if (tube > 7)
      tube = 0;
    time_update();
  }
}
