

#include <DFRobot_ID809.h>
#include "Wire.h"
#include "LiquidCrystal_I2C.h"



LiquidCrystal_I2C LCD(0x27,16,2);



    #include <SoftwareSerial.h>
    SoftwareSerial FPSerial(2, 3);  //RX, TX

  char nom_chauffeur;

DFRobot_ID809 fingerprint;

void setup(){
  LCD.init(); // initialisation de l'afficheur
  LCD.backlight();

  LCD.setCursor(1, 0);
   LCD.print("Veuillez");
  
   LCD.setCursor(1, 1);
   LCD.print("vous identifier");
   
  Serial.begin(9600);

  FPSerial.begin(115200);
  fingerprint.begin(FPSerial);

  while(!Serial);

  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");

    delay(1000);
  }
  identifyFP();
}

void identifyFP(){
  uint8_t ret = 0;
  
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  Serial.println("Please press down your finger");

  if((fingerprint.collectionFingerprint(/*timeout=*/0)) != ERR_ID809){
    
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
    Serial.println("Capturing succeeds");
      Serial.println("Please release your finger");

    ret = fingerprint.search();
    
    if(ret != 0){
      /*Set fingerprint LED ring to always ON in green */
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
      Serial.print("Matching succeeds,ID=");
      Serial.println(ret);
      if(ret = 4){
        nom_chauffeur = "Oussama";
        LCD.clear();
        LCD.setCursor(1, 0);
        LCD.print("Bienvenue");
        
        LCD.setCursor(1, 1);
        LCD.print("Oussama");
        delay(3000);
       
      }
    else{
      /*Set fingerprint LED ring to always ON in red*/
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
      Serial.println("Matching fails");
              LCD.clear();
        LCD.setCursor(1, 0);
         LCD.print("ACCES");
        
         LCD.setCursor(1, 1);
         LCD.print("REFUSE");
         delay(5000);
         LCD.clear();
         identifyFP();
    }
  }

    else(identifyFP());

  Serial.println("-----------------------------");
  delay(1000);
}
}


void loop(){
  
}
