#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 51   
#define motor 50
#define DHTTYPE DHT11  
#define botao1 20
#define botao2 21


const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;//Pinos para ligar o display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Define os pinos que serão usados para ligar o display

DHT dht(DHTPIN, DHTTYPE);

int t_user = 22;

void setup() {
  pinMode(DHTPIN, INPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(F("Sistema iniciado"));
  delay(2000);

  attachInterrupt(digitalPinToInterrupt(botao1), subir_temp, RISING);
  attachInterrupt(digitalPinToInterrupt(botao2), descer_temp, RISING);
}

void loop() {

  int u = dht.readHumidity();
  int t = dht.readTemperature();

  if (isnan(u) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(u);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temperatura"));
  lcd.setCursor(0, 1);
  lcd.print(F("atual: "));
  lcd.print(t);
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temperatura"));
  lcd.setCursor(0, 1);
  lcd.print(F("acionamento: "));
  lcd.print(t_user);
  delay(3000);

  if(t >= t_user){
    digitalWrite(motor, HIGH);
  } else{
    digitalWrite(motor, LOW);
    Serial.println("entrou no if");
  }

}

void subir_temp(){
  Serial.println(F("FUNÇÃO ATIVADA"));
  t_user++;
  delay(5000);
  Serial.println(t_user);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temperatura de"));
  lcd.setCursor(0, 1);
  lcd.print(F("acionamento: "));
  lcd.print(t_user);
  delay(5000);
  lcd.clear();
}

void descer_temp(){
  Serial.println(F("FUNÇÃO ATIVADA"));
  t_user--;
  delay(5000);
  Serial.println(t_user);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Temperatura de"));
  lcd.setCursor(0, 1);
  lcd.print(F("acionamento: "));
  lcd.print(t_user);
  delay(5000);
  lcd.clear();
}