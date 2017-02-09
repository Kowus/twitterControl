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

Using The Simple Twitter Example
========

```cpp
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

## What if we wanted to check for multiple keywords?

>    The above example will not work because `strstr()` will only check if 
>    **:1** exists in the string, and depending on how you structure your if 
>    statements, the code will do every instance once even if you had each 
>    keyword multiple entered multiple times.
>>  ## Example: 
>>              OneSheeld :1 :2 :3 :4 :5 :1 :1 :3 :4
>>      Using strstr() will only check for :1 once.
