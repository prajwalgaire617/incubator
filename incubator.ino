

#include <Servo.h>

#include <LiquidCrystal.h>

#include "DHT.h"

#define DHTPIN 2 // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Servo servo;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  //these pins are for lcd screen

void setup() {

  pinMode(3, OUTPUT);   //relay pin
  pinMode(13, OUTPUT);  //motor pin
  servo.attach(11);     //11 for servo motor

  dht.begin();
  lcd.begin(16, 2);
 
}

void loop() {

  for (int i = 0; i <= 180; i += 1) {
    servo.write(i);
    delay(15);
  }

  for (int i = 180; i >= 0; i -= 1) {
    servo.write(i);
    delay(15);
  }


  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    lcd.print("Failed to read from DHT sensor!");
    return;
  }


  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %");





  if (h > 75) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  if (t < 37.5) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }

}
