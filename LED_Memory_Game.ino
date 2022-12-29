#include <SoftwareSerial.h>
SoftwareSerial bt(8,9); /* Tx, Rx*/

int ledPin[] = {2,3,4,5}; // {GREEN, YELLOW, RED, GREEN}
int outList[] = {};
int randomPin = 0;
int pinInput = "";
char inmsg = "";

void setup() {
  // put your setup code here, to run once:
  bt.begin(9600);               // Bluetooth Module intialization 
  Serial.begin(9600);           // Serial Monitor intialization
  randomSeed(analogRead(0));    // Random Module setup
  for (int i=0; i<5; i++ ){     // Loop to intialize LEDs
    pinMode(ledPin[i], OUTPUT);
  }
}

void check_LED(){
  // Blinks LEDs in sequence so that user can check if all the LEDs are in working condition
  for (int i=0; i<5; i++ ){
    digitalWrite(ledPin[i], HIGH);
    delay(500);
    digitalWrite(ledPin[i], LOW);
    delay(500);
  }
}
void play_LED(){
  /* Randomly blinking LED and adding blink record to a array*/
  for(int i=0;i<6; i++){
    randomPin = random(0,4);
    outList[i] = randomPin;
    digitalWrite(i, HIGH);
    delay(400);
    digitalWrite(i, LOW);
    Serial.println(randomPin);
   
  }
  //Serial.println(outList);
}

void check_input(String in_string){
}

void loop() {
  // put your main code here, to run repeatedly:
  inmsg = "";
  if (bt.available()){
    inmsg = bt.read();
    Serial.println(inmsg);
    if (inmsg == char("K")){
      bt.println("Check if all LEDs are working, If not, Check connections,components");
       check_LED();
    }
     if (inmsg == "PLAY"){
      bt.println("Observe the LED blink pattern");
      play_LED();
      delay(100);
      bt.println("Enter R/G/Y/B in sequence as blinked : ");
      if (bt.available()){
       //CHECK INPUT given by user and verify with list
       pinInput = bt.read();
        
       }
       
    }
  }

}
