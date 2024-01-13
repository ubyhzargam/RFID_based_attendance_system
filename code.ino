#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include "RTClib.h"
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //define green LED pin
#define LED_R 4 //define red LED
#define BUZZER 2 //buzzer pin
RTC_DS1307 rtc;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name
 
void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Place card/tag near reader...");
  Serial.println();
  rtc.begin();
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    Serial.println("Place card/tag near reader...");
  }

}
void loop()
{
   
  DateTime time = rtc.now();
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
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "DA 49 24 B0") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println("USN: 1RV21EC099");
    Serial.println("Welcome Mohammed Asim......");
     Serial.println(String("DateTime::TIMESTAMP_DATE:\t")+time.timestamp(DateTime::TIMESTAMP_DATE));

    //Full Timestamp
    Serial.println(String("DateTime::TIMESTAMP_TIME:\t")+time.timestamp(DateTime::TIMESTAMP_TIME));
    
    delay(3000);
   
    Serial.println();
    delay(500);
    digitalWrite(LED_G, HIGH);
     myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
    Serial.println();
    Serial.println();
    Serial.println("Place card/tag near reader...");
  }
  else if (content.substring(1) == "03 AD A1 A9") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println("USN : 1RV21EC167");
    Serial.println("Welcome Sourish G......");
    Serial.println();
    //Serial.println(String("DateTime::TIMESTAMP_FULL:\t")+time.timestamp(DateTime::TIMESTAMP_FULL));

     //Date Only
    Serial.println(String("DateTime::TIMESTAMP_DATE:\t")+time.timestamp(DateTime::TIMESTAMP_DATE));

    //Full Timestamp
    Serial.println(String("DateTime::TIMESTAMP_TIME:\t")+time.timestamp(DateTime::TIMESTAMP_TIME));
    delay(3000);
    
    delay(500);
    digitalWrite(LED_G, HIGH);
     myServo.write(180);
    delay(5000);
    myServo.write(0);
    digitalWrite(LED_G, LOW);
     Serial.println();
    Serial.println();
    Serial.println("Place card/tag near reader...");
  }
 
 else   {
 
    Serial.println(" Access denied");
  Serial.println(String("DateTime::TIMESTAMP_DATE:\t")+time.timestamp(DateTime::TIMESTAMP_DATE));

    //Full Timestamp
    Serial.println(String("DateTime::TIMESTAMP_TIME:\t")+time.timestamp(DateTime::TIMESTAMP_TIME));
    delay(500);
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 900);
    delay(4000);
   digitalWrite(LED_R, LOW);
   noTone(BUZZER);
    Serial.println();
    Serial.println();
    Serial.println("Place card/tag near reader...");
  }
}
