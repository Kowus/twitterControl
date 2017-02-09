# Twitter Control by Barnabas Nomo
## Example on how to control a robot from Twitter by typing #kofecode and issuing a couple of commands.

### Application Cases
1. type #kofecode to enable trigger watch on current tweet
2. :1 :2 :3 :4 :5 to specify dotion in different directions (forward, right, backward, left, and stop respectively)
3. Takes an option and converts it to an integer to determine how long to execute a specific command. 

>            Eg. #kofecode :1-2000 :2-450 :4-450 :3-2000 :1-6000 
>            will cause the robot to move forward for 2 seconds, 
>            turn right for 450ms, turn left for 450ms, 
>            move backwards for 2 seconds and move forward for 6 seconds;
>>          In case an option is not stated with any of the : 
>>          commands,  :1 or :2 will have a delay of 2000, 
>>          :2 and :4 will have a delay of 450
            

Hardware
============

1. Arduino Uno
2. One SHEELD Multipurpose Shield
3. RGB LED
4. Assembled Robot kit 

> # **Note:**
>           This Tutorial will not cover assembling the robot kit. 
>           It will only cover how to use ONE SHEELD's twitter 
>           interface to queue commands to control your robot


### [Download the OneSheeld library and App](http://1sheeld.com/downloads/)

Using The Stock Twitter Example
========

```arduino
/*

Twitter Shield Example

This example shows an application on 1Sheeld's Twitter shield.

By using this example, you can flash a LED once a certain keyword
is mentioned on Twitter.

OPTIONAL:
To reduce the library compiled size and limit its memory usage, you
can specify which shields you want to include in your sketch by
defining CUSTOM_SETTINGS and the shields respective INCLUDE_ define. 

*/

#define CUSTOM_SETTINGS
#define INCLUDE_TWITTER_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* A name for led on pin 13. */
int ledPin = 13;
/* A variable to track number of tracked tweets returned. */
int trackingCounter = 0;

void setup() {
  /* Start communication. */
  OneSheeld.begin();
  /* Set the LED pin as output. */
  pinMode(ledPin,OUTPUT);
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
  Twitter.trackKeyword("1Sheeld");
}

void myTweet(char * userName , char * userTweet)
{
    /* Check if the tweet has 1Sheeld keyword. */
    if(strstr(userTweet,":1")!=0)
    {
      /* Turn on the LED. */
      digitalWrite(ledPin,HIGH);
      /* Use OneSheeld delay for better performance. */
      OneSheeld.delay(1000);
      /* Increment the counter. */
      trackingCounter++;
      /* Turn off the LED. */
      digitalWrite(ledPin,LOW);
    }
    /* Check if the counter reached three times. */
    if(trackingCounter == 3)
    {
      /* Stop tracking the word 1Sheeld. */
      Twitter.untrackKeyword("1Sheeld");
      /* Reset the counter. */
      trackingCounter = 0;
    }
}
```

This simple example allows you to Track a specific (**in this case _:1_**) keyword in your posts, and if it contains a specific keyword, the led turns on.



What if we wanted to check for multiple keywords?
============

>    The above example will not work because `strstr()` will only check if 
>    **:1** exists in the string, and depending on how you structure your if 
>    statements, the code will do every instance once even if you had each 
>    keyword multiple entered multiple times.
>>  ## Example: 
>>              OneSheeld :1 :2 :3 :4 :5 :1 :1 :3 :4
>>      Using strstr() will only check for :1 once.

# Solution
> I will brush through the code quickly the code is heavily commented 
> to explain what is happening at what point. 

```arduino
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
```

set the motor pins to OUTPUT, begin OneSheeld instance and write to phone terminal: waitiing for tweet...
```arduino
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
```

Leave the void loop blank
```arduino
void loop()
{
  /* Leave the loop empty. */
}
```
create shieldSelection function to track keyword
```arduino
void shieldSelection()
{
  /* Track hashtag #kofecode on Twitter. */
  Twitter.trackKeyword("#kofecode");
}
```

```arduino
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
      Terminal.println("Token "+String(j) + " = " + String(buf[j][0]) + \tSubtoken = " + String(buf[j][1]));
      subtokens[j] = String(buf[j][1]).toInt();
      OneSheeld.delay(100);
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
```


### Motor Functions
```arduino
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
  OneSheeld.delay(time);
}

void backward(int time)
{
  brake(50);
  motorABackward();
  motorBBackward();
  OneSheeld.delay(time);
}

void turnLeft(int time)
{
  brake(50);
  motorABackward();
  motorBForward();
  OneSheeld.delay(time);
}

void turnRight(int time)
{
  brake(50);
  motorAForward();
  motorBBackward();
  OneSheeld.delay(time);
}


void brake(int time)
{
  motorABrake();
  motorBBrake();
  OneSheeld.delay(time);
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
```

# Altogether now

```arduino
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
  /* Track hashtag #kofecode on Twitter. */
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
      Terminal.println("Token " + String(j) + " = " + String(buf[j][0]) + "\tSubtoken = ") + String(buf[j][1]));
      subtokens[j] = String(buf[j][1]).toInt();
      OneSheeld.delay(100);
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
  OneSheeld.delay(time);
}

void backward(int time)
{
  brake(50);
  motorABackward();
  motorBBackward();
  OneSheeld.delay(time);
}

void turnLeft(int time)
{
  brake(50);
  motorABackward();
  motorBForward();
  OneSheeld.delay(time);
}

void turnRight(int time)
{
  brake(50);
  motorAForward();
  motorBBackward();
  OneSheeld.delay(time);
}


void brake(int time)
{
  motorABrake();
  motorBBrake();
  OneSheeld.delay(time);
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
```



