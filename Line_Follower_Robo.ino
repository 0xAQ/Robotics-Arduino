/*.....Defining INPUTS.....*/

#define LS 8         // Left sensor
#define RS 7         // Right sensor

/*.....Defining OUTPUTS.....*/

#define LMp 1       // Left motor
#define LMn 2       // Left motor
#define RMp 4       // Right motor
#define RMn 3       // Right motor

void setup()
{
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LMp, OUTPUT);
  pinMode(LMn, OUTPUT);
  pinMode(RMp, OUTPUT);
  pinMode(RMn, OUTPUT);
}

void loop()
{
  if(!(digitalRead(LS)) && !(digitalRead(RS)))  // Move FORWARD
  {
    digitalWrite(LMp, HIGH);
    digitalWrite(LMn, LOW);
    digitalWrite(RMp, LOW);
    digitalWrite(RMn, HIGH);
  }
  
  if(!(digitalRead(LS)) && digitalRead(RS))     // Turn LEFT
  {
    digitalWrite(LMp, LOW);
    digitalWrite(LMn, HIGH);
    digitalWrite(RMp, LOW);
    digitalWrite(RMn, HIGH);
  }
  
  if(digitalRead(LS) && !(digitalRead(RS)))     // Turn RIGHT
  {
    digitalWrite(LMp, HIGH);
    digitalWrite(LMn, LOW);
    digitalWrite(RMp, HIGH);
    digitalWrite(RMn, LOW);
  }
  
  if((digitalRead(LS)) && (digitalRead(RS)))    // STOP
  {
    digitalWrite(LMp, LOW);
    digitalWrite(LMn, LOW);
    digitalWrite(RMp, LOW);
    digitalWrite(RMn, LOW);
  }
}  
  
