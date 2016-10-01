
/********************************
Creation Computation: 2016

Assignment one: This is a series of 3 fabric patches that play music if they are pressed. People apply them to themselves, and they
alert ppl if being touched there is a YES, NO, or SURPRISE. 
This version uses the tone library, next will use an SD Card. Mostly just getting the logic down. 
3 buttons. 
3 songs. 
1 button tied to 1 song. 
***********************/

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 20;    // the debounce time; increase if the output flickers
boolean isPlaying = false;            // tracks if a song is playing or not

// BUTTON STRUCT //////////////////////////
// read up on structs and how they work. I have an idea, but its vauge as shit right now 
// just remember carlucci told me this when i was workign on the ISS Love. 

struct Button {
  const int btnPin;         // the button Pin
  const int btnLed;         // the button LED
  int songNumber;           // the song number
  int buttonState;          // always 0
  int lastButtonState;      // always 0
};

// array of structs that are buttons, sets the inital value sent to the struct. 
// {pin,LED,songNmber}

struct Button buttons[] = {{2,13,1},{3,12,2},{4,11,3}};

void buttonBehaviour(struct Button * button){

  // look up somethings about pointers in arduino
  
  int buttonReading = digitalRead(button->btnPin);
  
  if (buttonReading != button->lastButtonState) {
    lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    button->buttonState = buttonReading;
    if (button->buttonState == LOW && !isPlaying){
      isPlaying = true;
      digitalWrite(button->btnLed, HIGH);
      playSongs(button->songNumber);
    } else {
      digitalWrite(button->btnLed, LOW);
    }
  }
  button->lastButtonState = buttonReading;
}


void setup(){

  Serial.begin(9600);

  // LED PINS ////////////////////////////

  pinMode(buttons[0].btnLed, OUTPUT);
  pinMode(buttons[1].btnLed, OUTPUT);
  pinMode(buttons[2].btnLed, OUTPUT);

  // INPUT PINS //////////////////////////

  pinMode(buttons[0].btnPin, INPUT_PULLUP);
  pinMode(buttons[1].btnPin, INPUT_PULLUP);
  pinMode(buttons[2].btnPin, INPUT_PULLUP);

}

void loop(){

  buttonBehaviour(&buttons[0]); // 2
  buttonBehaviour(&buttons[1]); // 3
  buttonBehaviour(&buttons[2]); // 4
}

void playSongs(int s){
  int songID = s;
  //Serial.println("songID");
  //Serial.println(songID);
  if(songID == 1){
    Serial.println("NO");
    delay(2000);
  } else if(songID == 2){
    Serial.println("YES");
    delay(2000);
  } else if(songID == 3){
    Serial.println("SURPRISE");
    delay(2000);
  }
  isPlaying = false;
  
}


