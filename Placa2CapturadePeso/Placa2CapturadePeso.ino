#include <HX711_ADC.h> // Biblioteca Sensor
#include <Wire.h> // Biblioteca LCD
#include <LiquidCrystal_I2C.h> // Biblioteca LCD
HX711_ADC LoadCell(6, 7); // Sensor DT pino 6, SCK pino 7
LiquidCrystal_I2C lcd(0x27, 16,2); // 0x27 Checar se o LCD está nesse canal

void setup()
{
  Serial.begin(9600); // Inicia a comunicação serial na velocidade de 9600 - Baud Rate
  LoadCell.begin(); 
  LoadCell.start(1000); // Tempo de estabilização
  LoadCell.setCalFactor(1000.0); // Parâmetro de calibração
  lcd.init(); 
  lcd.backlight();
}

void loop()
{ 
  LoadCell.update(); // Mostrar peso arduino
  float i = LoadCell.getData(); 
  lcd.setCursor(0, 0); 
  lcd.print("BALANCA GENOVA"); 
  lcd.setCursor(0, 1); 
  lcd.print(i);
  lcd.print(" KG *");
  Serial.println(i);
  delay(100);
}
