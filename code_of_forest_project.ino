const int FwdPin_A = 25;  
const int BwdPin_A = 26;  
const int FwdPin_B = 17;  
const int BwdPin_B = 16;  
const int FwdPin_C = 27;  
const int BwdPin_C = 12; 
const int FwdPin_D = 2;   
const int BwdPin_D = 13;  

const int TrigPin = 5;    
const int EchoPin = 4;    
const float DistanceThreshold = 20.0; 

int MaxSpd = 255;
int LowSpd = 0;

void setup() {
  pinMode(FwdPin_A, OUTPUT);
  pinMode(BwdPin_A, OUTPUT);
  pinMode(FwdPin_B, OUTPUT);
  pinMode(BwdPin_B, OUTPUT);
  pinMode(FwdPin_C, OUTPUT);
  pinMode(BwdPin_C, OUTPUT);
  pinMode(FwdPin_D, OUTPUT);
  pinMode(BwdPin_D, OUTPUT);
  
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

float getDistance() {
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  long duration = pulseIn(EchoPin, HIGH);
  float distance = duration * 0.034 / 2;  
  return distance;
}

void moveForward() {
  analogWrite(FwdPin_A, LowSpd);
  analogWrite(BwdPin_A, MaxSpd);
  analogWrite(FwdPin_B, LowSpd);
  analogWrite(BwdPin_B, MaxSpd);
  analogWrite(FwdPin_C, LowSpd);
  analogWrite(BwdPin_C, MaxSpd);
  analogWrite(FwdPin_D, MaxSpd);
  analogWrite(BwdPin_D, LowSpd);
}

void moveBackward() {
  analogWrite(FwdPin_A, MaxSpd);
  analogWrite(BwdPin_A, LowSpd);
  analogWrite(FwdPin_B, MaxSpd);
  analogWrite(BwdPin_B, LowSpd);
  analogWrite(FwdPin_C, MaxSpd);
  analogWrite(BwdPin_C, LowSpd);
  analogWrite(FwdPin_D, LowSpd);
  analogWrite(BwdPin_D, MaxSpd);
}

void turnRight() {
  analogWrite(FwdPin_A, LowSpd);
  analogWrite(BwdPin_A, MaxSpd);
  analogWrite(FwdPin_B, LowSpd);
  analogWrite(BwdPin_B, MaxSpd);
  analogWrite(FwdPin_C, MaxSpd);
  analogWrite(BwdPin_C, LowSpd);
  analogWrite(FwdPin_D, LowSpd);
  analogWrite(BwdPin_D, MaxSpd);
}

void loop() {
  float distance = getDistance();
  
  if (distance < DistanceThreshold && distance > 0) {
    moveBackward();  
    delay(2000);
    turnRight();     
    delay(1000);
  } else {
    moveForward();   
  }
  
  delay(100);  
}