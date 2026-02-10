#include "Keyboard.h"

const int trigPin = 9;
const int echoPin = 10;
const int mesafeSiniri = 100; 
const int dogrulamaSayisi = 5; // Üst üste kaç okuma sınırın altında olmalı?

int sayac = 0; // Hatalı okumaları engellemek için

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Keyboard.begin();
  delay(2000); 
}

void loop() {
  long duration;
  int distance;

  // Mesafe ölçümü
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout ekledik (boşluğa bakınca takılmasın)
  distance = duration * 0.034 / 2;

  // Filtreleme Mantığı
  // 0 genelde hata okumasıdır, onu ve çok uzak değerleri eliyoruz
  if (distance > 2 && distance < mesafeSiniri) {
    sayac++; // Sınırın altındaysa sayacı artır
  } else {
    sayac = 0; // Mesafe tekrar açılırsa veya hatalı okuma gelirse sayacı sıfırla
  }

  // Eğer belirlediğin süre boyunca (örn: 5 okuma boyunca) birisi yakındaysa
  if (sayac >= dogrulamaSayisi) {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    delay(100); 
    Keyboard.releaseAll();
    
    sayac = 0; // İşlem bittikten sonra sayacı temizle
    delay(5000); // 5 saniye boyunca tekrar tetiklenmesin (o sırada kaçarsın)
  }

  delay(30); // Tarama hızı
}
