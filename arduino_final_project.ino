#include <Stepper.h>
#include <SoftwareSerial.h>

//wheel setting
int deal1 = 11;

//turning setting
Stepper stepper(2048, 4, 12, 5, 13);
//int turn_cclockwise = 9; int turn_clockwise = 10;

//bluetooth setting
SoftwareSerial BT(2, 3);
char val;
int num;
int c = 15;
bool start = false, d = false;

//sound and light effect
int buzzer = 7, LED = 8;

// IR setting
int IR = 6;

void setup()
{
  pinMode (LED, OUTPUT); pinMode (buzzer, OUTPUT);
  pinMode (deal1, OUTPUT); pinMode (deal2, OUTPUT);
  stepper.setSpeed(12);
  //pinMode (turn_clockwise, OUTPUT); pinMode(turn_cclockwise, OUTPUT);
  BT.begin(9600); Serial.begin(9600);
}

void loop(){
  if (BT.available()){
    val = BT.read();
    start = true;
  }
  if (start){
    num = val - '0';
    if (num > 0) {
      turning(num);
      light(num);
      buzz();
      start = false;
    }
  }
}

//function
void dealer()
{
  int IRState = digitalRead(IR);
  if (IRState == 0) {
    analogWrite (deal1, 255);
  } else {
    analogWrite (deal1, 0);
    d = true;
  }
}

void turning(int n)
{
  int s, i = 1, j = 1;
  if (i <= (c / n))
  {
    for (j = 1; j <= n , i <= (c / n);)
    {
      dealer();
      if (d) {
        if (i % 2 == 1 && j != n) {
          s = 1024 / (n - 1);
          j++;
        } else if (i % 2 == 0 && j != 1) {
          s = -1024 / (n - 1);
          j--;
        } else if (i % 2 == 1 && j == n) {
          s = 0;
          i++;
        } else if (i % 2 == 0 && j == 1) {
          s = 0;
          i++;
        }
        stepper.step(s);
        delay(250);
        d = false;
      }
    }
  }
  if (c % n > 0)
  {
    for (int k=1 ; k <= (c % n);)
    {
      dealer();
      if (d) {
        if ((c / n) % 2 == 0) {
          s = 1024 / (n - 1);
        }else{
          s = -1024 / (n - 1);
        }
        k++;
        stepper.step(s);
        delay(250);
        d = false;
      }
    }
  }
}

void light(int m)
{
  for (; m > 0; m--)
  {
    digitalWrite(LED, 1); delay(250);
    digitalWrite(LED, 0); delay(250);
  }
}
void buzz()
{
  digitalWrite(buzzer, 1); delay(100);
  digitalWrite(buzzer, 0); delay(50);
  digitalWrite(buzzer, 1); delay(100);
  digitalWrite(buzzer, 0); delay(50);
}
