/*
   Twitter Remote Control Robot
   by Barnabas Nomo <https://github.com/Kowus/twitterControl.git>
  To reduce the library compiled size and limit its memory usage, you
  can specify which shields you want to include in your sketch by
  defining CUSTOM_SETTINGS and the shields respective INCLUDE_ define.
*/

#define CUSTOM_SETTINGS
#define INCLUDE_TWITTER_SHIELD
#define INCLUDE_TERMINAL_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* A variable to track number of tracked tweets returned. */
//int trackingCounter = 0;
char *str1, *token, *subToken, *saveptr1, *saveptr2;
int j, it = 0, dsw = 0, i = 0, subtokens[30];
int red = 13, blue = 12, green = 9;

char *buf[80][1];


// Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)
int enableA = 11;
int pinA1 = 6;
int pinA2 = 5;

//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableB = 10;
int pinB1 = 4;
int pinB2 = 3;


void setup() {
  //  Set Motor Pin Behaviours
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);

  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
  /* Start communication. */
  OneSheeld.begin();
  Terminal.println("Waiting for tweet...");
  /* Subscribe to setOnSelected event for the Twitter shield. */
  Twitter.setOnSelected(&shieldSelection);
  /* Subscribe to onNewTweet event. */
  Twitter.setOnNewTweet(&myTweet);

}

void loop()
{
  /* Leave the loop empty. */
}

void shieldSelection()
{
  /* Track keyword 1Sheeld on Twitter. */
  Twitter.trackKeyword("#kofecode");
}

void myTweet(char * userName , char * userTweet)
{
  for (j = 0, str1 = userTweet; ; j++, str1 = NULL) {
    token = strtok_r(str1, ":", &saveptr1);
    if (token == NULL) {
      dsw = 1;
      break;
    }
    buf[j][0] = token;
    for (i = 0; ; i++, token = NULL) {
      subToken = strtok_r(token, "-", &saveptr2);
      if (subToken == NULL)break;
      buf[j][i] = subToken;
      Terminal.println("Token " + String(j) + " = " + String(buf[j][0]) + String("\t\t\tSubtoken = ") + String(buf[j][1]));
      subtokens[j] = String(buf[j][1]).toInt();
      delay(100);
    }
  }
  int tempToken = 0;
  Terminal.println("\n\n       Blank       \n\n");

  while (dsw) {
    enableMotors();
    tempToken = String(buf[it][0]).toInt();
    switch (tempToken) {
      case 1:
        Terminal.println("case " + String(tempToken));
        digitalWrite(blue, LOW);
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);


        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          forward(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          forward(3000);
        }

        break;
      case 2:
        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(red, LOW);
        digitalWrite(blue, HIGH);
        digitalWrite(green, LOW);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          turnRight(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          turnRight(2700);
        }
        break;
      case 3:
        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          backward(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          backward(3000);
        }
        break;
      case 4:
        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
        digitalWrite(green, HIGH);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          turnLeft(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          turnLeft(2700);
        }
        break;
      case 5:

        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(red, HIGH);
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          brake(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          brake(1000);
        }
        break;
      default:
        Terminal.print("defaulted: " + String(buf[it][0]) + ": ");
        if (it >= j) {
          Terminal.println("Overflow\texiting...");
          brake(100);
          dsw = 0;

          disableMotors();
          continue;
        }
        else {
          digitalWrite(red, LOW);
          digitalWrite(blue, LOW);
          digitalWrite(green, LOW);
          if (subtokens[it] != NULL) {
            Terminal.println(String(subtokens[it]) + " is Not Null\n");
            forward(subtokens[it]);
          } else {
            Terminal.println(String(subtokens[it]) + " is Null\n");
            forward(1000);
          }
          break;
        }

        break;
    }
    it++;
  }
  it=0;
  Terminal.println("Exited");
}







void enableMotors()
{
  motorAOn();
  motorBOn();
}

void disableMotors()
{
  motorAOff();
  motorBOff();
}

void forward(int time)
{
  brake(50);
  motorAForward();
  motorBForward();
  delay(time);
}

void backward(int time)
{
  brake(50);
  motorABackward();
  motorBBackward();
  delay(time);
}

void turnLeft(int time)
{
  brake(50);
  motorABackward();
  motorBForward();
  delay(time);
}

void turnRight(int time)
{
  brake(50);
  motorAForward();
  motorBBackward();
  delay(time);
}


void brake(int time)
{
  motorABrake();
  motorBBrake();
  delay(time);
}
//Define low-level H-bridge commands

//enable motors
void motorAOn()
{
  digitalWrite(enableA, HIGH);
}

void motorBOn()
{
  digitalWrite(enableB, HIGH);
}

//disable motors
void motorAOff()
{
  digitalWrite(enableB, LOW);
}

void motorBOff()
{
  digitalWrite(enableA, LOW);
}

//motor A controls
void motorAForward()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
}

void motorABackward()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
}

//motor B controls
void motorBForward()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
}

void motorBBackward()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
}


void motorABrake()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
}
void motorBBrake()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
}
