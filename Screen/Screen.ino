#include <memorysaver.h>
#include <UTFT.h>

// UTFT_ViewFont 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the included fonts.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>


// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Inconsola[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ILI9341_16, 52,50,48,46);

int interval;
const int REFRESH_INTERVAL = 30;
const int Y_MAX = 240;
const int PAD = 25;
const int TASKS = 4;
const int Y_MIN = 20;


static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{
    return alphanum[rand() % stringLength];
}

void make_green() {
  myGLCD.setColor(0, 255, 0);
}

void make_blue() {
  myGLCD.setColor(21, 113, 207);
}

struct display_text {
    int pos;
    String message;
};

String title = "To-Do";

String message_buffer;

struct display_text message_queue[TASKS] = {
  {0, "sample"},
  {1, "this"},
  {2, "screen"},
  {3, "bump"},
};

void show_title() {
  make_green();
  myGLCD.print(title, CENTER, 0);
}
void show_screen() {
  make_blue();
  int current_y = Y_MIN;
  for (int i = 0; i < TASKS; i ++) {
    current_y += PAD;
    String current_message = message_queue[i].message;
    myGLCD.print(current_message, LEFT, current_y);
    current_y +=PAD;
  }
}

void update_message(int id, String text) {
  message_queue[id] = {id, text};
}

void remove_message(int id) {
  message_queue[id] = {id, ""};
}


void setup()
{
  myGLCD.InitLCD();
  interval = 1;
  
  myGLCD.clrScr(); 
}


void text_update() {
  show_title();
  show_screen();
  check_updates();
}

void check_updates() {
  int message_length = message_buffer.length();
  if (message_length == 40) {
    String build_str = "";
    for (int i = 0; i < 10; i++) {
      build_str += message_buffer[i];
    }
    update_message(0, build_str);
    build_str = "";
    for (int i = 10; i < 20; i++) {
      build_str += message_buffer[i];
    }
    update_message(1, build_str);
    build_str = "";
    for (int i = 20; i < 30; i++) {
      build_str += message_buffer[i];
    }
    update_message(2, build_str);
    build_str = "";
    for (int i = 30; i < 40; i++) {
      build_str += message_buffer[i];
    }
    update_message(3, build_str);
    message_buffer = "";
  }
}

void loop()
{
  myGLCD.setColor(0, 255, 0);
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.setFont(Inconsola);
  int i = 0;
  while(1) {
    if (interval % REFRESH_INTERVAL == 0) {
      interval = 0;
      String test = "";
      for (int j = 0; j < 40; j ++) {
        test += genRandom();
      }
      message_buffer = test;
      test = "";
      // update_message(1, String(i));
      text_update();
    }
    i++;
    interval++;
    
    };
}

  
  // myGLCD.setColor(0, 255, 0);
  // myGLCD.setBackColor(0, 0, 0);

  // myGLCD.setFont(Inconsola);
  // myGLCD.print("Eat your snack!", LEFT, 0);
  // if (i%30 == 0) {
  //   myGLCD.print("AAAAHHHHH!!!!", LEFT, 32); 
  //   myGLCD.clrScr();
  // }

  // myGLCD.print("@ABCDEFGHIJKLMNO", CENTER, 32);
  // myGLCD.print("PQRSTUVWXYZ[\\]^_", CENTER, 48);
  // myGLCD.print("`abcdefghijklmno", CENTER, 64);
  // myGLCD.print("pqrstuvwxyz{|}~ ", CENTER, 80);

  // myGLCD.setFont(SmallFont);
  // myGLCD.print(" !\"#$%&'()*+,-./0123456789:;<=>?", CENTER, 120);
  // myGLCD.print("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", CENTER, 132);
  // myGLCD.print("`abcdefghijklmnopqrstuvwxyz{|}~ ", CENTER, 144);

  // myGLCD.setFont(SevenSegNumFont);
  // myGLCD.print("0123456789", CENTER, 190);
