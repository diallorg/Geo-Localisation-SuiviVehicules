#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>  
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN D3
#define RST_PIN D5
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

byte nuidPICC[4];

//WiFi Connection configuration
char ssid[] = "iPhone Ouss";     //  le nom du reseau WIFI
char password[] = "azertyuiop";  // le mot de passe WIFI
//mqtt server
char mqtt_server[] = "broker.emqx.io";  //adresse IP serveur 
#define MQTT_USER "attiaoussama06@gmail.com"
#define MQTT_PASS "Depay06*"

WiFiClient espClient;
PubSubClient MQTTclient(espClient);

char response[50];

char Slat[10];
char Slon[10];

//Fonctions mqtt
void MQTTsend() {

 String driver="Oussama";
 long lat=random(43100000,43500000)/1000000;
 long lon=random(7500000,7800000)/1000000;
 
 dtostrf(lat, 7, 5, Slat);
 dtostrf(lon, 8, 5, Slon);
 
 sprintf(response, "%s/%s/%s",driver, Slat, Slon);
 Serial.println(response);

 MQTTclient.publish("attiaoussama06@gmail.com/Location/AB123CD",response);
}

void MQTTconnect() {

  while (!MQTTclient.connected()) {
      Serial.print("Attente  MQTT connection...");
      String clientId = "AB123CD-";
      clientId += String(random(0xffff), HEX);

    // test connexion
    if (MQTTclient.connect(clientId.c_str(),"","")) {
      Serial.println("connected");

    } else {  // si echec affichage erreur
      Serial.print("ECHEC, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" nouvelle tentative dans 5 secondes");
      delay(5000);
    }
  }
}

void setup() {
Serial.begin(115200);

 SPI.begin(); // Init SPI bus
 rfid.PCD_Init(); // Init MFRC522
  // Conexion WIFI
   WiFi.begin(ssid, password);
   Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   Serial.println("Connected");
   MQTTclient.setServer(mqtt_server, 1883);
  
}

void loop() {
  static uint32_t  lastTimeMqtt= 0;
  // connect serveur MQTT
  if (!MQTTclient.connected()) {
    MQTTconnect();
  }

  if (millis() - lastTimeMqtt >= 10000)  // toutes les 20 secondes
   {
     lastTimeMqtt = millis();
     MQTTsend();
   }
}
