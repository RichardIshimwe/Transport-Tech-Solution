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
SoftwareSerial gpsSerial(10, 11);  // RX, TX

// Create a TinyGPS++ object to handle the GPS data
TinyGPSPlus gps;
String keypadInput;
int select = 0;
bool page1 = true;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 39, 41, 43, 45 };
byte colPins[COLS] = { 47, 49, 51, 53 };
int Contrast = 100;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//----------------------------------------------------------------normal setup----------------------------------------

//  void setup()
//  {
//     analogWrite(6,Contrast);
//      lcd.begin(20, 4);
//   }
//----------------------------------------------------------------setup for gps----------------------------------------------------------------------------
// void setup() {
//   // Start the serial communication
//   Serial.begin(9600);
//   gpsSerial.begin(9600);
//   lcd.begin(20, 4);
//   analogWrite(6, Contrast);

//   // Wait for GPS module to initialize
//   delay(1000);

//   // Check if GPS module is connected
//   if (!gpsSerial) {
//     lcd.println("GPS module not connected. Please check the wiring.");
//   }
// }

//----------------------------------------------------------------setup for nfc and gps--------------------------------------------------------------------
void setup() {
  lcd.begin(20, 4);
  analogWrite(6, Contrast);
  gpsSerial.begin(9600);
  Serial.begin(9600);
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  myLogo();
  delay(3000);
  if (!versiondata) {
    while (1)
      ;
  }
  if (!gpsSerial) {
    lcd.print("GPS module not connected. Please check the wiring.");
  }

  nfc.SAMConfig();
  lcd.clear();
}
//----------------------------------------------------------------main loop--------------------------------------------------------------------------------
void loop() {
  //  keypadChange();
  // currentPostion();
  // lcdDisplay();
  // makeChoice();
  keypadChange();
}
//----------------------------------------------------------------screens---------------------------------------------------------------------------------
//  +++++++++++++++logo+++++++++++++++++
void myLogo() {
  lcd.setCursor(0, 0);
  lcd.print("---------------------");
  lcd.setCursor(0, 1);
  lcd.print("---Transport Tech---");
  lcd.setCursor(0, 2);
  lcd.print("------Solution------");
  lcd.setCursor(0, 3);
  lcd.print("--------------------");
}
//  +++++++++++++++choice+++++++++++++++++
void makeChoice() {
  lcd.setCursor(0, 0);
  lcd.print("    Select Role:   ");
  lcd.setCursor(0, 1);
  lcd.print("1.Admin");
  lcd.setCursor(0, 2);
  lcd.print("2.Driver");
  lcd.setCursor(0, 3);
  lcd.print("3.Settings");
}
//  +++++++++++++++change selected+++++++++++++++++
int selectedItem(int selected) {
  lcd.setCursor(0, 0);
  lcd.print("    Select Role:   ");
  if (select == 1) {
    lcd.setCursor(0, 1);
    lcd.print("--Admin");
    lcd.setCursor(0, 2);
    lcd.print("2.Driver");
    lcd.setCursor(0, 3);
    lcd.print("3.Settings");
  } else if (select == 2) {
    lcd.setCursor(0, 1);
    lcd.print("1.Admin");
    lcd.setCursor(0, 2);
    lcd.print("--Driver");
    lcd.setCursor(0, 3);
    lcd.print("3.Settings");
  } else if (select == 3) {
    lcd.setCursor(0, 1);
    lcd.print("1.Admin");
    lcd.setCursor(0, 2);
    lcd.print("2.Driver");
    lcd.setCursor(0, 3);
    lcd.print("--Settings");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("    Select Role:   ");
    lcd.setCursor(0, 1);
    lcd.print("1.Admin");
    lcd.setCursor(0, 2);
    lcd.print("2.Driver");
    lcd.setCursor(0, 3);
    lcd.print("3.Settings");
  }
}
//  +++++++++++++++choice+++++++++++++++++
void driverPage() {
  lcd.clear();
    lcd.setCursor(0, 0);
  lcd.print("tap card to proceed");
  readCard();
}
void adminPage() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("welcome to admin");
}
void settingPage() {
  lcd.clear();
  lcd.setCursor(0, 1);
  // lcd.print("welcome to setting");
  currentPostion();
}
// -------------------------------------------------------------------------lcd display-------------------------------------------------------------------

void lcdDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Only Innovative");
  lcd.setCursor(0, 1);
  lcd.print("Subscribe");
  lcd.setCursor(0, 2);
  lcd.print("Subscribe");
  lcd.setCursor(0, 3);
  lcd.print("Subscribe");
}
// ----------------------------------------------------------------------------keypad---------------------------------------------------------------------

// void loop() {
//     char key = keypad.getKey();
//     lcd.setCursor(0, 0);
//     lcd.print("All inputs: ");
//   if (key) {
//     // Handle keypad input here
//     keypadInput += key;
//       lcd.setCursor(0, 1);
//       lcd.print("Keypad input: ");
//       // lcd.print(key);
//       lcd.print(keypadInput);
//     }
//   }
// ++++++++++++++++++++++++++++++++keypad function++++++++++++++++++++++++++++++++
void keypadChange() {
  char key = keypad.getKey();

  if (page1 == true) {
    selectedItem(select);
  }
  if (key == 'C') {
    page1 = false;
    if (select == 1) {
      adminPage();
      select == 12;
    } else if (select == 2) {
      driverPage();
    } else if (select == 3) {
      settingPage();
    }
  };
  if(key == 'D'){
    lcd.clear();
    page1 = true;
  }
  if (key) {
    if (select < 0) select = 1;
    if (select > 3) select = 1;
    keypadInput += key;
    if (key == 'A') select--;
    if (key == 'B') select++;
    delay(50);
  }
}

// -------------------------------------------------------------------------nfc card reader------------------------------------------------------------------
void readCard() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    lcd.setCursor(0, 1);
    lcd.print("Card found: ");

    String uidString = "";

    for (uint8_t i = 0; i < uidLength; i++) {
      if (uid[i] < 0x10) {
        uidString += "0";
      }
      uidString += String(uid[i], HEX);
    }
lcd.setCursor(0, 2);
lcd.print(uidString);
  }
  delay(500);
}
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
// -----------------------------gps function and ---------------------------
void currentPostion() {
  // keypadChange();
  // readCard();

  static unsigned long previousMillis = 0;
  const unsigned long interval = 1000;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {

    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        // If valid data is received, print the GPS information
        previousMillis = currentMillis;
        if (gps.location.isValid()) {
          lcd.setCursor(0, 0);
          lcd.print("Latitude: ");
          lcd.print(gps.location.lat(), 6);
          lcd.setCursor(0, 1);
          lcd.print("Longitude: ");
          lcd.print(gps.location.lng(), 6);
          lcd.setCursor(0, 2);
          lcd.print("Altitude: ");
          lcd.print(gps.altitude.meters());
        }
      }
    }
    // keypadChange();
  }
}
