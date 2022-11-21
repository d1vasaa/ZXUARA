 // This code was made by Team ZXUARA. Please do not copy our code, thank you.
 // libraries //
#include <dht.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
// libraries //

// variables //
#define dht_apin A0 // Analog Pin sensor is connected to
dht DHT;
int SoilSensor = A1; 
int sensorValue;  
int h;
int t;
bool condition;
char iv = 0;
// variables //

// setup //
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  Serial.begin(9600); 
  pinMode(9, OUTPUT); // Pin setup for the water pump.
  pinMode(8, OUTPUT); // Pin setup for the fan.
  pinMode(SoilSensor, INPUT);
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight
  //  SDA --> A4
  //  SCL --> A5
}
// setup //

// the logic //
void loop() {
  // the code for the soil moisture sensor, mobile app and water pump ig //
  condition = true;
  iv = Serial.read();
  Serial.println(iv);
  if (iv == '0') {
    while(condition==true) {
      digitalWrite(9, HIGH);
      Serial.println("on");
      char avn = Serial.read();
      Serial.println(avn);
      if (avn == '1') {
        condition = false;
      }
    }
  } else {
    digitalWrite(9, LOW);
    Serial.println("off");
    sensorValue = analogRead(SoilSensor); 
    Serial.println("Analog Value : ");
    Serial.println(sensorValue);
    if (sensorValue>900) {
      digitalWrite(9, HIGH); 
    } else {
      digitalWrite(9, LOW);
    }
    iv = Serial.read(); 
    Serial.println(iv);
  }
  // the code for the soil moisture sensor, mobile app and water pump ig //
  
  // the code for the I2C LCD 16x2 //
  DHT.read11(dht_apin);
  h = DHT.humidity;
  t = DHT.temperature;

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %, Temp: ");
  Serial.print(t);
  Serial.println(" ° Celsius");

  lcd.setCursor(0, 0);
  lcd.println(" Now Temperature ");
    
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("C");

  lcd.setCursor(6, 1);
  lcd.println("2022 ");
     
  lcd.setCursor(11, 1);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");

  delay(1000);
  // the code for the I2C LCD 16x2 //

  // the code for the fan ig //
  if (t > 31) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
  // the code for the fan ig //
}
// the logic // 
