#include "DHT.h" 
#include <Adafruit_SSD1306.h> 
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>

#define DHTPIN 7   
#define rele 12  
#define bt1 2 
#define bt2 3 
#define PIR 4 

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define DHTTYPE DHT11
#define OLED_RESET     -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

int t_user = 22; 

void setup() {
  pinMode(DHTPIN, INPUT); 
  pinMode(PIR, INPUT);
  pinMode(bt1, INPUT); 
  pinMode(bt2, INPUT); 
  pinMode(rele, OUTPUT); 

  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  
  dht.begin(); 
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.display(); 
  delay(500); 
  display.clearDisplay(); 
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0, 0); 
  display.setTextSize(2); 
  display.print("Iniciando..."); 
  display.display(); 

  delay(1000); 

  attachInterrupt(digitalPinToInterrupt(bt1), subir_temp, FALLING); 
  attachInterrupt(digitalPinToInterrupt(bt2), descer_temp, FALLING); 

void loop() {
  int t = dht.readTemperature();
  
  Serial.print("temperatura atual: ");
  Serial.println(t);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("Temperatura atual: ");
  display.print(t);
  display.display();

  delay(2000);
  
  Serial.print("Presença: ");
  Serial.println(digitalRead(PIR));
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Temperatura programada: ");
  display.print(t_user);
  display.display();

  Serial.print("temperatura programada: ");
  Serial.println(t_user);

  delay(2000);

  if(t >= t_user && digitalRead(PIR) == HIGH){
    digitalWrite(rele, HIGH);
  } else{
    digitalWrite(rele, LOW);
    Serial.println("entrou no if");
  }

}

void subir_temp(){
  t_user++;
  delay(1000);
  Serial.println("ativado");
}

void descer_temp(){
  t_user--;
  delay(1000);
  Serial.println("ativado");
}