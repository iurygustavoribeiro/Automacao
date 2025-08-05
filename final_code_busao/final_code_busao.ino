#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int leader_counter;
int matriz_counter;
int jacobina3_counter;

void setup() {
  // put your setup code here, to run once:	
  Serial.begin(9600);
  Serial.println();
  Serial.print(F("Testando Serial... Aproxime o cartão \n"));
  rfid.PCD_Init();
  SPI.begin();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(F("OI MOTORISTA! :)"));
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("ACOMPANHE AS"));
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(F("INFORMACOES AQUI"));
  delay(3000);

  for (byte i = 0; i < 6; i++) {
     key.keyByte[i] = 0xFF;
  }
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent()){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Leader: "));
      lcd.print(leader_counter);
      lcd.setCursor(0, 1);
      lcd.print(F("Jacobina 3: "));
      lcd.print(jacobina3_counter);
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Matriz: "));
      lcd.print(matriz_counter);
      delay(3000);
  }

  if ( ! rfid.PICC_ReadCardSerial())
    return;
  
  byte sector         = 1;
  byte blockAddr      = 4;
  byte trailerBlock   = 7;
  MFRC522::StatusCode status;  
  byte buffer[18];
  byte size = sizeof(buffer);

  //Serial.println(F("Current data in sector:"));
  rfid.PICC_DumpMifareClassicSectorToSerial(&(rfid.uid), &key, sector);
  Serial.println();

  //Serial.print(rfid.MIFARE_Read(blockAddr, buffer, &size));
  //Serial.println();
  //Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
  dump_byte_array(buffer, &size); //Serial.println();

  if (buffer[0] == 0x01){
      Serial.println();
      Serial.print(F("O bairro do aluno é Leader \n"));  
      Serial.print(F("O número de pessoas neste bairro é: "));
      leader_counter++;
      Serial.print(leader_counter);
      //lcd.clear();
      //lcd.setCursor(0,0);
      //lcd.print("Leader:");
      //lcd.setCursor(0,1);
      //lcd.print(leader_counter);
    }
    else if (buffer[0] == 0x02){
      Serial.println();
      Serial.print(F("O bairro do aluno é Matriz \n"));  
      Serial.print(F("O número de pessoas neste bairro é: "));
      matriz_counter++;
      Serial.print(matriz_counter);
      //lcd.clear();
      //lcd.setCursor(0,0);
      //lcd.print("Matriz:");
      //lcd.setCursor(0,1);
      //lcd.print(matriz_counter);
      }
    else if (buffer[0] == 0x03){
      Serial.println();
      Serial.print(F("O bairro do aluno é Jacobina 3 \n"));  
      Serial.print(F("O número de pessoas neste bairro é: "));
      jacobina3_counter++;
      Serial.print(jacobina3_counter);
      //lcd.clear();
      //lcd.setCursor(0,0);
      //lcd.print("Jacobina 3:");
      //lcd.setCursor(0,1);
      //lcd.print(matriz_counter);
      }
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();
      }

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
  }
