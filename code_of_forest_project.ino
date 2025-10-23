const int FwdPin_A = 25;  
const int BwdPin_A = 26;  
const int FwdPin_B = 17;  
const int BwdPin_B = 16;  

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
}

void moveBackward() {
  analogWrite(FwdPin_A, MaxSpd);
  analogWrite(BwdPin_A, LowSpd);
  analogWrite(FwdPin_B, MaxSpd);
  analogWrite(BwdPin_B, LowSpd);
}

void turnRight() {
  analogWrite(FwdPin_A, LowSpd);
  analogWrite(BwdPin_A, MaxSpd);
  analogWrite(FwdPin_B, LowSpd);
  analogWrite(BwdPin_B, MaxSpd);
}

void loop() {
  float distance = getDistance();
  
  if (distance < DistanceThreshold && distance > 0) {
    moveBackward();  
    delay(2000);
    turnRight();     
    delay(2000);
  } else {
    moveForward();   
  }
  
  delay(100);  
}
