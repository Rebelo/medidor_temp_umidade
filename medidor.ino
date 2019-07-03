#include "DHT.h"
#include "DHT_U.h"
#include "LiquidCrystal.h"

#define dht_dpin A1
#define switch_button_pin 13

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(dht_dpin, DHT11);
int switch_button_state = 0;
int previous_counter = 0;
int previous_temperature_C = 0;
int previous_temperature_F = 0;
int previous_humidity = 0;
int counter = 0;

void setup() {
	lcd.begin(16, 2);
 
	Serial.begin(10000);
  dht.begin();

  pinMode(switch_button_pin, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Temp(Celsius)");
  lcd.setCursor(0, 3);
  lcd.print(round(dht.readTemperature(false)));
  lcd.print("C");
}

void loop() {
  int temperature_C = round(dht.readTemperature(false));
  int temperature_F = round(dht.readTemperature(true));
  int humidity = round(dht.readHumidity(false));
  
  delay(1000);

  switch_button_state = digitalRead(switch_button_pin);
  
  previous_counter = counter;
  
  if(switch_button_state == HIGH)
    counter++;
  if(counter > 2)
  counter = 0;

  switch(counter){
    case 0: if(previous_counter == counter || previous_temperature_C == temperature_C){
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Temp(Celsius)");
              lcd.setCursor(0, 3);
              lcd.print(temperature_C);
              lcd.print("C");
             }
             break;
    case 1: if(previous_counter == counter || previous_temperature_F == temperature_F){
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Temp(Fahrenheit):");
              lcd.setCursor(0, 3);
              lcd.print(temperature_F);
              lcd.print("F");
             }
             break;
    case 2: if(previous_counter == counter || previous_temperature_F == temperature_F){
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Umidade");
              lcd.setCursor(0, 3);
              lcd.print(humidity);
              lcd.print("%");
            }
            break;
  }

  previous_temperature_C = temperature_C;
  previous_temperature_F = temperature_F;
  previous_humidity = humidity;
}
