
/********************************
Creation Computation: 2016

Assignment one: This is a series of 3 fabric patches that play music if they are pressed. People apply them to themselves, and they
alert ppl if being touched there is a YES, NO, or SURPRISE. 
This version uses the tone library, next will use an SD Card. Mostly just getting the logic down. 

3 buttons. 
3 songs. 
1 button tied to 1 song. 

https://maxoffsky.com/maxoffsky-blog/how-to-play-wav-audio-files-with-arduino-uno-and-microsd-card/   <-- SD WAV tutorial
http://forum.arduino.cc/index.php?topic=198073.0 <-- loop logic

// USE PWM FOR SPEAKER!!
**********************************/

#include <SD.h>                      
#define SD_ChipSelectPin SS       // SS pin on micro  
#include <TMRpcm.h>           
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch

unsigned long lastDebounceTime = 0;     // the last time the output pin was toggled
unsigned long debounceDelay = 20;      // the debounce time; increase if the output flickers
//boolean isPlaying = false;            // tracks if a song is playing or not

boolean wasPlaying = false;
boolean finished = false;
boolean start = false;;

// BUTTON STRUCT //////////////////////////

// http://playground.arduino.cc/Code/ResourceFriendlyStructs
//  http://en.cppreference.com/w/cpp/keyword/struct


struct Button {
  const int btnPin;         // the button Pin
  const int btnLed;         // the button LED
  int songNumber;           // the song number
  int buttonState;          // always 0
  int lastButtonState;      // always 0
};

// array of structs that are buttons, sets the inital value sent to the struct. 
// {pin,LED,songNmber}

struct Button buttons[] = {{2,5,1},{3,6,2},{4,7,3}};

// passing the struct to a function.
void buttonBehaviour(struct Button * button){

  // pointing back to the struct
  // http://playground.arduino.cc/Code/Pointer
  
  int buttonReading = digitalRead(button->btnPin);
  
  if (buttonReading != button->lastButtonState) {
    lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    button->buttonState = buttonReading;
    if (button->buttonState == HIGH){
      digitalWrite(button->btnLed, LOW);
    } else {
      digitalWrite(button->btnLed, HIGH);
      playSongs(button->songNumber);
      //isPlaying = true;
      start = true;
    }
  }
  button->lastButtonState = buttonReading;
}


void setup(){

  Serial.begin(9600);

  // LED PINS ////////////////////////////

  pinMode(buttons[0].btnLed, OUTPUT); // 5
  pinMode(buttons[1].btnLed, OUTPUT); // 6 
  pinMode(buttons[2].btnLed, OUTPUT); // 7

  // INPUT PINS //////////////////////////

  pinMode(buttons[0].btnPin, INPUT_PULLUP); // 2
  pinMode(buttons[1].btnPin, INPUT_PULLUP); // 3
  pinMode(buttons[2].btnPin, INPUT_PULLUP); // 4

  tmrpcm.speakerPin = 9;  // Must be PWM pin

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");
    return;   // don't do anything more if not
  }

  // FLIP ALL THE LEDS ON/OFF TO SHOW THAT SETUP IS DONE.  

  digitalWrite(buttons[0].btnLed, HIGH);
  digitalWrite(buttons[1].btnLed, HIGH);
  digitalWrite(buttons[2].btnLed, HIGH);
  delay(2000);
  digitalWrite(buttons[0].btnLed, LOW);
  digitalWrite(buttons[1].btnLed, LOW);
  digitalWrite(buttons[2].btnLed, LOW);

}

void loop(){

  buttonBehaviour(&buttons[0]); // 2
  buttonBehaviour(&buttons[1]); // 3
  buttonBehaviour(&buttons[2]); // 4

  // shut off the audio when its done.

  if(tmrpcm.isPlaying()){
    while(tmrpcm.isPlaying());
    tmrpcm.stopPlayback();
  }
  Serial.flush();   // flush your serial
}

void playSongs(int s){
  int songID = s;

  // as long as a song is playing. wasPlaying == true.
  // this will loop, because its in the loop (sorta, its in the struct, which is referenced in the loop)

  if(wasPlaying == true) {
    Serial.println("Completed playback.");
    wasPlaying = false;
    finished = true;
    start = false;
  }

  if(songID == 1){
    Serial.println("NO");
    tmrpcm.play("ring2.wav");
  } else if(songID == 2){
    Serial.println("YES");
    tmrpcm.play("pingding.wav");
  }else if(songID == 3){
    Serial.println("SURPRISE");
    tmrpcm.play("6.wav");
  }
  
  wasPlaying = true;  
  
}

/// Save old code for now ///////

//Serial.println("songID");
  //Serial.println(songID);
  /*switch (songID) {
      case 1:
        Serial.println("NO");
        break;
      case 2:
        // do something
        Serial.println("YES");
        break;
      case 3:
        // do something
        Serial.println("SURPRISE");
      default:
        break;
  }
  isPlaying = false;  // set the boolean back to false. */

/*if(songID == 1 ){
    Serial.println("NO");
    delay(2000);  // song or function would go here instead of delay
  } else if(songID == 2){
    Serial.println("YES");
    delay(2000);  // song or function would go here instead of delay
  } else if(songID == 3){
    Serial.println("SURPRISE");
    delay(2000);  // song or function would go here instead of delay
  }*/


