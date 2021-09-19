
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
int outPins[8] = {LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8};

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

  int i = 0;
  int j = 0;
  if (digitalRead(PUSH1) == LOW) {
    for (i = 0; i < 255; i++) {
      for (j = 0; j < 8; j++) {

        if ( ((i >> j) & 1 )  == 1)  {
          digitalWrite(outPins[j], HIGH);

        }
        else {
          digitalWrite(outPins[j], LOW);
        }

      }
      delay(250);
    }
  }

}
