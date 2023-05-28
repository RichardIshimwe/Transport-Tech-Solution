// #include <LiquidCrystal.h> 
// #include <Wire.h>                    // Include the Wire library for I2C communication
// #include <Adafruit_PN532.h>          // Include the Adafruit_PN532 library
// #define SDA_PIN 20                   // Define the SDA pin
// #define SCL_PIN 21  
// #include <Keypad.h>  
// const byte ROWS = 4; //four rows
// const byte COLS = 4; //four columns
// String keypad_input;

// char keys[ROWS][COLS] = {
//   {'1','2','3','A'},
//   {'4','5','6','B'},
//   {'7','8','9','C'},
//   {'*','0','#','D'}
// };

// byte rowPins[ROWS] = {39, 41, 43, 45}; //connect to the row pinouts of the keypad
// byte colPins[COLS] = {47, 49, 51, 53}; //connect to the column pinouts of the keypad

// Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );               // Define the SCL pin

// LiquidCrystal lcd(22, 24, 26, 28, 30, 32);  
// String cardId = "";

// Adafruit_PN532 nfc(SDA_PIN, SCL_PIN); // Create an instance of the PN532 module
int Contrast=40;

// void setup(void) {
//   analogWrite(6,Contrast);
//   lcd.begin(20, 4);

//   nfc.begin();                        // Initialize the PN532 module
//   uint32_t versiondata = nfc.getFirmwareVersion(); // Get the firmware version of the module

//   if (!versiondata) {
//     while (1);                        // Halt the program if the module is not found
//   }

//   nfc.SAMConfig(); 
// }

// void loop() {
//    char key = keypad.getKey();

//   if (key) {
//     lcd.setCursor(0, 1);
//     lcd.print("All inputs: ");
//     lcd.print(key);

//     // Handle keypad input here

//     delay(500);
//   }

//   uint8_t success;
//   uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
//   uint8_t uidLength;

//   success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

//   if (success) {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print("Card found: ");

//     String uidString = "";

//     for (uint8_t i = 0; i < uidLength; i++) {
//       if (uid[i] < 0x10) {
//         uidString += "0";
//       }
//       uidString += String(uid[i], HEX);
//     }

//     lcd.print(uidString);

//     delay(1000);
//   }
// }


#include <Wire.h>
#include <Adafruit_PN532.h>
#include <LiquidCrystal.h> 
#include <Keypad.h>

#define SDA_PIN 20
#define SCL_PIN 21

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);  

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {39, 41, 43, 45};
byte colPins[COLS] = {47, 49, 51, 53};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
enum State {
  STATE_IDLE,
  STATE_WAITING_FOR_KEY,
  STATE_WAITING_FOR_CARD
};

State currentState = STATE_WAITING_FOR_KEY;  // Start in the waiting state for keypad input
String keypadInput = "";
String cardId = "";

void setup() {
  lcd.begin(20, 4);
  analogWrite(6, Contrast);
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();

  if (!versiondata) {
    while (1);
  }

  nfc.SAMConfig();
}

// void loop() {
//     char key = keypad.getKey();
//     lcd.setCursor(0, 0);
//     lcd.print("All inputs: ");
//   if (key) {
//     // Handle keypad input here
//     keypadInput += key;
//       lcd.setCursor(0, 1);
//       lcd.print("Keypad input: ");
//       lcd.print(keypadInput);
//     }
//   }


void loop() {
    uint8_t success;
    uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
    uint8_t uidLength;

    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

    if (success) {
      lcd.setCursor(0, 2);
      lcd.print("Card found: ");

      String uidString = "";

      for (uint8_t i = 0; i < uidLength; i++) {
        if (uid[i] < 0x10) {
          uidString += "0";
        }
        uidString += String(uid[i], HEX);
      }

      lcd.print(uidString);

      // Transition to the next state
    }
}
