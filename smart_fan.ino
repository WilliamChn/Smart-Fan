#include <dht.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,3);  // set the LCD address and the number of columns and rows

#define tempsensor 2       

#define FAN 7
#define RED_LIGHT 6
#define BLUE_LIGHT 5
#define Increase 13
#define Decrease 12
dht DHT;

void setup() {

  lcd.begin();

  pinMode(FAN, OUTPUT); 
  pinMode(Increase, INPUT_PULLUP);
  pinMode(Decrease, INPUT_PULLUP);

  pinMode(RED_LIGHT, OUTPUT);
  pinMode(BLUE_LIGHT, OUTPUT);
  digitalWrite(FAN, LOW);

  Serial.begin(9600);
  
}

int pressed = 0;
int threshold = 76;

void loop() {
  Serial.println(threshold);

  int increaseButton = digitalRead(13);
  int decreaseButton = digitalRead(12);

  delay (10);

  if (decreaseButton == pressed) {
    threshold -= 1;
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Set Temperature");
    lcd.setCursor(0,1);  
    lcd.print(threshold);
    lcd.print(" F");
    delay(1500);
    lcd.clear();
  }

  if (increaseButton == pressed) {
    threshold += 1;
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Set Temperature");
    lcd.setCursor(0,1); 
    lcd.print(threshold);
    lcd.print(" F");
    delay(1500);
    lcd.clear();
  }

  DHT.read11(tempsensor);

  float cel = DHT.temperature;
  float temperature = (cel * 9.0 / 5.0) + 32.0;
  int temp = temperature;

  
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println("°F");

  lcd.setCursor(0,0);  
  lcd.print(temp);

  if (temperature > threshold) { 
    digitalWrite(FAN, HIGH); 
    digitalWrite(RED_LIGHT, LOW);  
    digitalWrite(BLUE_LIGHT, HIGH);   
    Serial.println("Fan ON");
    lcd.setCursor(0,1); 
    lcd.print("Fan On");
  } else {
    digitalWrite(FAN, LOW); 
    digitalWrite(RED_LIGHT, HIGH);   
    digitalWrite(BLUE_LIGHT, LOW);  
    Serial.println("Fan OFF");
    lcd.setCursor(0,1); 
    lcd.print("Heater On");
  }


}