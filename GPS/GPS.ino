#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpsSerial(10, 11); // RX, TX

// Create a TinyGPS++ object to handle the GPS data
TinyGPSPlus gps;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  gpsSerial.begin(9600);

  // Wait for GPS module to initialize
  delay(1000);

  // Check if GPS module is connected
  if (!gpsSerial) {
    Serial.println("GPS module not connected. Please check the wiring.");
  }
}

void loop() {
  // Read data from the GPS module
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // If valid data is received, print the GPS information
      if (gps.location.isValid()) {
        Serial.print("Latitude: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: ");
        Serial.println(gps.location.lng(), 6);
        Serial.print("Altitude: ");
        Serial.println(gps.altitude.meters());
      }
    }
  }
}
