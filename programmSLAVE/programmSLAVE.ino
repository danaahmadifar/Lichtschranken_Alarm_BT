#include <SoftwareSerial.h>
#include <LiquidCrystal.h>     //Library für LCD Display
#define ledPin 5

SoftwareSerial BTserial(2, 3); // RX | TX
char state;                    //Datentyp für Bluetooth Outputsignal
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7; //PINS für LCD Display RS=Register Select, EN=Enable Pin, D4-D7=4 Wire Mode für Data
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                   //aktiviert Library Befehle für LCD
int cursorColumn = 0;                                        //Datentyp für Cursor der LCD

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);  //ledPin versorgt auch den Buzzer, setzt den PIN in Outputmode
  Serial.begin(9600);       //aktiviert die Datenrate bei 9600 Bits pro Sekunde (Baudrate)
  BTserial.begin(9600);     //aktiviert die Bluetoothdatenrate bei 9600 Bits pro Sekunde (Baudrate)

  lcd.begin(16, 2);          //aktiviert die LCD mit 16 Spalten und 2 Zeilen
  lcd.print("Verbinde...");  //LCD zeigt "Verbinde..." bis BT Module verbunden sind
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 1);         //setzt den Cursor auf Spalte 0 und Zeile 1
  if (BTserial.available() > 0) {  //schaut ob Bluetooth Signal kommt
      state = BTserial.read();      //liest den Bluetooth Signal und schreibt disen in state
      Serial.write(state);          //zum Überprüfen im Serial Monitor
    }
  if (state == '0') {               //falls eine 0 über Bluetooth kommt
    digitalWrite(ledPin, LOW);      //Alarm bleibt aus
    lcd.clear();                    //löscht Inhalt auf dem LCD
    lcd.print("ALARM BEREIT");      //Sagt dem User, dass Alarm bereit ist
    delay(100);                     //delay für Stabilität
    state = BTserial.read();        //liest den Bluetooth Signal erneut
    }
  else if (state == '1') {          //falls eine 1 über Bluetooth kommt
    digitalWrite(ledPin, HIGH);     //Aktiviert Alarm
    lcd.clear();                    //löscht Inhalt auf dem LCD
    lcd.print("ALARM!");            //printet ALARM auf dem LCD
    delay(100);                     //cooler Alarm Effekt
    digitalWrite(ledPin, LOW);      //gehört zum coolen Alarm Effekt
    delay(100);                     //immernoch cooler Alarm Effekt
    state = BTserial.read();        //liest den Bluetooth Signal erneut
  }
}
