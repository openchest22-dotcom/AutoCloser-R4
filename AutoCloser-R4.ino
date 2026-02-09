#include "Keyboard.h" // Klavye emülasyonu için gerekli

const int trigPin = 9;
const int echoPin = 10;
const int mesafeSiniri = 100; // Kaç cm kala Alt+F4 atsın? (1 metre)

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Klavye özelliğini başlat
  Keyboard.begin();
  
  // Hata payını önlemek için kısa bir açılış beklemesi
  delay(2000); 
}

void loop() {
  // Mesafe ölçümü
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Eğer biri belirlediğin mesafeden daha yakınsa
  if (distance > 0 && distance < mesafeSiniri) {
    
    // Alt + F4 Kombinasyonu
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    
    delay(100); // Tuşlara basılı tutma süresi
    
    Keyboard.releaseAll(); // Tuşları bırak
    
    // Arkasından seri köz getirir gibi ekranın kapanması için 
    // kısa bir bekleme koyalım ki sürekli komut göndermesin
    delay(3000); 
  }

  delay(50); // Tarama hızı
}
