#include <ESP32Servo.h>

#define IN1 26
#define IN2 16
#define IN3 13
#define IN4 14
#define EN_1 27
#define EN_2 33
#define SERVO_PIN 18
#define TRIG_PIN 5
#define ECHO_PIN 17 
#define garbage_trig 23
#define garbage_echo 34
#define garbage_open 21
#define pin 2



Servo detection ; 
Servo garbage;
int distance; 
int dis;
int network_status=false;
void setup() {
Serial.begin(115200);


ESP32PWM::allocateTimer(0);
ESP32PWM::allocateTimer(1);


detection.setPeriodHertz(50);
garbage.setPeriodHertz(50);
detection.attach(SERVO_PIN, 500, 2400);
garbage.attach(garbage_open, 500, 2400);

pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
pinMode(garbage_trig, OUTPUT);
pinMode(garbage_echo, INPUT);
ledcAttach(EN_1, 1000, 8);
ledcAttach(EN_2, 1000, 8);
delay(1000);
pinMode(pin , OUTPUT);
}

int getDistance() {
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);
long duration = pulseIn(ECHO_PIN, HIGH, 25000);
int distance = duration * 0.034 / 2;
if (distance <= 0 || distance > 400) return 999;
return distance;
}
int dete(){
digitalWrite(garbage_trig, LOW);
delayMicroseconds(2);
digitalWrite(garbage_trig, HIGH);
delayMicroseconds(10);
digitalWrite(garbage_trig, LOW);

long dur = pulseIn(garbage_echo, HIGH, 25000);
int dis = dur * 0.034 / 2;

if (dis <= 0 || dis > 400) return 999;
return dis;
}

void moveForward() {
ledcWrite(EN_1,150);
ledcWrite(EN_2,150);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}

void reverseBot() {
ledcWrite(EN_1,150);
ledcWrite(EN_2,150);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void turnLeft() {
ledcWrite(EN_1,225);
ledcWrite(EN_2,225);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
delay(500);}

void turnRight() {
ledcWrite(EN_1,225);
ledcWrite(EN_2,225);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
delay(500); 
}

void stopBot() {
ledcWrite(EN_1,0);
ledcWrite(EN_2,0);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}

int scanDirection(int angle) {
detection.write(angle);
delay(500);
return getDistance();
}

void loop() {
int dis=dete();
distance = getDistance();
Serial.print("Distance: ");
Serial.println(distance);
Serial.println("garbage_detection");
Serial.print(dis);


if (distance <= (50 +random(1,20))){
Serial.println("work");
stopBot();
delay(300);
reverseBot();
delay(900);
stopBot();
delay(5000);
dis=dete();
delay(5000);
if(dis <= random(5,10)){
delay(5000);
for(int x = 0;x <= 140; x+=2){
garbage.write(x);
 delay(random(10,20));
}
delay(random(1000,5000));
delay(3000);
garbage.write(0);
digitalWrite(pin ,HIGH);
delay(3000);


}


int distLeft = 0;
int distRight = 0;
if (random(0, 2) == 0) {
distLeft = scanDirection(180);
distRight = scanDirection(0);
} else {
distRight = scanDirection(180);
distLeft = scanDirection(0);
}

detection.write(90); 
delay(300);
Serial.println("Left");
Serial.println(distLeft);
Serial.println("Right");
Serial.println(distRight);
if (distLeft >= distRight ){
turnLeft();Serial.println("Left");
delay(250); 
} else {
turnRight();Serial.println("Right");
delay(250); 
}
stopBot(); 
delay(200); 
} else {
moveForward(); 
}
delay(400);
if (Serial.available()) {
 char cmd = Serial.read();

 if (cmd == 'r') {
Serial.println("Reverse");
stopBot();
reverseBot();
delay(2000);
}
else if (cmd == 'f') {
Serial.println("Forward");
moveForward();
}
else if (cmd == 's') {
Serial.println("Stop");
stopBot();
delay(20000);
}else if (cmd == 't') {
Serial.println("Stop");
turnRight();
delay(20000);
}else if (cmd == 'l') {
Serial.println("Stop");
turnLeft();
delay(20000);
}
Serial.println("stuheheheuhodhodhoh");
} 
}