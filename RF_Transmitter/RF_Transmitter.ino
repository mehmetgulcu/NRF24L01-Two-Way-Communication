#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 7);
const byte addresses[][6] = { "00001", "00002" };

int buton = 2;
bool buttonState = LOW;

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.setPALevel(RF24_PA_MIN);

  pinMode(buton, INPUT);
}

void loop() {
  bool currentButtonState = digitalRead(buton);

  if (currentButtonState == HIGH && buttonState == LOW) {
    radio.stopListening();
    String message = "on";
    char b[32];
    message.toCharArray(b, 32);
    radio.write(&b, sizeof(b));
    Serial.println("Butona basıldı, 'on' gönderildi");
    delay(100);
  }

  if (currentButtonState == LOW && buttonState == HIGH) {
    radio.stopListening();
    String message = "off";
    char b[32];
    message.toCharArray(b, 32);
    radio.write(&b, sizeof(b));
    Serial.println("Butondan el çekildi, 'off' gönderildi");
    delay(100);
  }

  buttonState = currentButtonState;
}
