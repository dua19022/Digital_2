
#define BLUE PF_2
#define GREEN PF_3
#define RED PF_1
#define PUSH1 PF_4
#define PUSH2 PF_0
#define LED1 PD_0
#define LED2 PD_1
#define LED3 PD_2
#define LED4 PD_3
#define LED5 PE_1
#define LED6 PE_2
#define LED7 PE_3
#define LED8 PA_7

// Defino las variables
int lector1 = 0;
int lector2 = 0;
int counter = 0;
int push;

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
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  lector1 = digitalRead(PUSH1);
  lector2 = digitalRead(PUSH2);

  // Antirrebote
  if (lector1 == HIGH){
    push = 1;
  }

  if (lector1 == LOW && push == 1){
    digitalWrite(BLUE, HIGH);
    counter = counter + 1;
    push = 0;
  }
  else{
    digitalWrite(BLUE, LOW);
  }

  if (lector2 == HIGH){
    digitalWrite(GREEN, LOW);
  }
  else{
    digitalWrite(GREEN, HIGH);
  }

  if (counter == 1){
    digitalWrite(LED1, HIGH);
    //delay(250);
  }
  if(counter == 2){
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
    delay(100);
  }
  if(counter == 3){
    digitalWrite(LED3, HIGH);
    digitalWrite(LED2, LOW);
    delay(100);
  }
  if(counter == 4){
    digitalWrite(LED4, HIGH);
    digitalWrite(LED3, LOW);
    delay(100);
  }
  if(counter == 5){
    digitalWrite(LED5, HIGH);
    digitalWrite(LED4, LOW);
    delay(100);
  }
  if(counter == 6){
    digitalWrite(LED6, HIGH);
    digitalWrite(LED5, LOW);
    delay(100);
  }
  if(counter == 7){
    digitalWrite(LED7, HIGH);
    digitalWrite(LED6, LOW);
    delay(100);
  }
  if(counter == 8){
    digitalWrite(LED8, HIGH);
    digitalWrite(LED7, LOW);
    delay(100);
  }
  if(counter == 9){
    counter = 0;
    digitalWrite(LED8, LOW);
    delay(100);
  }

}
