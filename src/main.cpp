#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define TRIG GPIO_NUM_27
#define ECHO GPIO_NUM_26
#define SCL GPIO_NUM_22
#define SDA GPIO_NUM_21

LiquidCrystal_I2C lcd(0x27, 16, 2);

double duration;
double distance;

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = 0.034 * duration / 2;
  
  lcd.clear();
  lcd.print(distance);
  delay(1000);
}