#include <memorysaver.h>
#include <UTFT.h>
#define KEY_PIN_BL 2
#define RX_PIN 15
#define TX_PIN 14

// #include <SoftwareSerial.h>

const String BLUETOOTH_NAME = "SCREENAGERS";
const String BLUETOOTH_PASSWORD = "4321";
String text;

// SoftwareSerial BTSerial(RX_PIN, TX_PIN); // BTSerial
String data;


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
const int REFRESH_INTERVAL = 60;
const int MSG_INTERVAL = REFRESH_INTERVAL/2;
const int BUTTON_INTERVAL = MSG_INTERVAL/2;
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
  // pinMode(KEY_PIN_BL, OUTPUT);
  // Set Module to AT mode commands to be able to modify pass and name
//  digitalWrite(KEY_PIN_BL, HIGH);
//  BTSerial.begin(9600);
//  delay(100);
//
//  text = "AT+NAME=";
//  text = String(text + BLUETOOTH_NAME + "\r\n");
//  for (int i = 0; i < text.length(); i++) {
//    BTSerial.write(text[i]);
//  }
//
//  delay(100);
//  text = "AT+PSWD=";
//  text = String(text + BLUETOOTH_PASSWORD + "\r\n");
//  for (int i = 0; i < text.length(); i++) {
//    BTSerial.write(text[i]);
//  }
  Serial.begin(9600);

  
}


void text_update() {
  show_title();
  show_screen();
  check_updates();
}

void msg_update() {
  // check if a signal is received! 
  if (Serial.available()) {
    char received = Serial.read();
    Serial.write(received);
    if (received == '~') {
      Serial.write("We have received: ");
      Serial.write(received+'\n' + data.charAt(0) + data.charAt(1));
      if (data.length() > 40) {
        int offset = data.length() - 40;
        String tmp = "";
        for (int k = offset; k < data.length(); k ++) {
          tmp += data.charAt(k);
        }
        data = tmp;
      } else if (data.length() < 40) {
        String tmp = "";
        for (int k = data.length(); k < 40; k ++) {
          tmp += " ";
        }
        data = tmp;
      }
      message_buffer = data;
      data = "";
    } else {
      data+=received;
    }

  }
  
}

void check_updates() {
  int message_length = message_buffer.length();
  if (message_length >0) {
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

    msg_update();
    if (interval % REFRESH_INTERVAL == 0) {
      interval = 0;
      
      text_update();
    }
    //if (interval % MSG_INTERVAL == 0) {
    //  msg_update();
    //}
    i++;
    interval++;
    
    };
}
