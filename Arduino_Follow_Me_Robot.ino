//include the library code:
#include<NewPing.h>           
#include<Servo.h>             
#include<AFMotor.h>           

#define RIGHT A2              // Kanan IR ke A2
#define LEFT A3               // kiri IR ke A3
#define TRIGGER_PIN A1        // Trigger ultrasonic ke A1
#define ECHO_PIN A0           // Echo ultrasonic ke A0
#define MAX_DISTANCE 200      // Maximum jarak

unsigned int distance = 0;    
unsigned int Right_Value = 0; 
unsigned int Left_Value = 0;  
  

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 


AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

 Servo myservo; 
 int pos=0;     

void setup() { 
  
   Serial.begin(9600); 
   myservo.attach(10); 
{
for(pos = 90; pos <= 180; pos += 1){    // pergerakan servo dari 90 ke 180 derajat
  myservo.write(pos);                   //servo bergerak sesuai nilai pos
  delay(15);                            
  } 
for(pos = 180; pos >= 0; pos-= 1) {     //pergerakan servo dari 180 ke 0 derajat
  myservo.write(pos);                   //servo bergerak sesuai nilai pos
  delay(15);                           
  }
for(pos = 0; pos<=90; pos += 1) {       //pergerakan servo dari 0 ke 90 derajat
  myservo.write(pos);                   //servo bergerak sesuai nilai pos
  delay(15);                            
  }
}
   pinMode(RIGHT, INPUT); 
   pinMode(LEFT, INPUT);  
}

// the lope function runs forever
void loop() {                             
  
delay(50);                                        
distance = sonar.ping_cm();                       //setting distance ke cm
Serial.print("distance");                   
Serial.println(distance);                         // serial print menampilkan distance


    Right_Value = digitalRead(RIGHT);             
    Left_Value = digitalRead(LEFT);              
 
Serial.print("RIGHT");                      
Serial.println(Right_Value);                      // print IR sensor ke serial print
Serial.print("LEFT");                       
Serial.println(Left_Value);                       //print IR kiri ke serial monitor:

if((distance > 1) && (distance < 15)){            //check jangkauan ultrasonik tetap di 1-15
                                                  //jika masuk di if
  //Maju ke depan:
  Motor1.setSpeed(130);  //speed motor 1
  Motor1.run(FORWARD);   //motor berputar seaarah jarum jam
  Motor2.setSpeed(130);  //speed motor 2
  Motor2.run(FORWARD);   //motor berputar seaarah jarum jam
  Motor3.setSpeed(130);  //speed motor 3
  Motor3.run(FORWARD);   //motor berputar seaarah jarum jam
  Motor4.setSpeed(130);  //speed motor 4
  Motor4.run(FORWARD);   //motor berputar seaarah jarum jam
  
}else if((Right_Value==0) && (Left_Value==1)) {   //ngecek infrared kanan 0 kiri 1
  
  //belok kiri                                                
  Motor1.setSpeed(150);  //speed motor 1
  Motor1.run(FORWARD);   //motor berputar seaarah jarum jam
  Motor2.setSpeed(150);  //speed motor 2
  Motor2.run(FORWARD);   //motor berputar seaarah jarum jam
  Motor3.setSpeed(150);  //speed motor 3
  Motor3.run(BACKWARD);  //motor berputar seaarah jarum jam
  Motor4.setSpeed(150);  //speed motor 3
  Motor4.run(BACKWARD);  //motor berputar seaarah jarum jam
  delay(150);
  
}else if((Right_Value==1)&&(Left_Value==0)) {     //ngecek infrared kanan 1 kiri 0
  
  //belok kanan
  Motor1.setSpeed(150);  //speed motor 1
  Motor1.run(BACKWARD);  //putar motor berlawan jarum jam
  Motor2.setSpeed(150);  //speed motor 2
  Motor2.run(BACKWARD);  //putar motor berlawan jarum jam
  Motor3.setSpeed(150);  //speed motor 3
  Motor3.run(FORWARD);   //putar motor berlawan jarum jam
  Motor4.setSpeed(150);  //speed motor 4
  Motor4.run(FORWARD);   //putar motor berlawan jarum jam
  delay(150);
  
}else if(distance > 15) {                          //jika jarak lebih dari 15 maka
  
  //Stop
  Motor1.setSpeed(0);    //speed motor 1
  Motor1.run(RELEASE);   //stop motor1:
  Motor2.setSpeed(0);    //speed motor 2
  Motor2.run(RELEASE);   //stop motor2:
  Motor3.setSpeed(0);    //speed motor 3
  Motor3.run(RELEASE);   //stop motor3:
  Motor4.setSpeed(0);    //speed motor 4
  Motor4.run(RELEASE);   //stop motor4:
}
}
