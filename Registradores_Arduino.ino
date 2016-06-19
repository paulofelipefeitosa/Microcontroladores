unsigned long time1, time2;
volatile int state = 0;
#define LED3 (1 << 7)
ISR(PCINT0_vect);
void setup() 
{
  cli();
  /* Equivalente a
    pinMode(12, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
  */
  DDRB &= ~( (1 << DDB4) | (1 << DDB3) | (1 << DDB2) );
  PORTB |= ( (1 << PORTB4) | (1 << PORTB3) | (1 << PORTB2) );
 
  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  PCMSK0 |= ( (1 << PCINT4) | (1 << PCINT3) | (1 << PCINT2) );
 
  sei();
  //DDRD |= LED;
  //DDRD |= LED2;
  DDRD &= ~LED3;
  //PORTD |= (1 << PORTD7);
  //DDRD |= LED4;
  /* Equivalente:
  pinMode(9,OUTPUT);
  pinMode(9,INPUT);
  */
  //DDRB |= (1 << DDB1);
  //DDRB &= ~(1 << DDB1);
  Serial.begin(9600);
  time1 = millis();
}

void loop() 
{
  time2 = millis();
  if(time2 - time1 >= 2000)
  {
    time1 = millis();
    PORTD = (PIND & LED3)?(Serial.println("Ligado")):(Serial.println("Desligado"));
    Serial.print("Estado: ");
    Serial.println(state);
  }
  /* Equivalente:
  digitalWrite(9,LOW);
  */
  //PORTB &= ~(1 << PORTB1);
  
  /* Equivalente:
  pinMode(9,INPUT);
  digitalWrite(9,HIGH); //Nesse contexto, ativa o pull-up interno.
  bool x = digitalRead(9);
  */ 
  //DDRB &= ~(1 << DDB1);
  //PORTB |= (1 << PORTB1);
  //bool x = (PINB & (1 << PINB1));
  
}

volatile uint8_t last_PINB = PINB;
 
/* Função de Tratamento de Interrupção */
ISR(PCINT0_vect) 
{
  uint8_t changed_bits;
  changed_bits = PINB ^ last_PINB;
  last_PINB = PINB;
 
  if (changed_bits & (1 << PINB4))
  {
    if (PINB & (1 << PINB4)) 
    {
      // D12 mudou de LOW para HIGH;
      state = !state;
    }
    else 
    {
      // D12 mudou de HIGH para LOW;
      state = !state;
    }
  }
  else if (changed_bits & (1 << PINB3))
  {
    if (PINB & (1 << PINB3)) 
    {
      // D11 mudou de LOW para HIGH;
      state = !state;
    }
    else 
    {
      // D11 mudou de HIGH para LOW;
      state = !state;
    }
  }
  else if (changed_bits & (1 << PINB2))
  {
    if (PINB & (1 << PINB2)) 
    {
      // D10 mudou de LOW para HIGH;
      state = !state;
    }
    else 
    {
      // D10 mudou de HIGH para LOW;
      state = !state;
    }
  }
}
