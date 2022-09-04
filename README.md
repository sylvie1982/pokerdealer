# pokerdealer
A poker card dealer that can use blooth to control
## Hardware
* Arduino Uno
* A breadboard
* Jump wires
* L298N Arduino medule
* CTRT5000(IR sensor)
* 3D printing model
* Stepper motor
* DC motor
* LED
* Buzzer
* BT05 bluetooth module
* A little tire
## Functions
* turning()<br>
Use turning function to determine the direction of dealing next poker card<br>
Idea:<br>
<img width="498" alt="image" src="https://user-images.githubusercontent.com/112713737/188296723-0ddfee96-c884-475e-b1f3-68775c4f1d09.png">

```
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

```
* dealer()<br>
Control the little tire to roll and slide down only one poker card
```
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
```
* main function
```
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
```
## Steps
1. Install "Serial Bluetooth Terminal" on device<br>![image](https://user-images.githubusercontent.com/112713737/188296529-fb450c5f-9ad6-4e15-88ba-a04fed8b0a43.png)
<br>
2. Connect to the pokerdealer<br>
3. Enter th number of players<br>
4. Start dealing!

## Demo video
https://youtu.be/ieziwGbhUMA
