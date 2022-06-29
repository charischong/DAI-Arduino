#include <Servo.h>

// servo 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0;    // variable to store the servo position
const int FSR_PIN = A0; // Pin connected to FSR/resistor divider
const int LED_PIN1 = 13;
const int LED_PIN2 = 11;
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor

// Motor A connections
int enA = 6;
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
  Serial.begin(9600); // for the serial monitor
  pinMode(FSR_PIN, INPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  
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
  
  myservo.attach(12);
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

   int fsrADC = analogRead(FSR_PIN);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) 
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;
    Serial.println("Force: " + String(force) + " g");
    Serial.println();
    if(force>100)
    {
      digitalWrite(LED_PIN1,HIGH);
      digitalWrite(LED_PIN2,LOW);
    }
    if(force>500)
    {
      digitalWrite(LED_PIN1,LOW);
      digitalWrite(LED_PIN2,HIGH);
    }
  }  
  else
  {
    Serial.println("No resistance detected");
    digitalWrite(LED_PIN1,LOW);
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
