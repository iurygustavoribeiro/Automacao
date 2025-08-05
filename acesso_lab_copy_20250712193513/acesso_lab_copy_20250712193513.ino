#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define rele_tranca 4

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  rfid.PCD_Init();
  SPI.begin();

  for (byte i = 0; i < 6; i++) {
     key.keyByte[i] = 0xFF;
  }

  Serial.print(F("Testando serial, aproxime o cartão\n"));
  pinMode(rele_tranca, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  if ( ! rfid.PICC_IsNewCardPresent()){
  delay(3000);
  Serial.print(F("Nenhum cartão detectado\n"));
  return;}

  if ( ! rfid.PICC_ReadCardSerial())
    return;

  byte sector         = 1;
  byte blockAddr      = 4;
  byte trailerBlock   = 7;
  MFRC522::StatusCode status;  
  byte buffer[18];
  byte size = sizeof(buffer);

  rfid.PICC_DumpMifareClassicSectorToSerial(&(rfid.uid), &key, sector);
  Serial.println();

  dump_byte_array(buffer, &size);

  if (buffer[0] == 0x28){
    digitalWrite(rele_tranca, HIGH);
    Serial.println(F("Acesso liberado!"));
    delay(8000);
    digitalWrite(rele_tranca, LOW);
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