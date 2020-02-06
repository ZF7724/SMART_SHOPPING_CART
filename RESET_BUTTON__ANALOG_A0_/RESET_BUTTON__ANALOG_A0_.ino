#include <LiquidCrystal.h>

const int buttonPin = A0;

int Contrast=100;
const int rs=7 , en=8, d4=5 , d5=4, d6=3 ,d7=2;
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);

int buttonState = 0;  

void setup() {
  // put your setup code here, to run once:
  analogWrite(6,Contrast);
  lcd.begin(16,2);
  pinMode(buttonPin, INPUT);

  lcd.print("Please Scan Items:");
  delay(5000);
  lcd.clear();

}

void loop() {
  
  buttonState = digitalRead(buttonPin);
  if(buttonState==HIGH){
  lcd.noDisplay();
  delay(2000);
  lcd.display();
  lcd.print("Resetting........");
  delay(3000);
  lcd.clear();
  lcd.display();
  lcd.print("Please Scan Items: ");
  delay(6000);
  lcd.clear();
  }

  

}
