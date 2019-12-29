#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

int Chips=5;
int Chocolate=3;
int Potato=8;

int total=0;
int *pntr=&total;

int Max_Nmbr_Items;



MFRC522 mfrc522(SS_PIN, RST_PIN);   

 
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();    
  mfrc522.PCD_Init();   
  Serial.println("Please Scan Your Items: ");
  Serial.println();

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


  for(Max_Nmbr_Items=0;Max_Nmbr_Items<1000;Max_Nmbr_Items++){

  while(content.substring(1) == "E9 F2 E3 B8"){
    *pntr=*pntr+Chips;
    Serial.print("You added Lays Barbq Chips($5) to your tab.| Current Total Balance: $");
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
  Serial.println(total);
    delay(3000);
    for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], DEC));
  }
  }
   
 }

 Serial.print("TOTAL BALANCE: $");
 Serial.println(total);
 
 

 
} 
