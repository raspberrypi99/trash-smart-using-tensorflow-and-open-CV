#include <AFMotor.h>
#include<Servo.h>
Servo name_servo;
const int trigPin = 6;
const int echoPin = 5;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  name_servo.attach (10);
  
  motor2.setSpeed(500);
  motor2.run(RELEASE);

  motor1.setSpeed(700);
  motor1.run(RELEASE);
}

void loop() {
  if(Serial.available()){
    blink(Serial.read() - '0');
  }
   delay(5000);
}

void blink(int numberOfTimes){
  while(numberOfTimes){
  digitalWrite(trigPin,LOW);
  delay(2000);

  digitalWrite(trigPin,HIGH);
  delay(5000);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distance = (duration*0.034/2)+1;

  if(distance <= 12 && distance<= 14){
    Serial.print("Distance: ");
    Serial.println(distance);
    delay(1000);

    name_servo.write(-60);             //servo arm opens
    delay(2000);
    
    motor1.run(FORWARD);
    delay(5800);
    motor1.run(RELEASE);
    delay(1000);
   
    motor2.run(BACKWARD);
    delay(4500);
    motor2.run(RELEASE);
    delay(1000);

    name_servo.write(60);              //servo arm picking object
    delay(2000);

   motor2.run(FORWARD);
   delay(3000);
   motor2.run(RELEASE);
   delay(1000);

   name_servo.write(-60);             
   delay(2000);

   motor1.run(BACKWARD);
   delay(4500);
   motor1.run(RELEASE);
   delay(1000);

   name_servo.write(60);              
   delay(2000);
  }

  else if(distance >=14 && distance < 23){
    Serial.print("Distance: ");
    Serial.println(distance);
    
    name_servo.write(-60);             //servo picks object2
    delay(1000);
   
    motor2.run(BACKWARD);               //frontarm moves forward
    delay(4500);
    motor2.run(RELEASE);

 
    name_servo.write(60);             //servo picks object2
    delay(1000);

    motor2.run(FORWARD);             //frontarm moves back
    delay(3000);
    motor2.run(RELEASE);

    name_servo.write(-60);             
    delay(2000);
                                     //servo arm drops object and closes
    name_servo.write(60);
    delay(2000);
  }
 else{
  Serial.print("Distance: ");
  Serial.println(distance);
 }
   }
}
