#include <ESP32Servo.h>

const int FwdPin_A = 26;
const int BwdPin_A = 25;
const int FwdPin_B = 16;
const int BwdPin_B = 17;

const int TrigPin = 14;
const int EchoPin = 27;

const int ServoPin = 12;
const int PumpPin = 13;

const float DistanceThreshold = 20.0; // см
const int MaxSpd = 255;
const int LowSpd = 0;

Servo seedServo;
unsigned long lastObstacleTime = 0;
bool seedActionDone = false;

void setup() {
  pinMode(FwdPin_A, OUTPUT);
  pinMode(BwdPin_A, OUTPUT);
  pinMode(FwdPin_B, OUTPUT);
  pinMode(BwdPin_B, OUTPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(PumpPin, OUTPUT);

  seedServo.attach(ServoPin);
  seedServo.write(0);

  digitalWrite(PumpPin, LOW);
  lastObstacleTime = millis();
}

float getDistance() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  long duration = pulseIn(EchoPin, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

void moveForward() {
  analogWrite(FwdPin_A, MaxSpd);
  analogWrite(BwdPin_A, LowSpd);
  analogWrite(FwdPin_B, MaxSpd);
  analogWrite(BwdPin_B, LowSpd);
}

void moveBackward() {
  analogWrite(FwdPin_A, LowSpd);
  analogWrite(BwdPin_A, MaxSpd);
  analogWrite(FwdPin_B, LowSpd);
  analogWrite(BwdPin_B, MaxSpd);
}

void turnRight() {
  analogWrite(FwdPin_A, MaxSpd);
  analogWrite(BwdPin_A, LowSpd);
  analogWrite(FwdPin_B, LowSpd);
  analogWrite(BwdPin_B, MaxSpd);
}

void stopMoving() {
  analogWrite(FwdPin_A, 0);
  analogWrite(BwdPin_A, 0);
  analogWrite(FwdPin_B, 0);
  analogWrite(BwdPin_B, 0);
}

void dropSeedAndWater() {
  stopMoving();
  delay(1000);            
  seedServo.write(45);     
  delay(500);
  seedServo.write(0);       
  delay(300);
  digitalWrite(PumpPin, HIGH);
  delay(500);
  digitalWrite(PumpPin, LOW);
}

void loop() {
  float distance = getDistance();

  if (distance > 0 && distance < DistanceThreshold) {
    lastObstacleTime = millis();
    seedActionDone = false;
    moveBackward();
    delay(2000);
    turnRight();
    delay(2000);
  } else {
    moveForward();
  }
  if (!seedActionDone && millis()-lastObstacleTime>5000) {
    dropSeedAndWater();
    seedActionDone=true; 
    lastObstacleTime=millis();
  }

  delay(100);
}
