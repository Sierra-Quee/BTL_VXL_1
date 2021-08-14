#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#define pirPin  4
#define relayPin 2
#define buzzPin 5
#define buttonPin 12
#define ledPin 17


bool isPushOnApp = false;
int VIRTUAL_PIN_0;

char auth[] = "FbQq7ozGSgUWcOeQbSx2kyjDHZeLIhcd";

char ssid[] = "Tung mat";
char pass[] = "0866127261";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  // connect to wifi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Blynk.begin(auth, ssid, pass); 
}


void loop() {
  // put your main code here, to run repeatedly:
  
Blynk.run();

//dong bo nut nhan va app Blynk
if (isPushOnApp == true) // if button on app is pushed
{
    digitalWrite(ledPin, VIRTUAL_PIN_0); //write status of V0 to led
    isPushOnApp = false; // delete variation
}

if (digitalRead(buttonPin) == 0) // if button is pushed
{
    while (digitalRead(buttonPin) == 0); 
    if (digitalRead(buttonPin) == 1);
    {
        VIRTUAL_PIN_0 = !VIRTUAL_PIN_0; // swap value       
        digitalWrite(ledPin,VIRTUAL_PIN_0); // write value to led
        Blynk.virtualWrite(V0, VIRTUAL_PIN_0); // write value on app by V0
    }
}

  // receive value from pir sensor
if (digitalRead(pirPin) == HIGH)
{    
    digitalWrite(relayPin, LOW);  
    digitalWrite(buzzPin, LOW);
}
  else 
  {
      digitalWrite(relayPin, HIGH);  
      digitalWrite(buzzPin, HIGH);
  }   
}

BLYNK_CONNECTED() 
{
    Blynk.syncAll();
}
BLYNK_WRITE(V0)
{
    VIRTUAL_PIN_0 = param.asInt();
    isPushOnApp = true;
}
