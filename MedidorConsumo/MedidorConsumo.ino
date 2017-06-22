#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "EmonLib.h"
#include <SPI.h>
 
EnergyMonitor emon;
 
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

//Pino do sensor SCT
int pin = 1;
 
void setup()
{
  Serial.begin(9600);
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 2000/33 = 60
  emon.current(pin, 60);
  display.begin();
  display.setContrast(48);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.drawRect(0, 0, 84, 48,  2);
  display.fillRect(0, 0, 84, 15,  2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(18, 4);
  display.println("Watts");
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(2);
}
 
void loop()
{
  double Irms = emon.calcIrms(20);
  int voltagem = 220;
  Serial.print("Corrente : ");
  Serial.print(Irms);
 
  display.fillRect(4, 15, 55 , 20, 0);
  display.setCursor(8, 22);
  display.println(Irms*voltagem, 2);
  display.display();
  display.setCursor(67, 22);
  display.println("W");
  delay(1000);
}
