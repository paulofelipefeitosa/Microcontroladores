#include <PID_v1.h>
unsigned long long int time1, time2;
volatile int state = 2;
int out;
double Setpoint = 25, Input, Output, Kp =10, Ki = 2, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);
void setup() 
{
  pinMode(12, OUTPUT);
  attachInterrupt(0, INTPT, FALLING);
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  Setpoint = 29;
  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);
  time2 = millis();
}
void loop() 
{
  Input = ((analogRead(A2)*5.00)/1023.00)*20.00;
  myPID.Compute();
  out = analogRead(A0)*6.90;
  analogWrite(3, Output);
  if(state==1)//UM PULSO DE SUBIDA, DESLIGA A CHAVE
  {
    digitalWrite(12, LOW);
    time1 = micros();
    state = 0;
  }
  else if(state==0)//UM PULSO DE DESCIDA, LIGA A CHAVE
  {
    if((micros()-time1)>=out)
    {
      digitalWrite(12, HIGH);
      delayMicroseconds(800);
      digitalWrite(12, LOW);
      state = 2;
      //time1 = micros();
    }
  }
  if(millis()-time2>=3000)
  {
    time2 = millis();
    Serial.print("Input: ");
    Serial.println(Input);
    Serial.print("Output: ");
    Serial.println(Output);
  }
}
void INTPT()
{
  state = 1;
}

