#include <HX711_ADC.h> // Biblioteca Sensor
#include <Wire.h> // Biblioteca LCD
#include <LiquidCrystal_I2C.h> // Biblioteca LCD
#include <Servo.h> // Biblioteca Servo Motor
HX711_ADC LoadCell(6, 7); // Sensor DT pino 6, SCK pino 7
LiquidCrystal_I2C lcd(0x27, 16,2); // 0x27 Checar se o LCD está nesse canal
#define botao 2 // Defini o botão na entrada 2
Servo servo_3; // Defini Servo 1 na entrada 3
Servo servo_5; // Defini Servo 2 na entrada 5

void setup()
{
  Serial.begin(9600); // Inicia a comunicação serial na velocidade de 9600 - Baud Rate
  LoadCell.begin(); 
  LoadCell.start(1000); // Tempo de estabilização
  LoadCell.setCalFactor(1000.0); // Parâmetro de calibração
  lcd.init(); 
  lcd.backlight();
  
  pinMode(botao,INPUT); // Definição das entradas
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  servo_3.attach(3, 500, 2500);
  servo_5.attach(5, 500, 2500);
  pinMode(8, OUTPUT); // Defini o Buzzer
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
  
  if(digitalRead(botao)){  
  digitalWrite(9, LOW); // Tempo para a demonstração com o farol fechado
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(90);
  servo_5.write(90);
  tone(8, 523, 2000);
  delay(8000); 
  
  digitalWrite(9, LOW); // Abrindo a cancela 1 para o caminhão entrar com o farol vermeho
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(90);
  servo_5.write(93);
  delay(720); 

  digitalWrite(9,HIGH); // Cancela 1 aberta aguardando o caminhão entrar com o farol verde
  digitalWrite(12, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(90);
  servo_5.write(90); 
  delay(8000); 

  digitalWrite(9,LOW); // Fechando a cancela 1 para a pesagem
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(90);
  servo_5.write(86);
  delay(650);

  digitalWrite(9, LOW); // Aguardando a pesagem do caminhão
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(90);
  servo_5.write(90);
  delay(8000); 

  digitalWrite(9, LOW); // Abrindo a cancela 2 para o caminhão sair com o farol verde
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(80);
  servo_5.write(90);
  delay(720); 

  digitalWrite(9, LOW); // Aguardando o caminhão sair com a cancela 2 aberta e sinal verde
  digitalWrite(12, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  servo_3.write(90);
  servo_5.write(90);
  delay(8000); 

  digitalWrite(9, LOW); // Fechando a cancela 2 para realizar a outra pesagem
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(98);
  servo_5.write(90);
  delay(640); 

  digitalWrite(9, LOW); // Tempo para aguardar o outro caminhão
  digitalWrite(12, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  servo_3.write(90);
  servo_5.write(90);
  tone(8, 523, 2000);
  delay(10000); 
  }
}
