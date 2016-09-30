
/********************************
Creation Computation. 
Assignment one: Make something basic using Fabric, Button, Buzzer. 
This is a soft switch fabric that plays a song when you squeeze it. 

http://www.princetronics.com/supermariothemesong/ <-- the awesome mario themes
https://vine.co/v/5rDU6UenUbH

// too do: maybe make this a randomized music thing. 
// Maybe use more than one button, like a piano. 
// maybe use two buzzers?
// maybe use two buttons that play with pitch of tone rather than just a melody?

***********************/

#include "pitches.h"
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int ledPin2 = 12;
const int buzzerPin = 8;

boolean isPlaying = false;

int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 20;    // the debounce time; increase if the output flickers

int marioMelody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

int marioTempo[] = {
  10, 10, 10, 10,
  10, 10, 10, 10,
  10, 10, 10, 10,
  10, 10, 10, 10,

  10, 10, 10, 10,
  10, 10, 16, 10,
  10, 10, 10, 10,
  10, 10, 10, 10,

  8, 8, 8,
  10, 10, 10, 10,
  10, 10, 10, 10,
  10, 10, 10, 10,

  10, 10, 10, 10,
  10, 10, 16, 10,
  10, 10, 10, 10,
  10, 10, 10, 10,

  8, 8, 8,
  10, 10, 10, 10,
  10, 10, 10, 10,
  10, 10, 10, 10,
};


int starWarsMelody [] = {
  NOTE_F4, NOTE_F4, NOTE_F4,  
  NOTE_AS4, NOTE_F5,
  
  NOTE_DS5, NOTE_D5, NOTE_C5, 
  NOTE_AS5, NOTE_F5,
   
  NOTE_DS5,  NOTE_D5,  NOTE_C5, 
  NOTE_AS5, NOTE_F5,
   
  NOTE_DS5, NOTE_D5, NOTE_DS5, 
  NOTE_C5
};

// still kinda meh, but works. 
int starWarsTempo [] = {
  8,  8, 8,  
  2, 4, 
  8,  8,  8, 
  2, 4,  
  8,  8,  8, 
  2, 4, 
  8, 8,  8, 
  2
};

int previousSong;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  //pinMode(buttonPin, INPUT
  pinMode(buttonPin, INPUT_PULLUP);  // don't use a pull down on this. 
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);

  previousSong = random(1, 3); // pick a random number between 1 and 2
  //Serial.println(previousSong);
  //Serial.println("setup done");
}

void loop() {

  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if(buttonState == LOW && !isPlaying){
        
        
        // don't play the same song twice in a row. 
        if(previousSong == 1){
          digitalWrite(ledPin, HIGH);
          playSong(2);
        } else if(previousSong == 2){
          digitalWrite(ledPin2, HIGH);
          playSong(1);
        } 

      } else {
        digitalWrite(ledPin, LOW);
        digitalWrite(ledPin2, LOW);
      }
    }
  }
  lastButtonState = reading;
}

void playSong(int s){
  Serial.println("PlaySong: "+s);
  int song = s;
  

  if(song == 2){
    previousSong = 2;

    Serial.println(" Mario Theme");
    int size = sizeof(marioMelody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++){
      int noteDuration = 1000 / marioTempo[thisNote];
      tone(buzzerPin, marioMelody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(buzzerPin);
    }
    

  } else if(song == 1) {
    previousSong = 1;
    Serial.println("star wars?");
    int size = sizeof(starWarsTempo) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++){
      int noteDuration = 1350 / starWarsTempo[thisNote];
      tone(buzzerPin, starWarsMelody[thisNote],noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(buzzerPin);
    }
  } 

  isPlaying = false;
   
} // end of playSong