#define SOBRE (1 << 5)//PINO 5
#define SUB (1 << 4)//PINO 4
#define CONTATOR (1 << 5)//PINO 13
#define CORRENTE (1 << 0)//PINO A0
#define StandardTime 1000

volatile int state = 0;
bool status = false;
unsigned long time1, time2;

void setup()
{
  DDRB |= CONTATOR;
  DDRD &= ~SOBRE;
  DDRD &= ~SUB;
  DDRC &= ~CORRENTE;
  attachInterrupt(1, SOB_SUB_TENSAO, RISING);//PINO 3
  attachInterrupt(0, FALTADEFASE, FALLING);//PINO 2
  Serial.begin(9600);
  time1 = millis();
}

void loop()
{
  if(!state)//HABILITAR TUDO NA PRIMEIRA PASSAGEM
  {
    if(!status)
    {
      noInterrupts();
      PORTB |= CONTATOR;
      delay(100);
      interrupts();
      status = true;
    }
    else
    {
      time2 = millis();
      if(time2 - time1 >= StandardTime)
      {
        time1 = millis();
        Serial.println("NOTHING HAPPENING!");
      }
    }
  }
  else if(state==1)
    Serial.println("ATENCAO! SOBRETENSAO!");
  else if(state==2)
    Serial.println("ATENCAO! SUBTENSAO!");
  else if(state==3)
      Serial.println("ATENCAO! FALTA DE FASE!");
}

void SOB_SUB_TENSAO()  //DESLIGA TUDO
{
  if(PIND & SOBRE)
    state = 1;
  else if(PIND & SUB)
    state = 2;
  PORTB &= ~CONTATOR;
}

void FALTADEFASE()  //DESLIGA TUDO
{
  state = 3;
  PORTB &= ~CONTATOR;
}
