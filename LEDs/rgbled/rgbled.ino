/* RGB LED firefly
 
 Vladimir Malyarevich, 2015

*/


//constants
int RedPin=0;
int GreenPin=1;
int BluePin=2;

//variable
char red_b=0, green_b, blue_b; //PWM buffers
volatile char count=0; //PWM counter

void setup() {
  
  noInterrupts();
  
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  
  //set timer0 interrupt at 2kHz
  TCCR0A |= 0b10;
  TCCR0B = 4;
  TCNT0 = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  interrupts(); //allows interrupts globally
}

ISR(TIM0_COMPA_vect) {
  digitalWrite(RedPin, count<red_b);
  digitalWrite(GreenPin, count<green_b); 
  digitalWrite(BluePin, count<blue_b);
  count++;  
}

void change_color(char to_red, char to_green, char to_blue, char pause) {
    while(red_b!=to_red||green_b!=to_green||blue_b!=to_blue){
        if(to_red!=red_b)
            if(to_red>red_b)red_b++;
            else red_b--;
        if(to_green!=green_b)
            if(to_green>green_b)green_b++;
            else green_b--;
        if(to_blue!=blue_b)
            if(to_blue>blue_b)blue_b++;
            else blue_b--;
        if(pause)delay(pause);
    } 
}

void loop() {
  randomSeed(analogRead(4)); //Shuffle random function with nose from unused port
  change_color(random(25),100,200,20);
}
