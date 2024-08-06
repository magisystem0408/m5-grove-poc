#include <M5Unified.h>
#include <TinyGPS++.h>

HardwareSerial GPSRaw(2);
TinyGPSPlus gps;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Lcd.setRotation(1);
  GPSRaw.begin(9600, SERIAL_8N1, 33, 32);
} 

void loop() {
  M5.Lcd.setTextFont(1);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("GPS sample");
  while(GPSRaw.available() > 0) { 
    if(gps.encode(GPSRaw.read())) {
      break;
    }
  }
  if(gps.location.isValid()) {
    M5.Lcd.printf("lat:%.4f\n", gps.location.lat() );
    M5.Lcd.printf("lng:%.4f\n", gps.location.lng() );
  } else {
    M5.Lcd.println("invalid location");
  }
  delay(3000);
}
