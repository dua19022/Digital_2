
#define BLUE PF_2
#define GREEN PF_3
#define RED PF_1
#define PUSH1 PF_4
#define PUSH2 PF_0

//Se definen las leds del jugador 1
#define LED1 PD_0
#define LED2 PD_1
#define LED3 PD_2
#define LED4 PD_3
#define LED5 PE_1
#define LED6 PE_2
#define LED7 PE_3
#define LED8 PA_7

// Se definen las leds del jugador 2
#define LED9 PB_3
#define LED10 PC_4
#define LED11 PC_5
#define LED12 PC_6
#define LED13 PC_7
#define LED14 PD_6
#define LED15 PD_7
#define LED16 PA_2

// Defino las variables
int lector1 = 0;
int lector2 = 0;
int counter = 0;
int counter1 = 0;
int push;
int push1;
int activator1, activator2;

void setup() {
  // put your setup code here, to run once:
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  pinMode(LED10, OUTPUT);
  pinMode(LED11, OUTPUT);
  pinMode(LED12, OUTPUT);
  pinMode(LED13, OUTPUT);
  pinMode(LED14, OUTPUT);
  pinMode(LED15, OUTPUT);
  pinMode(LED16, OUTPUT);
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly: 
  lector1 = digitalRead(PUSH1);
  lector2 = digitalRead(PUSH2);

  // Antirrebote
  if (lector1 == HIGH){
    push = 1;
  }
  if (lector2 == HIGH){
    push1 = 1;
  }

  if (counter == 1 || counter1 == 1){
    digitalWrite(RED, HIGH);
    delay(1500);
    digitalWrite(GREEN, HIGH);
    delay(1500);
    digitalWrite(RED, LOW);
    delay(1500);
    digitalWrite(GREEN, LOW);
    counter = 2;
    counter1 = 2;
  }
    
  if (lector1 == LOW && push == 1){
    counter = counter + 1;
    push = 0;
  }

  if (lector2 == LOW && push1 == 1){
    counter1 = counter1 + 1;
    push1 = 0;
  }

  // Jugador 1
  if (counter == 3){
    digitalWrite(LED1, HIGH);
    //delay(250);
  }
  if(counter == 4){
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
    delay(100);
  }
  if(counter == 5){
    digitalWrite(LED3, HIGH);
    digitalWrite(LED2, LOW);
    delay(100);
  }
  if(counter == 6){
    digitalWrite(LED4, HIGH);
    digitalWrite(LED3, LOW);
    delay(100);
  }
  if(counter == 7){
    digitalWrite(LED5, HIGH);
    digitalWrite(LED4, LOW);
    delay(100);
  }
  if(counter == 8){
    digitalWrite(LED6, HIGH);
    digitalWrite(LED5, LOW);
    delay(100);
  }
  if(counter == 9){
    digitalWrite(LED7, HIGH);
    digitalWrite(LED6, LOW);
    delay(100);
  }
  if(counter == 10){
    digitalWrite(LED8, HIGH);
    digitalWrite(LED7, LOW);
    delay(100);
  }
  if(counter == 11){
    counter = 0;
    digitalWrite(LED8, LOW);
    delay(100);
  }

  //Jugador 2
  if (counter1 == 3){
    digitalWrite(LED9, HIGH);
    //delay(250);
  }
  if(counter1 == 4){
    digitalWrite(LED10, HIGH);
    digitalWrite(LED9, LOW);
    delay(100);
  }
  if(counter1 == 5){
    digitalWrite(LED11, HIGH);
    digitalWrite(LED10, LOW);
    delay(100);
  }
  if(counter1 == 6){
    digitalWrite(LED12, HIGH);
    digitalWrite(LED11, LOW);
    delay(100);
  }
  if(counter1 == 7){
    digitalWrite(LED13, HIGH);
    digitalWrite(LED12, LOW);
    delay(100);
  }
  if(counter1 == 8){
    digitalWrite(LED14, HIGH);
    digitalWrite(LED13, LOW);
    delay(100);
  }
  if(counter1 == 9){
    digitalWrite(LED15, HIGH);
    digitalWrite(LED14, LOW);
    delay(100);
  }
  if(counter1 == 10){
    digitalWrite(LED16, HIGH);
    digitalWrite(LED15, LOW);
    delay(100);
  }
  if(counter1 == 11){
    counter1 = 0;
    digitalWrite(LED16, LOW);
    delay(100);
  }

// Rutinas para ver quien gana
  if (counter == 10){ // Si gana el jugador 1
    digitalWrite(BLUE, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, LOW);
    digitalWrite(LED10, LOW);
    digitalWrite(LED11, LOW);
    digitalWrite(LED12, LOW);
    digitalWrite(LED13, LOW);
    digitalWrite(LED14, LOW);
    digitalWrite(LED15, LOW);
    digitalWrite(LED16, LOW);
    counter = 0;
    counter1 = 0;
    delay(1000);
    digitalWrite(BLUE, LOW);
  }
  if (counter1 == 10){  // Si gana el jugador 2
    digitalWrite(GREEN, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    digitalWrite(LED6, LOW);
    digitalWrite(LED7, LOW);
    digitalWrite(LED8, LOW);
    digitalWrite(LED9, LOW);
    digitalWrite(LED10, LOW);
    digitalWrite(LED11, LOW);
    digitalWrite(LED12, LOW);
    digitalWrite(LED13, LOW);
    digitalWrite(LED14, LOW);
    digitalWrite(LED15, LOW);
    digitalWrite(LED16, LOW);
    counter1 = 0;
    counter = 0;
    delay(1000);
    digitalWrite(GREEN, LOW);
  }
  
}
