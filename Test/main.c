#include <LiquidCrystal.h>
#define RS PC_6
#define EN PB_7
#define D4 PA_2
#define D5 PA_3
#define D6 PA_4
#define D7 PB_6
#define sensorPin PE_2

int sensorValue ;
float voltages;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
void setup() {
   lcd.begin(16, 2);
   lcd.setCursor(0, 0);
  lcd.print("CircuitDigest");
  delay(2000);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  lcd.setCursor(0, 0);
  lcd.print("ADC value:");
  lcd.setCursor(10, 0);
  lcd.print(sensorValue);
  lcd.setCursor(0, 1);
  lcd.print("Voltages:");
  voltages=(sensorValue*3.3)/4096;
  lcd.setCursor(10, 1);
  lcd.print(voltages);
delay(1000);
}
