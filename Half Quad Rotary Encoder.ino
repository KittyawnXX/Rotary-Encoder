// Code made with luv 💙 by Kittyawn aka. Alvian
// Half Quadrature Rotary Encoder

#include <LiquidCrystal.h>
#define _RS_PIN 12
#define _EN_PIN 11
#define _D4_PIN 10
#define _D5_PIN 9
#define _D6_PIN 8
#define _D7_PIN 7

LiquidCrystal lcd(_RS_PIN, _EN_PIN, _D4_PIN, _D5_PIN, _D6_PIN, _D7_PIN);

int count = 0; // var init for counting the holes inside the encoder motor
int nA = 0, oA = 0, oB = 0; // var init used for data processing on encoder
float jarak = 0;

void ISR_INT0_1(){
  nA = digitalRead(2); // FALLING or RISING mode detection
  computeEncoder(); // func callback for encoder data process  
  oA = nA; // update the var value
}

void ISR_INT1_1(){
  oB = digitalRead(3); // FALLING or RISING mode detection
  computeEncoder(); // func callback for encoder data process  
}

void computeEncoder(){
  if (nA == oA) {
    return; // Tidak ada perubahan status, keluar dari fungsi
  }

  // Rotasi Clockwise (CW) - jika A naik (HIGH) dan B LOW
  if (nA == HIGH && oB == LOW) {
    count++; // Rotasi CW
  }
  // Rotasi Counter-Clockwise (CCW) - jika A turun (LOW) dan B HIGH
  else if (nA == LOW && oB == HIGH) {
    count--; // Rotasi CCW
  }
}

void setup() {
  pinMode(3, INPUT_PULLUP); // Input A Pin init mode as INT Pull Up
  pinMode(2, INPUT_PULLUP); // Input B Pin init mode as INT Pull Up
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Test");

  // untuk mode half quadrature
  attachInterrupt(0, ISR_INT0_1, CHANGE); // init the 0 ext interrupt with BIT CHANGE mode
  attachInterrupt(1, ISR_INT1_1, CHANGE); // init the 1 ext interrupt with BIT CHANGE mode
  sei(); // declare section for activate the global interrupt
  lcd.clear();
}

void loop() {
  // wheel radius = 10 cm with 7 PPR Encoder
  jarak = count * 8.97 / 4; // algorithm for counting the distance with Half Quadrature
  lcd.setCursor(0,0);
  lcd.print("Data : "); lcd.print(count); lcd.print("  ");
  lcd.setCursor(0,1);
  lcd.print("jarak: "); lcd.print(jarak, 2); lcd.print(" cm ");
}
