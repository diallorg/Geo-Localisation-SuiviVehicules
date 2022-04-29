#include <DFRobot_ID809.h>

#define COLLECT_NUMBER 3
#define IRQ 6   

#include <SoftwareSerial.h>
SoftwareSerial Serial1(2, 3);  //RX, TX
#define FPSerial Serial1

DFRobot_ID809 fingerprint;
//String desc;

void setup(){
  Serial.begin(9600);
  FPSerial.begin(115200);
  fingerprint.begin(FPSerial);
  while(!Serial);

  while(fingerprint.isConnected() == false){
    Serial.println("Communication with device failed, please check connection");
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
    delay(1000);
  }
}

//Blue LED Comparison mode  Yellow LED Registration mode  Red Deletion mode 
void loop(){
  if(digitalRead(IRQ)){
    uint16_t i = 0;
    if((fingerprint.collectionFingerprint(/*timeout=*/5)) != ERR_ID809){
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */3);  //blue LED blinks quickly 3 times, means it's in fingerprint comparison mode now
      while(fingerprint.detectFinger()){
        delay(50);
        i++;
        if(i == 15){             //Yellow LED blinks quickly 3 times, means it's in fingerprint regisrtation mode now
          fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
        }else if(i == 30){      //Red LED blinks quickly 3 times, means it's in fingerprint deletion mode now 
          fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */3);
        }
      }
    }
    if(i == 0){
    }else if(i > 0 && i < 15){
      Serial.println("Enter fingerprint comparison mode");
      fingerprintMatching();
    }else if(i >= 15 && i < 30){
      Serial.println("Enter fingerprint registration mode");
      fingerprintRegistration();
    }else{
      Serial.println("Enter fingerprint deletion mode");
      fingerprintDeletion();
    }
  }
}

//Compare fingerprints
void fingerprintMatching(){
  uint8_t ret = fingerprint.search();
  if(ret != 0){
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
    Serial.print("Successfully matched,ID=");
    Serial.println(ret);
  }else{
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
    Serial.println("Matching failed");
  }
  delay(1000);
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eNormalClose, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  Serial.println("-----------------------------");
}

//Fingerprint Registration
void fingerprintRegistration(){
  uint8_t ID,i;
  fingerprint.search();       //Can add "if else" statement to judge whether the fingerprint has been registered. 
  if((ID = fingerprint.getEmptyID()) == ERR_ID809){
    while(1){
      //desc = fingerprint.getErrorDescription();
      //Serial.println(desc);
      delay(1000);
    }
  }
  Serial.print("Unregistered ID,ID=");
  Serial.println(ID);
  i = 0;   //Clear sampling times 
  while(i < COLLECT_NUMBER){
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eBreathing, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
    Serial.print("The fingerprint sampling of the");
    Serial.print(i+1);
    Serial.println("(th) time is being taken");
    Serial.println("Please press down your finger");
    if((fingerprint.collectionFingerprint(/*timeout = */10)) != ERR_ID809){
      fingerprint.ctrlLED(/*LEDMode = */fingerprint.eFastBlink, /*LEDColor = */fingerprint.eLEDYellow, /*blinkCount = */3);
      Serial.println("Capturing succeeds");
      i++;   //Sampling times +1 
    }else{
      Serial.println("Capturing fails");
      //desc = fingerprint.getErrorDescription();
      //Serial.println(desc);
    }
    Serial.println("Please release your finger");
    while(fingerprint.detectFinger());
  }
  
  if(fingerprint.storeFingerprint(/*Empty ID = */ID) != ERR_ID809){
    Serial.print("Saving succeed，ID=");
    Serial.println(ID);
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
    delay(1000);
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eNormalClose, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  }else{
    Serial.println("Saving failed");
    //desc = fingerprint.getErrorDescription();
    //Serial.println(desc);
  }
  Serial.println("-----------------------------");
}


//Fingerprint deletion
void fingerprintDeletion(){
  uint8_t ret;
  ret = fingerprint.search();
  if(ret){
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDGreen, /*blinkCount = */0);
    fingerprint.delFingerprint(ret);
    Serial.print("deleted fingerprint,ID=");
    Serial.println(ret);
  }else{
    fingerprint.ctrlLED(/*LEDMode = */fingerprint.eKeepsOn, /*LEDColor = */fingerprint.eLEDRed, /*blinkCount = */0);
    Serial.println("Matching failed or the fingerprint hasn't been registered");
  }
  delay(1000);
  fingerprint.ctrlLED(/*LEDMode = */fingerprint.eNormalClose, /*LEDColor = */fingerprint.eLEDBlue, /*blinkCount = */0);
  Serial.println("-----------------------------");
}
