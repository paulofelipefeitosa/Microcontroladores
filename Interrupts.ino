#define LED (1 << 5)
void setup() {
  cli();
 
  /* Equivalente a
    pinMode(12, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
  */
  DDRD |= LED;
  DDRB &= ~( (1 << DDB4) | (1 << DDB3) | (1 << DDB2) );
  PORTB |= ( (1 << PORTB4) | (1 << PORTB3) | (1 << PORTB2) );// Liga Pull-up;
 
  // Seta as "chaves" necessárias para que as interrupções cheguem ao vetor;
  PCICR |= (1 << PCIE0);
  PCMSK0 |= ( (1 << PCINT4) | (1 << PCINT3) | (1 << PCINT2) );
 
  sei();
}
 
void loop() 
{
  //...
}
 
// Variáveis globais que são acessadas por interrupções devem ser declaradas volatile;
volatile uint8_t last_PINB = PINB;
 
/* Função de Tratamento de Interrupção */
ISR(PCINT0_vect) {
  uint8_t changed_bits;
  changed_bits = PINB ^ last_PINB;
  last_PINB = PINB;
 
  if (changed_bits & (1 << PINB4))
  {
    if (PINB & (1 << PINB4)) 
    {
      PORTD |= LED;
      // D12 mudou de LOW para HIGH;
    }
    else 
    {
      PORTD &= ~LED;
      // D12 mudou de HIGH para LOW;
    }
  }
  else if (changed_bits & (1 << PINB3))
  {
    if (PINB & (1 << PINB3)) {
      // D11 mudou de LOW para HIGH;
    }
    else {
      // D11 mudou de HIGH para LOW;
    }
  }
  else if (changed_bits & (1 << PINB2))
  {
    if (PINB & (1 << PINB2)) {
      // D10 mudou de LOW para HIGH;
    }
    else {
      // D10 mudou de HIGH para LOW;
    }
  }
}
