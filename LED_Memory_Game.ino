#include <SoftwareSerial.h>
SoftwareSerial bt(8,9); /* Tx, Rx*/

int ledPin[4] = {2,3,4,5}; // {GREEN, YELLOW, RED, GREEN}
char inmsg;
String played_seq;
String entered_seq;


void setup() {
  // put your setup code here, to run once:
  bt.begin(9600);               // Bluetooth Module intialization 
  Serial.begin(9600);           // Serial Monitor intialization
  randomSeed(analogRead(0));    // Random Module setup
  for (int i=0; i<5; i++ ){     // Loop to intialize LEDs
    pinMode(ledPin[i], OUTPUT);
  }
  bt.println("Enter 'P' to play a round of the game.");
}

void check_LED()
{
  // Blinks LEDs in sequence so that user can check if all the LEDs are in working condition
  for (int i=0; i<5; i++ )
  {
    digitalWrite(ledPin[i], HIGH);
    delay(400);
    digitalWrite(ledPin[i], LOW);
    delay(400);
  }
}

String play_LED()
{
  /* Randomly blinking LED and adding blink record to a array*/
  played_seq = "";
  for(int i=0;i<5; i++)
  {
    int randomPin = random(0,4);
    //randomPin = randomPin + 2;
    //Serial.print(randomPin);
    played_seq.concat(randomPin);
    digitalWrite(ledPin[randomPin], HIGH);
    delay(500);
    digitalWrite(ledPin[randomPin], LOW);
    delay(500);
  }
  //Serial.println();
  return played_seq;
}


void loop()
{
  /* Where everything happens */
  String entered_seq = "";
  inmsg = "";
  if(bt.available())
  {
    inmsg = bt.read();
    Serial.println(inmsg);
    if(inmsg=='P')
    {
      Serial.println("Play LED sequence");
      bt.println("Observe the LED blink sequence");
      delay(1000);
      played_seq = play_LED();
      Serial.println("Sequence blinked : " + played_seq);
      bt.println("Enter the sequence (eg: 0123) : ");
      while(entered_seq.length() < 5)
      {
        while(bt.available())
        {
          char character = bt.read();
          entered_seq.concat(character);
        }
      }
      Serial.println("User entered : " + entered_seq);
      if(entered_seq == played_seq)
      {
        bt.println("Great! That is correct.\nPlay another round by entering 'P'.");
        digitalWrite(ledPin[0], HIGH);
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], HIGH);
        digitalWrite(ledPin[3], HIGH);
        delay(200);
        digitalWrite(ledPin[0], LOW);
        digitalWrite(ledPin[1], LOW);
        digitalWrite(ledPin[2], LOW);
        digitalWrite(ledPin[3], LOW);
        delay(300);
        digitalWrite(ledPin[0], HIGH);
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], HIGH);
        digitalWrite(ledPin[3], HIGH);
        delay(200);
        digitalWrite(ledPin[0], LOW);
        digitalWrite(ledPin[1], LOW);
        digitalWrite(ledPin[2], LOW);
        digitalWrite(ledPin[3], LOW);
        delay(300);
        digitalWrite(ledPin[0], HIGH);
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[2], HIGH);
        digitalWrite(ledPin[3], HIGH);
        delay(200);
        digitalWrite(ledPin[0], LOW);
        digitalWrite(ledPin[1], LOW);
        digitalWrite(ledPin[2], LOW);
        digitalWrite(ledPin[3], LOW);
        delay(300);
        
      }
      else
      {
        bt.println("Sorry! What you enterd is wrong.\nTry again by entering 'P'.");
        for (int i=0; i<5; i++ )
          {
            digitalWrite(ledPin[i], HIGH);
            delay(300);
            digitalWrite(ledPin[i], LOW);
            delay(300);
           }
      }
      
    }

    else 
    {
      bt.println("Enter 'P' to play a round of memory game.");
      check_LED();
    }
  }
}
  
