//LED variables
int yellow = 3;
int green = 4;
int blue = 5;
int red = 6;

//Button variables
int yellowBttn = 8;
int greenBttn = 9;
int blueBttn = 10;
int redBttn = 11;
int pb_Bttn = 2; 
int reset_Bttn = 7;

//Piezo buzzer variable
int piezo = 13;

//Array variables
int index = 0;
int saveArray[50];

//Debounce variables
boolean lastButton = LOW; //previous reading from playback pin
boolean currentButton = LOW;  //current state of playback
boolean currentResetButton = LOW;
boolean lastResetButton = LOW;

/*********************************************************************************************************************************************/
void setup() {
  //LEDs
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);

  //buttons
  pinMode(yellowBttn, INPUT);
  pinMode(greenBttn, INPUT);
  pinMode(blueBttn, INPUT);
  pinMode(redBttn, INPUT);
  pinMode(pb_Bttn, INPUT);
  pinMode(reset_Bttn, INPUT);

  //piezo buzzer
  pinMode(piezo, OUTPUT);

  //turn LEDs off
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(red, LOW);
}
/*********************************************************************************************************************************************/
/*
 * Debounce button compares previous and current state of the playback button to determine when to execute playback
 * This method ensures that playback does not get pressed more than once, which could potentially cause an error
 */

boolean debounce(boolean last){
   boolean current = digitalRead(pb_Bttn);
   if(last != current)
   {
    delay(5); //CRUCIAL: without pause button will reset too quickly to read
    current = digitalRead(pb_Bttn);
   }
   return current;  //returns debounce value
}
/*********************************************************************************************************************************************/
void turnOffLEDs(){
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(yellow, LOW);
}
/*********************************************************************************************************************************************/
void playBack(){
  for(int i = 0; i<index; i++)
  {
    if(saveArray[i] == red)
    {
      digitalWrite(red, HIGH);
      tone(piezo, 1000, 500);
      delay(500);
      turnOffLEDs();
    }
    else if(saveArray[i] == green)
    {
      digitalWrite(green, HIGH);
      tone(piezo, 1200, 500);
      delay(500);
      turnOffLEDs();
    }
    else if(saveArray[i] == blue)
    {
      digitalWrite(blue, HIGH);
      tone(piezo, 1400, 500);
      delay(500);
      turnOffLEDs();
    }
    else if(saveArray[i] == yellow)
    {
      digitalWrite(yellow, HIGH);
      tone(piezo, 1600, 500);
      delay(500);
      turnOffLEDs();
    }
  }
}
/*********************************************************************************************************************************************/
void loop() {
  int yellow_State = digitalRead(yellowBttn);
  int green_State = digitalRead(greenBttn);
  int blue_State = digitalRead(blueBttn);
  int red_State = digitalRead(redBttn);
  currentButton = debounce(lastButton); //activate debounce function
  int reset_State = digitalRead(reset_Bttn);
  
  
  if(red_State == HIGH)
  {
    digitalWrite(red, HIGH);          //turn LED on
    tone(piezo, 1000, 500);           //play tone
    saveArray[index] = red;           //save pin into array for playback
    index++;                          //increment size of array
    delay(500);                       //delay button to avoid repeat
    digitalWrite(red, LOW);           //turn off LED
  }
  if(green_State == HIGH)
  {
    digitalWrite(green, HIGH);
    tone(piezo, 1200, 500);
    saveArray[index] = green;
    index++;
    delay(500);
    digitalWrite(green, LOW);
  }
  if(blue_State == HIGH)
  {
    digitalWrite(blue, HIGH);
    tone(piezo, 1400, 500);
    saveArray[index] = blue;
    index++;
    delay(500);
    digitalWrite(blue, LOW);
  }
  if(yellow_State == HIGH)
  {
    digitalWrite(yellow, HIGH);
    tone(piezo, 1600, 500);
    saveArray[index] = yellow;
    index++;
    delay(500);
    digitalWrite(yellow, LOW);
  }
  if(lastButton == LOW && currentButton == HIGH)
  {  //button has been pressed
    playBack();
  }
  lastButton = currentButton;
  if(reset_State == HIGH)
  {
    index = 0;
  }
}
