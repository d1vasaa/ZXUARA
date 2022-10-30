 // This code was made by Team ZXUARA. Please do not copy our code, thank you.
 //  I2C LCD1602
 //  SDA --> A4
 //  SCL --> A5

//Libraries
#include <dht.h> 
//I2C LCD:
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
  
//Constants
#define dht_apin A0 // Analog Pin sensor is connected to
dht DHT;
int sensorPin = A1;
int sensorValue;  

//Variables
//int chk;
int h;  // Stores humidity value
int t; // Stores temp erature value

void setup()
{
    Serial.begin(9600); 
    pinMode(9, OUTPUT); // pin setup for the water pump
    pinMode(8, OUTPUT); // pin setup for the fan
    Serial.println("Temperature and Humidity Sensor Test");
    lcd.init(); //initialize the lcd
    lcd.backlight(); //open the backlight
}

void loop()
{
    // Read's sensor data and prints it our in serial monitor
    sensorValue = analogRead(sensorPin); 
    Serial.println("Analog Value : ");
    Serial.println(sensorValue);
    // Read data and store it to variables h (humidity) and t (temperature)
    // Reading temperature or humidity takes about 250 milliseconds!
    DHT.read11(dht_apin);
    h = DHT.humidity;
    t = DHT.temperature;
    
    // Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %, Temp: ");
    Serial.print(t);
    Serial.println(" ° Celsius");

    // When the data is more than 800 it determines that the detection input is dry. 
    // If sensor data is more than 800, d9 turns on. Else, d9 turns off.
        
    if (sensorValue<900) {
      digitalWrite(9, LOW); 
    } else {
      digitalWrite(9,HIGH); 
    }
    delay(1000); // Delay 1 second.
        
// set the cursor to (0,0):
// print from 0 to 9:

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
    
  delay(1000); //Delay 1 sec.

// If the temperature data collected by the dht11 is more than 33 degree celsius, the fan will be turned on.

  if (t > 36) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }
}
