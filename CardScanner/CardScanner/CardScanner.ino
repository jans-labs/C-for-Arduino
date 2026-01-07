// RFID CARD SCANNER
// * Typical pin layout used:
// * -----------------------------------------------------------------------------------------
// *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
// *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
// * Signal      Pin          Pin           Pin       Pin        Pin              Pin
// * -----------------------------------------------------------------------------------------
// * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
// * SPI SS      SDA(SS)      10            53        D10        10               10
// * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
// * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
// * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_G 5 //define green LED pin
#define LED_R 4 //define red LED
#define BUZZER 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2); // Create LCD instance.
Servo myServo; //define servo name

 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  lcd.init();     // Initiate LCD
  lcd.backlight();  //Initiate LCD backlight
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  //  LCD welcome screen
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(2, 1);
  lcd.print("Present Card");
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
  if (content.substring(1) == "F3 2A D3 A5") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(100);
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 900);
    delay(300);
    noTone(BUZZER);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted!");
    delay(300);
    myServo.write(180);
    delay(5000);
    lcd.clear();
    myServo.write(0);
    digitalWrite(LED_G, LOW);
    delay(1500);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(100);
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied!");
    delay(1500);
    lcd.clear();
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
    delay(1500);
  }
}
