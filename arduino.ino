#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Time.h>

//LCD
#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

//Rotary Encoder
#define clkPin 2
#define dtPin 3
#define swPin 4

int n = 1;
int encoderVal = 0;

String incomingMessage;

LiquidCrystal_I2C	lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home
  
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);
  
  //setTime(12, 12, 32, 13, 2, 2016);
  //lcd.print(String(hour()) + ":" + String(minute()) + ":" + String(second())); 
}

void loop() {
  
    int change = getEncoderTurn();
  encoderVal = encoderVal + change;
  if(digitalRead(swPin) == LOW)
  {
    encoderVal = 0;
  }
  Serial.println(encoderVal % 20);
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingMessage = Serial.readString();
    
    String command = incomingMessage.substring(0, 3);
    String declaration = incomingMessage.substring(4);
    
    if(command == "TME") {
     processTime(declaration);
    }
    
    else if(command == "RDO") {
     processRadio(declaration);
    }
  }
}


//Work out encoder position
int getEncoderTurn(void)
{
  static int oldA = HIGH;
  static int oldB = HIGH;
  int result = 0;
  int newA = digitalRead(clkPin);
  int newB = digitalRead(dtPin);
  if (newA != oldA || newB != oldB)
  {
    // something has changed
    if (oldA == HIGH && newA == LOW)
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}

void processRadio(String declaration) {
  lcd.clear();
  lcd.print(declaration); 
}

void processTime(String time) {
  
}
