#include <LiquidCrystal.h> 
int Contrast=140;
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
String keypad_input;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {39, 41, 43, 45}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {47, 49, 51, 53}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
   Serial.begin(9600);
   analogWrite(6,Contrast);
   lcd.begin(16, 2);
}
  
void loop(){
  char key = keypad.getKey();
    lcd.setCursor(0,0);
    lcd.print("all inputs from the keypad");
  if (key){
    keypad_input += key;
    lcd.setCursor(0,1);
    lcd.print(keypad_input);
  }
}
