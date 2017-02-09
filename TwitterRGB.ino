/*
 * Twitter Remote Control Robot
 * by Barnabas Nomo <https://github.com/Kowus/twitterControl.git>
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

void setup() {
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
    tempToken = String(buf[it][0]).toInt();
    switch (tempToken) {
      case 1:
        Terminal.println("case " + String(tempToken));
        digitalWrite(blue, LOW);
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);


        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          delay(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          delay(1000);
        }

        break;
      case 2:
        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(red, LOW);
        digitalWrite(blue, HIGH);
        digitalWrite(green, LOW);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          delay(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          delay(1000);
        }
        break;
      case 3:
        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          delay(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          delay(1000);
        }
        break;
      case 4:
        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
        digitalWrite(green, HIGH);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          delay(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          delay(1000);
        }
        break;
      case 5:

        Terminal.print("case " + String(buf[it][0]) + ":\t");
        digitalWrite(red, HIGH);
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
        if (subtokens[it] != NULL) {
          Terminal.println(String(subtokens[it]) + " is Not Null\n");
          delay(subtokens[it]);
        } else {
          Terminal.println(String(subtokens[it]) + " is Null\n");
          delay(1000);
        }
        break;
      default:
        Terminal.print("defaulted: " + String(buf[it][0]) + ": ");
        if (it >= j) {
          Terminal.println("Overflow\texiting...");
          dsw = 0;
          continue;
        }
        else {
          digitalWrite(red, LOW);
          digitalWrite(blue, LOW);
          digitalWrite(green, LOW);
          if (subtokens[it] != NULL) {
            Terminal.println(String(subtokens[it]) + " is Not Null\n");
            delay(subtokens[it]);
          } else {
            Terminal.println(String(subtokens[it]) + " is Null\n");
            delay(1000);
          }
          break;
        }

        break;
    }
    it++;
  }

  Terminal.println("Exited");
}
