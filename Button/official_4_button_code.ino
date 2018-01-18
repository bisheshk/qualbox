
#include<Servo.h>

Servo myservo;
const int taskone = 39;     // the number of the pushbutton pin
const int tasktwo = 41;
const int taskthree = 43;
const int taskfour = 45;

//
// variables will change:
int statetaskone = 0;         // variable for reading the pushbutton status
int statetasktwo = 0;
int statetaskthree = 0;
int statetaskfour = 0;



void setup() {
  pinMode(taskone, INPUT);
  pinMode(tasktwo, INPUT);
  pinMode(taskthree, INPUT);
  pinMode(taskfour, INPUT);

  myservo.attach(3);  //Remember to modify this once you changed the pin for motor, linked with "PWM"
  myservo.write(85);
  Serial.begin(9600);
}
  
void loop() {
    if (statetaskone==0){
      statetaskone = buttonPush(taskone);
     // if(statetaskone==1){Serial.print("one pushed ");}
      }
    if (statetasktwo==0){
      statetasktwo = buttonPush(tasktwo);
     // if(statetasktwo==1){Serial.print("two pushed ");}
      }
    if (statetaskthree==0){
      statetaskthree = buttonPush(taskthree);
     // if(statetaskthree==1){Serial.print("three pushed ");}
      }
    if (statetaskfour==0){
      statetaskfour = buttonPush(taskfour);
     // if(statetaskfour==1){Serial.print("four pushed ");}
      }
 
      
  if(statetaskone && statetasktwo && statetaskthree && statetaskfour){
    myservo.write(180); 
  }
//  else{
//    myservo.write(0);
//  }

  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
//  if (buttonPushCounter % 2 == 0) {
//    digitalWrite(ledPin, HIGH);
//    myservo.write(0); 
//  } else {
//    digitalWrite(ledPin, LOW);
//    myservo.write(90); 
//  }


//   if (buttonState == LOW) { //pushed,servo moving, light off
//    // turn LED on:
//    myservo.write(90); 
//    digitalWrite(ledPin, LOW);
//    
//  } else {   //not pushed,servo not moving, light on
//    digitalWrite(ledPin, HIGH);
//    myservo.write(0);
//    //delay(100);
//    //myservo.write(90);
//    //delay(1000);
//  }
  
  //myservo.write(90);
  //delay(1000);

}

int buttonPush(int button){
 int  buttonState = digitalRead(button);
 int  buttonPushed = 0;
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushed = 1;
      delay(50);
   }
 return buttonPushed;     

}
