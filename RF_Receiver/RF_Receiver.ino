#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 7);
const byte addresses[][6] = { "00001", "00002" };

int led = 2;

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  radio.startListening();
  
  if (radio.available()) {
    char b[32];
    radio.read(&b, sizeof(b));
    String receivedMessage = String(b);
    
    Serial.println(receivedMessage + " geldi");

    if (receivedMessage == "on") {
      digitalWrite(led, HIGH);
    } else if (receivedMessage == "off") {
      digitalWrite(led, LOW);
    }
    
    delay(5);
  }
}
