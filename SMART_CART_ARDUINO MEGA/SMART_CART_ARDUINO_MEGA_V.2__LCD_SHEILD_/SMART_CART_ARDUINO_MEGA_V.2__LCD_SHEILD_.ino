
/*

ARDUINO PIN ASSIGNMENTS


===============================================================================================
For LCD: (Just put on LCD Sheild)                                                             +
                                                                                              +
VSS>>GND || VDD>>5V || RS>>8 ||RW>>GND || E>>9 || D4>>4 || D5>>5 || D6>>6 ||D7>>7             +  
===============================================================================================

==========================================================================================================
For RFID-RC522 Scanner:                                                                                  +
                                                                                                         +
SDA>> 53 || SCK>> 52 || MOSI>> 51 || MISO>> 50 || IRQ>> BLANK || GND>> GND || RST>> 2 || 3.3v >> 3.3v || +
==========================================================================================================


======================================================================================================
For Reset Button>> A0                                                                                +
======================================================================================================
*/


#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

const int rs=8, en=9, d4=4 , d5=5, d6=6 ,d7=7;
LiquidCrystal lcd (rs,en,d4,d5,d6,d7);

#define SS_PIN 53
#define RST_PIN 2

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
  lcd.begin(16,2);
  
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


  for(Max_Nmbr_Items=0;Max_Nmbr_Items<100;Max_Nmbr_Items++){

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
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("TOTAL: $");
    lcd.setCursor(8,1);
    lcd.print(total);
    Serial.println(*pntr);
    delay(1000);
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





 
 
 

 
