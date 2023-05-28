#include <Wire.h>
#include <Adafruit_PN532.h>
#include <LiquidCrystal.h> 
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#define SDA_PIN 20
#define SCL_PIN 21

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);
LiquidCrystal lcd(22, 24, 26, 28, 30, 32);  
SoftwareSerial gpsSerial(10, 11); // RX, TX

// Create a TinyGPS++ object to handle the GPS data
TinyGPSPlus gps;
String keypadInput;

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
int Contrast=20;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//----------------------------------------------------------------normal setup----------------------------------------

//  void setup()
//  {
//     analogWrite(6,Contrast);
//      lcd.begin(20, 4);
//   } 
//----------------------------------------------------------------setup for gps----------------------------------------------------------------------------
void setup() {
  // Start the serial communication
  Serial.begin(9600);
  gpsSerial.begin(9600);
  lcd.begin(20, 4);
  analogWrite(6, Contrast);

  // Wait for GPS module to initialize
  delay(1000);

  // Check if GPS module is connected
  if (!gpsSerial) {
    Serial.println("GPS module not connected. Please check the wiring.");
  }
}
//----------------------------------------------------------------setup for nfc and gps--------------------------------------------------------------------
// void setup() {
//   lcd.begin(20, 4);
//   analogWrite(6, Contrast);
//   gpsSerial.begin(9600);
//   nfc.begin();
//   uint32_t versiondata = nfc.getFirmwareVersion();
//   delay(1000);
//   if (!versiondata) {
//     while (1);
//   }
//     if (!gpsSerial) {
//     lcd.print("GPS module not connected. Please check the wiring.");
//   }

//   nfc.SAMConfig();
// }
// -------------------------------------------------------------------------lcd display-------------------------------------------------------------------

//     void loop()
//  { 
//      lcd.setCursor(0, 0);
//      lcd.print("Only Innovative");
//     lcd.setCursor(0, 1);
//      lcd.print("Subscribe");
//        lcd.setCursor(0, 2);
//      lcd.print("Subscribe");
//        lcd.setCursor(0, 3);
//      lcd.print("Subscribe");
//  }
// ----------------------------------------------------------------------------keypad---------------------------------------------------------------------

void loop() {
    char key = keypad.getKey();
    lcd.setCursor(0, 0);
    lcd.print("All inputs: ");
  if (key) {
    // Handle keypad input here
    keypadInput += key;
      lcd.setCursor(0, 1);
      lcd.print("Keypad input: ");
      // lcd.print(key);
      lcd.print(keypadInput);
    }
  }

// -------------------------------------------------------------------------nfc card reader------------------------------------------------------------------
// void loop() {
//     uint8_t success;
//     uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
//     uint8_t uidLength;

//     success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

//     if (success) {
//       lcd.setCursor(0, 2);
//       lcd.print("Card found: ");

//       String uidString = "";

//       for (uint8_t i = 0; i < uidLength; i++) {
//         if (uid[i] < 0x10) {
//           uidString += "0";
//         }
//         uidString += String(uid[i], HEX);
//       }

//       lcd.print(uidString);
//     }
//     delay(500);
// }
// ---------------------------------------------------gps tracker---------------------------------------------------------------
// void loop(){
//     while (gpsSerial.available() > 0) {
//     if (gps.encode(gpsSerial.read())) {
//       // If valid data is received, print the GPS information
//       if (gps.location.isValid()) {
//         lcd.setCursor(0, 0);
//         lcd.print("Latitude: ");
//         lcd.print(gps.location.lat(), 6);
//         lcd.setCursor(0, 1);
//         lcd.print("Longitude: ");
//         lcd.print(gps.location.lng(), 6);
//         lcd.setCursor(0, 2);
//         lcd.print("Altitude: ");
//         lcd.print(gps.altitude.meters());
//       }
//     }
// }}
