#include <LiquidCrystal.h>
#include <Servo.h>

Servo servo_shoulder;
Servo servo_elbow;
Servo servo_z;

const double length1 = 14.0;
const double length2 = 16.0;
const double total_distance = 452.0;

const int ini = 0;
const int fin = 0;

byte package_received[5];

byte x;
byte y;
byte z;

double A_actual;
double B_actual;
double A_previous;
double B_previous;

void setup() {
  Serial.begin(9600);
  servo_shoulder.attach(5);
  servo_elbow.attach(6);
  servo_z.attach(3);
  servo_z.write(0);
  servo_shoulder.write(0);
  servo_elbow.write(90);
  for(int i=0; i<5; i++)
    package_received[i]=-1;
  x=0;
  y=0;
  z=1;
  A_previous=0;
  B_previous=80;
}

bool valid_package(byte package_received[5]){
  return package_received[0]==ini && package_received[1]!=-1 && package_received[2]!=-1 && package_received[3]!=-1 && package_received[4]==fin; 
}

void loop() {  
int i=0;
   while(Serial.available()){
     package_received[i] = Serial.read();
     i++;
   }
  
  if(valid_package(package_received)){
   y = package_received[1];
   x = package_received[2];
   z = package_received[3];
   
   double cosB = ((double)y*(double)y+(double)x*(double)x-total_distance)/total_distance;
   double B_radians = acos(cosB);
   double A_radians = atan((double)y/(double)x)-atan(length2*sin(B_radians)/(length1+length2*cos(B_radians)));
   double B_degrees = B_radians*RAD_TO_DEG;
   double A_degrees = A_radians*RAD_TO_DEG;
   
    if(z==1){
      servo_z.write(0);
      delay(100);
    }

    if(A_degrees<175 && B_degrees<175){
      servo_shoulder.write(A_degrees+70);
      delay(50);
      servo_elbow.write(B_degrees);
      delay(200);
      servo_z.write(15);
    }  
  }
  delay(80);
  
  for(int i=0; i<5; i++)
    package_received[i]=-1;
  
}
