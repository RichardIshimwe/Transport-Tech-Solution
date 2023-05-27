#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>                    // Include the Wire library for I2C communication
#include <Adafruit_PN532.h>          // Include the Adafruit_PN532 library
SoftwareSerial gpsSerial(11, 10); // RX, TX
TinyGPSPlus gps;

#include <LiquidCrystal.h> 
int Contrast=30;
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
String keypad_input;
LiquidCrystal lcd(22, 24, 26, 28, 30, 32); 

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
  //  Serial.begin(9600);
   gpsSerial.begin(9600);
   analogWrite(6,Contrast);
   lcd.begin(20, 4);
   delay(1000);

  if (!gpsSerial) {
    // Serial.println("GPS module not connected. Please check the wiring.");
  }
  // Serial.print("trying to connect.......................");
}
  
void loop(){
  char key = keypad.getKey();
    // lcd.setCursor(0,0);
    // lcd.print("all inputs");
  if (key){
    keypad_input += key;
    // lcd.setCursor(0,0);
    // lcd.print(keypad_input);
  }
    while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // If valid data is received, print the GPS information
      if (gps.location.isValid()) {
        // Serial.print("Latitude: ");    
        lcd.setCursor(0,1);
        lcd.print("Lat: ");
        lcd.print(gps.location.lat(), 6);
        // Serial.println(gps.location.lat(), 6);
        // Serial.print("Longitude: ");
        lcd.setCursor(0,2);
        lcd.print("Long: ");
        lcd.print(gps.location.lng(), 6);
        // Serial.println(gps.location.lng(), 6);
        // Serial.print("Altitude: ");
        // Serial.println(gps.altitude.meters());
        lcd.setCursor(0,3);
        lcd.print("Alt: ");
        lcd.print(gps.altitude.meters());
      }
    }
  }
}
// #define SDA_PIN 20                   // Define the SDA pin
// #define SCL_PIN 21                   // Define the SCL pin

// Adafruit_PN532 nfc(SDA_PIN, SCL_PIN); // Create an instance of the PN532 module

// void setup(void) {
//   Serial.begin(9600);                // Initialize the serial communication

//   Serial.println("Hello!");

//   nfc.begin();                        // Initialize the PN532 module
//   uint32_t versiondata = nfc.getFirmwareVersion(); // Get the firmware version of the module

//   if (!versiondata) {
//     Serial.print("Didn't find PN53x board");
//     while (1);                        // Halt the program if the module is not found
//   }

//   nfc.SAMConfig();                    // Configure the PN532 module as a target
//   Serial.println("Waiting for an NFC card ...");
// }

// void loop(void) {
//   uint8_t success;
//   uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
//   uint8_t uidLength;

//   success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength); // Read the UID of a detected card

//   if (success) {
//     Serial.println("Found an NFC card!");

//     Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
//     Serial.print("UID Value: ");
//     for (uint8_t i = 0; i < uidLength; i++) {
//       Serial.print(" 0x");Serial.print(uid[i], HEX);
//     }
//     Serial.println("");

//     delay(1000);                    // Delay for a short time
//   }
// }
//--------------------------------------------------gps-------------------------------------------------------------

// void setup() {
//   Serial.begin(9600);
//   gpsSerial.begin(9600);
//   delay(1000);

//   if (!gpsSerial) {
//     Serial.println("GPS module not connected. Please check the wiring.");
//   }
//   Serial.print("trying to connect.......................");
// }

// void loop() {
//   // Read data from the GPS module
//   while (gpsSerial.available() > 0) {
//     if (gps.encode(gpsSerial.read())) {
//       // If valid data is received, print the GPS information
//       if (gps.location.isValid()) {
//         Serial.print("Latitude: ");
//         Serial.println(gps.location.lat(), 6);
//         Serial.print("Longitude: ");
//         Serial.println(gps.location.lng(), 6);
//         Serial.print("Altitude: ");
//         Serial.println(gps.altitude.meters());
//       }
//     }
//   }
// }

//////////////////////////////////////////////////////nfc card reader///////////////////////////////////////////////////////////////

/*
#include <Wire.h>                    // Include the Wire library for I2C communication
#include <Adafruit_PN532.h>          // Include the Adafruit_PN532 library

#define SDA_PIN 20                   // Define the SDA pin
#define SCL_PIN 21                   // Define the SCL pin

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN); // Create an instance of the PN532 module

void setup(void) {
  Serial.begin(9600);                // Initialize the serial communication

  Serial.println("Hello!");

  nfc.begin();                        // Initialize the PN532 module
  uint32_t versiondata = nfc.getFirmwareVersion(); // Get the firmware version of the module

  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1);                        // Halt the program if the module is not found
  }

  nfc.SAMConfig();                    // Configure the PN532 module as a target
  Serial.println("Waiting for an NFC card ...");
}

void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength); // Read the UID of a detected card

  if (success) {
    Serial.println("Found an NFC card!");

    Serial.print("UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(" 0x");Serial.print(uid[i], HEX);
    }
    Serial.println("");

    delay(1000);                    // Delay for a short time
  }
}
*/



