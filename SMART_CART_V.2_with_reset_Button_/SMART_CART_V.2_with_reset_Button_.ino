/*

ARDUINO PIN ASSIGNMENTS


===============================================================================================
For LCD:                                                                                      +
                                                                                              +
VSS>>GND || VDD>>5V || V0>>~6 || RS>>7 ||RW>>GND || E>>8 || D4>>5 || D5>>4 || D6>>3 ||D7>>2 ||+  2
===============================================================================================

==========================================================================================================
For RFID-RC522 Scanner:                                                                                  +
                                                                                                         +
SDA>> 10 || SCK>> 13 || MOSI>> 11 || MISO>> 12 || IRQ>> BLANK || GND>> GND || RST>> 9 || 3.3v >> 3.3v || +
==========================================================================================================


======================================================================================================
For Reset Button>> A0                                                                                +
======================================================================================================
*/


#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

int Contrast=100;
const int rs=7, en=8, d4=5 , d5=4, d6=3 ,d7=2;
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);

#define SS_PIN 10
#define RST_PIN 9

int Chips=5;
int Chocolate=3;
int Potato=8;
int Chicken=6;

const int RSTRTBUTTON = A0;
int RSTRTBUTTONSTATE = 0;  

int total=0;
int *pntr=&total;

int Max_Nmbr_Items;



MFRC522 mfrc522(SS_PIN, RST_PIN);   

 
void setup() 
{
  analogWrite(6,Contrast);
  lcd.begin(16,2);

  pinMode(RSTRTBUTTON, INPUT);
  
  Serial.begin(9600);   
  SPI.begin();    
  mfrc522.PCD_Init();   
  Serial.println("Please Scan Your Items: ");
  Serial.println();
  lcd.print("PLEASE SCAN ITEMS");
  delay(4000);
  lcd.clear();

}
void loop() 
{
  RSTRTBUTTONSTATE = digitalRead(RSTRTBUTTON);
  
  if(RSTRTBUTTONSTATE==HIGH){
  total=0;
  lcd.noDisplay();
  delay(2000);
  lcd.clear();
  lcd.display();
  lcd.print("Resetting........");
  delay(3000);
  lcd.clear();
  lcd.display();
  lcd.print("Please Scan Items: ");
  lcd.setCursor(0,1);
  lcd.print("Total= $0");
  delay(6000);
  lcd.clear();
  }
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();


  for(Max_Nmbr_Items=0;Max_Nmbr_Items<1000;Max_Nmbr_Items++){

  while(content.substring(1) == "E9 F2 E3 B8"){
    *pntr=*pntr+Chips;
    Serial.print("You added Lays Barbq Chips($5) to your tab.| Current Total Balance: $");
    lcd.setCursor(0,0);
    lcd.print("LAYS CHIPS ($5)");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("TOTAL: $");
    lcd.setCursor(8,1);
    lcd.print(total);
    Serial.println(*pntr);
    delay(3000);
           for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], DEC));
  }
  }

  while(content.substring(1)== "B2 34 32 2D"){
    *pntr=*pntr+Chocolate;
    Serial.print("You added CHOCOLATE ($3) to your tab.| Current Total Balance: $");
    lcd.setCursor(0,0);
    lcd.print("CHOCOLATE ($3)");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("TOTAL: $");
    lcd.setCursor(8,1);
    lcd.print(total);
    Serial.println(*pntr);
    delay(3000);
        for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], DEC));
  }
  }


  while(content.substring(1)== "09 32 E3 C2"){
  total=total+Potato;
  Serial.print("You added POTATO($8) to your tab.| Current Total Balance: $");
  lcd.setCursor(0,0);
    lcd.print("POTATO ($8)");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("TOTAL: $");
    lcd.setCursor(8,1);
    lcd.print(total);
  Serial.println(total);
    delay(3000);
    for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], DEC));
  }
  }

  while(content.substring(1)=="B9 C5 A1 D5"){
    total=total+Chicken;
    Serial.print("You added CHICKEN($6) to your tab.| Current Total Balance: $");
    lcd.setCursor(0,0);
    lcd.print("CHICKEN ($6)");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("TOTAL: $");
    lcd.setCursor(8,1);
    lcd.print(total);
    Serial.println(total);
    delay(3000);
    for (byte i=0; i<mfrc522.uid.size;i++){
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i],DEC));
    }
    
  }
   
 }

 Serial.print("TOTAL BALANCE: $");
 Serial.println(total);

  }





 
 
 

 
