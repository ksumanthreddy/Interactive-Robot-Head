#include <Servo.h>

Servo eyeLeft, eyeRight, cheekLeft, cheekRight, jawUp, jawDown;

void setup() {
  Serial.begin(9600);  // Communication with laptop
  eyeLeft.attach(9);   // Adjust pins based on your wiring
  eyeRight.attach(10);
  cheekLeft.attach(11);
  cheekRight.attach(12);
  jawUp.attach(13);    // Jaw up/down can share a servo or use two
  jawDown.attach(6);
  
  // Neutral positions
  eyeLeft.write(90);
  eyeRight.write(90);
  cheekLeft.write(90);
  cheekRight.write(90);
  jawUp.write(90);
  jawDown.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'H') {  // Happy: Cheeks up, eyes neutral, jaw slightly open
      cheekLeft.write(120);
      cheekRight.write(120);
      jawUp.write(100);
      eyeLeft.write(90);
      eyeRight.write(90);
    } else if (command == 'S') {  // Sad: Cheeks down, eyes down, jaw open
      cheekLeft.write(60);
      cheekRight.write(60);
      jawUp.write(80);
      eyeLeft.write(60);
      eyeRight.write(60);
    } else if (command == 'N') {  // Neutral: Reset all
      eyeLeft.write(90);
      eyeRight.write(90);
      cheekLeft.write(90);
      cheekRight.write(90);
      jawUp.write(90);
      jawDown.write(90);
    } else if (command == 'T') {  // Talk: Jaw moves
      jawUp.write(70);
      delay(200);
      jawUp.write(90);
    } else if (command == 'B') {  // Blink
      eyeLeft.write(0);
      eyeRight.write(0);
      delay(200);
      eyeLeft.write(90);
      eyeRight.write(90);
    }
  }
}
