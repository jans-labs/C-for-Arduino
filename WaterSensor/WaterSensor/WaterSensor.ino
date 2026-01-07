// Add libraries
#include <LiquidCrystal_I2C.h>

// define the pins
#define waterSensorPin A0
#define LED_B 11    // blue LED define
#define LED_Y 12    // yellow LED define
#define LED_R 13    // red LED define
#define BUZZER 2    // buzzer

LiquidCrystal_I2C lcd(0x27, 16, 2); // Create LCD instance.

void setup() {
  Serial.begin(9600);
  lcd.init();           //Initiate LCD
  lcd.backlight();      //Initiate LCD backlight
  pinMode(LED_B, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  noTone(BUZZER);
}

void loop() {
  // Read the input on analog pin 0
  int sensorValue = analogRead(waterSensorPin);

  // Print out the value
  Serial.print("Water Level: ");
  Serial.println(sensorValue);

  // Check if the water level is above threshold
  if (sensorValue < 300) {
    digitalWrite(LED_Y, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 900);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LEVEL: LOW");  

  } else if (sensorValue < 380) {
    noTone(BUZZER);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_Y, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LEVEL: MEDIUM");   
  
  } else {
      noTone(BUZZER);
      digitalWrite(LED_Y, LOW);
      digitalWrite(LED_B, HIGH);
      digitalWrite(LED_R, LOW);
      lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LEVEL: HIGH");   
  }
  // Wait for a seconf before taking the next reading
  delay(500);

}
