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
