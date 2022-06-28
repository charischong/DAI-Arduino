#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

const int FSR_PIN = A0; // Pin connected to FSR/resistor divider
const int LED_PIN1 = 7;
//const int LED_PIN2 = 6;
//const int LED_PIN3 = 4;
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor

void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN, INPUT);
  pinMode(LED_PIN1, OUTPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
//  pinMode(LED_PIN2, OUTPUT);
//  pinMode(LED_PIN3, OUTPUT);
}

void loop() 
{
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
//      digitalWrite(LED_PIN2,LOW);
//      digitalWrite(LED_PIN3,LOW);}
//    if(force>20)
//    {
//      digitalWrite(LED_PIN1,HIGH);
//      digitalWrite(LED_PIN2,LOW);
//      digitalWrite(LED_PIN3,LOW);
//     
//    }
//    if(force>100)
//    {
//      digitalWrite(LED_PIN2,HIGH);
//      digitalWrite(LED_PIN1,LOW);
//      digitalWrite(LED_PIN3,LOW);
//    }
//    if(force>1000)
//    {
//      digitalWrite(LED_PIN3,HIGH);
//      digitalWrite(LED_PIN2,LOW);
//      digitalWrite(LED_PIN1,LOW);
//    }
//  
    delay(500);
    }
    
  }
  else
  {
    Serial.println("No resistance detected");
    digitalWrite(LED_PIN1,LOW);
  }

  for (pos = 45; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 45; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to posit ion in variable 'pos'
    delay(10);                       // waits 15ms for the servo to reach the position
  }
}
