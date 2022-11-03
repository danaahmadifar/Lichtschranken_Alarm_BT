#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); //RX | TX

const int photoPin = A0;
int signal = A3;
int photoValue = 0;
const int ledPin = 6;
const int photoStrom = 7;
const int ausButton = 11;
int button = 0;
int buttonstate = 0;
const int ausSignal = 9;

void setup()  {
    pinMode(ledPin, OUTPUT); //setzt D6 Pin als Output für die Alarm-LED
    pinMode(photoStrom, OUTPUT); //setzt den D7 Pin als Output für die Photodiode
    pinMode(signal, OUTPUT);
    pinMode(ausButton, INPUT_PULLUP); //setzt den D11 Pin als PULL-UP Input, bedeuted 0 wenn nicht verbunden mit GND und 1 bei verbindung mit GND 
    digitalWrite(photoStrom, HIGH); //aktiviert die Stromversorgung für die Photodiode

    Serial.begin(9600); //aktiviert die Datenrate bei 9600 Bits pro Sekunde (Baudrate)
    BTserial.begin(38400); //aktiviert die Bluetoothdatenrate bei 38400 Bits pro Sekunde
}

void loop() {
  photoValue = analogRead(photoPin); //liest den Analogen Signal der Photodiode
  button = digitalRead(ausButton);  //Schaut ob ausButton Signal an GND liegt
  int sensorValue = analogRead(A0); //setzt den abgelesenen Wert von A0 (10-Bit ADC) in sensorValue (0-1024)
  Serial.println(sensorValue);      //zum Überprüfen im Serial Monitor
  Serial.println(button);           //siehe Z.34
  if (photoValue > 1000) {          //löst ab dem Wert Alarm aus
    while(button == HIGH){          //solange Ausbutton nicht gedrückt ist
      digitalWrite(ledPin, HIGH);   //aktiviert die Alarm-LED
      BTserial.print(1);            //sendet Alarm-Signal über Bluetooth an den SLAVE/Alarmanlage
      button = digitalRead(ausButton); //schaut ob Ausbutton gedrückt ist
      delay(100);                      //delay für Stabilität
    }
  }
  if (photoValue < 1000){             //löst bei diesen Werten kein Alarm aus
    digitalWrite(ledPin, LOW);        //deaktiviert Alarm-LED falls an, bzw. lässt sie ausbleibem
    BTserial.print(0);                //sendet OK-Signal an SLAVE/Alarmanlage
    delay(100);                       //delay für Stabilität
  }
}