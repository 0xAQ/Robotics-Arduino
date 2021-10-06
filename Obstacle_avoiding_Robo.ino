#include <Servo.h>

/*.....Defining UltraSonic.....*/

#define Trigger 4
#define Echo    4

/*.....Defining OUTPUTS.....*/

#define LMp 13       //  Left motor
#define LMn 12       //  Left motor
#define RMp 8        // Right motor
#define RMn 9        // Right motor
#define SM  6        // Servo motor

int pos = 0;
int distance = 0;
Servo myservo;


void setup()
{
  Serial.begin(9600);
  
  pinMode(LMp, OUTPUT);
  pinMode(LMn, OUTPUT);
  pinMode(RMp, OUTPUT);
  pinMode(RMn, OUTPUT);

  myservo.attach(6, 500, 2500);
  for (pos = 0; pos <= 90; pos += 1) {        //ultrasonic is facing 
    myservo.write(pos);                       //straight
   	delay(5);
  }
  delay(500);
}  

int getDistance()
{
int distance;
unsigned long pulseduration=0;
pinMode(Trigger, OUTPUT);
digitalWrite(Trigger, LOW);
delayMicroseconds(5);
digitalWrite(Trigger, HIGH);
delayMicroseconds(5);
digitalWrite(Trigger, LOW);
  
pinMode(Echo, INPUT);
pulseduration=pulseIn(Echo, HIGH);
pulseduration=pulseduration/29;

distance = int(pulseduration/2);
return distance;
}

void loop()
{
  int Rdistance, Ldistance;
  
  distance = int (getDistance());
  Serial.print(distance);
  Serial.println(" cm");
  delay(500);
  
  if (distance > 20){
    Serial.println("Moving Forward");
  	while(distance >20 ) {
    
    	Forward();
    	distance=getDistance();
  
  	}
  }   
  if (distance <= 20){
    
    Serial.println("STOP");
    Stop();
    delay(500);
    Reverse();
    delay(1000);
    Stop();
    
    /*.....Looking Left And Taking Reading.....*/
    
    for (pos = 90; pos <= 180; pos += 1) {
      myservo.write(pos);
      delay(15); 
    }
    delay(2000);
    
    Ldistance = int (getDistance());
    delay(100);
    Serial.print("Left side distance = ");
    Serial.print(Ldistance);
    Serial.println(" cm");

    /*.....Back to Intial Position.....*/

    for (pos = 180; pos >= 90; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    delay(1000);

    /*.....Looking Right And Taking Reading.....*/

    for (pos = 90; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    delay(2000);
    
    Rdistance = int (getDistance());
    delay(100);
    Serial.print("Right side distance = ");
    Serial.print(Rdistance);
    Serial.println(" cm");

    /*.....Back to Intial Position.....*/

    for (pos = 0; pos <= 90; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    delay(1000);

    /*.....Left or Right or (⊙_⊙)？.....*/

   if ((Ldistance | Rdistance) >= 50){              //limiting value
      
      if (Rdistance >= Ldistance){

        Serial.println("Taking Right Turn");
        while(distance <= Rdistance){              //to get accurate results
          RightTurn();                             //And to avoid delay function
          distance = getDistance();
        }
      }
      else {

        Serial.println("Taking Left Turn");
        while (distance <= Ldistance){             //Same
          LeftTurn();
          distance = getDistance();
        }
      }
    }

  else {
      Serial.println("Taking U turn until distance >= 50");
    
      while ( distance <= 50){
        
        distance = getDistance();
    
        digitalWrite(LMp, HIGH);
        digitalWrite(LMn, LOW);              //same as turn right but turns unit the 
        digitalWrite(RMp, HIGH);             //condition is achieved 
        digitalWrite(RMn, LOW);      
      }  
    }
  } 
}
      
void Forward(){
  
  digitalWrite(LMp, HIGH);
  digitalWrite(LMn, LOW);
  digitalWrite(RMp, LOW);
  digitalWrite(RMn, HIGH);
}   
    
void RightTurn(){ 
     
  digitalWrite(LMp, HIGH);
  digitalWrite(LMn, LOW);             
  digitalWrite(RMp, HIGH);            
  digitalWrite(RMn, LOW);    
}

void LeftTurn(){

  digitalWrite(LMp, LOW);
  digitalWrite(LMn, HIGH);
  digitalWrite(RMp, LOW);
  digitalWrite(RMn, HIGH);
}

void Reverse(){

  digitalWrite(LMp, LOW);
  digitalWrite(LMn, HIGH);
  digitalWrite(RMp, HIGH);
  digitalWrite(RMn, LOW);
}

void Stop(){

  digitalWrite(LMp, LOW);
  digitalWrite(LMn, LOW);
  digitalWrite(RMp, LOW);
  digitalWrite(RMn, LOW);
}

             /*..............Thank you.............*/







