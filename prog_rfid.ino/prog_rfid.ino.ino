#include <SPI.h>
#include <MFRC522.h>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

 
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C LCD(0x27,16,2); // définit le type d'écran lcd 16 x 2

String names[]={"Oussama","axel"};
String tag[]={"A3 D0 38 1A","41 F3 24 83"};
 
void setup() 
{
  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("bienvenue, presentez votre badge...");
  Serial.println();
  LCD.setCursor(3, 0);
  LCD.print("PRESENTEZ");
  LCD.setCursor(1, 1);
  LCD.print(" VOTRE BADGE!");
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
 
   
  if ((content.substring(1) == tag[0]) || (content.substring(1) == tag[1]))  //change here the UID of the card/cards that you want to give access
  {
    LCD.clear();
    Serial.println("Accès autorisé");
    Serial.println();
    LCD.setCursor(3, 0);
    LCD.print("BIENVENUE");
    LCD.setCursor(5, 1);
    LCD.print(names[0]);
    delay(2000);
    LCD.clear();
    LCD.setCursor(5,0);
    LCD.print(names[0]);
    delay(1000);
    
  }
 else   {
    LCD.clear();
    Serial.println(" Accès refusé");
    Serial.println();
    LCD.setCursor(2, 0);
    LCD.print("ACCES REFUSE");
    delay(5000);
    LCD.clear();  
    setup();
  }

  
  //Va permettre de scanner le badge une seule fois
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
} 
