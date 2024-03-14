#include <LiquidCrystal_I2C.h>
#include "Wheels.h"


Wheels w;
volatile char cmd;

void setup() {
  // put your setup code here, to run once:
  w.attach(7,8,5,12,11,10);
  
  Serial.begin(9600);
  Serial.println("Forward: WAD");
  Serial.println("Back: ZXC");
  Serial.println("Stop: S");

}

void loop() {
  while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': w.forward(); break;
      case 'x': w.back(); break;
      case 'a': w.forwardLeft(); break;
      case 'd': w.forwardRight(); break;
      case 'z': w.backLeft(); break;
      case 'c': w.backRight(); break;
      case 's': w.stop(); break;
      case '1': w.setSpeedLeft(75); break;
      case '2': w.setSpeedLeft(200); break;
      case '9': w.setSpeedRight(75); break;
      case '0': w.setSpeedRight(200); break;
      case '5': w.setSpeed(100); break;
    }
  }
}
byte LCDAddress = 0x27;

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);
  
uint8_t arrowRight[8] =
{
    0b01000,
    0b01100,
    0b00110,
    0b11111,
    0b11111,
    0b00110,
    0b01100,
    0b01000
};

int argIn = 0;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(200);

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, arrowRight);
}

void loop() {

  uint8_t barPos = 0;
  
  argIn = Serial.parseInt(SKIP_ALL);
  if(argIn <= 0) return;

  lcd.clear();
  lcd.setCursor(barPos, 1);
  lcd.write(0);

  for(int val=0;val<=argIn; val++) {
    lcd.setCursor(0,0);
    lcd.print(val);
    barPos = map(val, 0, argIn, 0, 16);
    lcd.setCursor(barPos, 1);
    lcd.print('=');
    lcd.write(0);
    delay(20);
  }
}
