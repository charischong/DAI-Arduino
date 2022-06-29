// Motor A connections
int enA = 9;
int dirA1 = 8;
int dirA2 = 7;
// Motor B connections
int enB = 3;
int dirB1 = 5;
int dirB2 = 4;

// Joystick
int jPinUpDown = A1;
int jPinLeftRight = A2;
int jVal;
int jVal2;
int mSpeed;
int MAXSPEED = 50.0;
int SPEED =45.0;

void setup() {
  // Set Joystick input
  pinMode(jPinUpDown,INPUT);
  pinMode(jPinLeftRight,INPUT);
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(dirA1, OUTPUT);
  pinMode(dirA2, OUTPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(dirA1, LOW);
  digitalWrite(dirA2, LOW);
  digitalWrite(dirB1, LOW);
  digitalWrite(dirB2, LOW);
  Serial.begin(9600); // for the serial monitor
}

void loop() {
  jVal = analogRead(jPinUpDown);
  jVal2 = analogRead(jPinLeftRight);
//  Serial.println("jVal");
  Serial.println(jVal);
//  Serial.println("jVal2");
//  Serial.println(jVal2);
  
  // joystick stick is forward
  if (jVal <10){
    mSpeed = -MAXSPEED/512.*jVal+MAXSPEED;
    moveForward(SPEED);
  }
  
  // joystick is back
  if(jVal >= 1000){
    mSpeed = (MAXSPEED/512.)*jVal-MAXSPEED;
    moveBackward(SPEED);
  }

  if (jVal2 <10){
    mSpeed = (MAXSPEED/512.)*jVal2+MAXSPEED;
    moveRight(SPEED);
  }

  if (jVal2 >= 1000){
    mSpeed = (MAXSPEED/512.)*jVal2-MAXSPEED;
    moveLeft(SPEED);
  }

  if(jVal >300 && jVal<700 && jVal2>300 && jVal2<700){
    Serial.println("stopping");
    stop();
  }

}

void moveForward(int val){
    digitalWrite(dirA1,LOW);
    digitalWrite(dirA2,HIGH);
    digitalWrite(dirB1,LOW);
    digitalWrite(dirB2,HIGH);
    analogWrite(enA,val);
    analogWrite(enB,val);
    Serial.println("forward");
}

void moveBackward(int val){
    digitalWrite(dirA1,HIGH);
    digitalWrite(dirA2,LOW);
    digitalWrite(dirB1,HIGH);
    digitalWrite(dirB2,LOW);
    analogWrite(enA,val);
    analogWrite(enB,val);
    Serial.println("backward");
}

void moveLeft(int val){
    digitalWrite(dirA1,HIGH);
    digitalWrite(dirA2,LOW);
    digitalWrite(dirB1,LOW);
    digitalWrite(dirB2,LOW);
    analogWrite(enA,val);
    Serial.println("left");
}

void moveRight(int val){
    digitalWrite(dirA1,LOW);
    digitalWrite(dirA2,LOW);
    digitalWrite(dirB1,HIGH);
    digitalWrite(dirB2,LOW);
    analogWrite(enB,val);
    Serial.println("right");
}

void stop(){
  analogWrite(enA,0);
  analogWrite(enB,0);
}
