// Kube-Aid Operating System v1.1
// Created by Spenser Fenton (@rotarybean)
// www.github.com/rotarybean; www.thingiverse.com/rotarybean

// Code completed, compiled, and uploaded to Arduino MEGA2560 on 4/4/2024.  All function as intended.

#include <LiquidCrystal.h>
#include <SimpleDHT.h>

// Declaring digital pin 11 as the DHT11 data pin
int pinDHT11 = 11;    // Declaring digital pin 11 as the DHT11 data pin
int R5vPin = 13;       // 5v VREG enable connected to digital pin 13
int R3v3Pin = 12;     // 3v3 VREG enable connected to digital pin 12
SimpleDHT11 dht11;

// Declaring the LCD pins
const int rs = 10, en = 7, d4 = 3, d5 = 4, d6 = 5, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(R5vPin, OUTPUT);  // sets pin 13 as output
  pinMode(R3v3Pin, OUTPUT); // sets pin 12 as output
  lcd.begin(16, 2); // Initialize the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kube-Aid Booting");
  lcd.setCursor(0, 1);
  lcd.print("Wait for Doom...");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("K.A.O.S. v1.1");
  lcd.setCursor(0, 1);
  lcd.print("by @rotarybean");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing 5v");
  lcd.setCursor(0, 1);
  lcd.print("Power Rail...");
  delay(2000);
  analogWrite(R5vPin, 255);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("5v Rail Active!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing 3v3");
  lcd.setCursor(0, 1);
  lcd.print("Power Rail...");
  delay(2000);
  analogWrite(R3v3Pin, 255);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("3v3 Rail Active!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Boot Complete!");
  lcd.setCursor(0, 1);
  lcd.print("Dispensing Doom:");
  delay(3000);
}

void loop() {
  Serial.println("=================================");
  Serial.println("DHT11 readings...");


  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("DHT ERROR");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.print("Readings: ");
  Serial.print((int)temperature);
  Serial.print(" Celsius, ");
  Serial.print((int)humidity);
  Serial.println(" %");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Kube-Aid 360w");

  lcd.setCursor(0, 1);
  lcd.print(" PSU Temp: ");
  lcd.print((int)temperature);
  lcd.print("c");

  delay(750);
}
