#include <stdio.h>
#include <stdlib.h>

long long int factor(long long int n)
{
  if (n <= 0)
  {
    return 1;
  }
  else
  {
    return n*factor(n - 1);
  }
}


int main(void)
{
  long long int val = 20;
  long long int fact = 0;

  fact = factor(val);

  printf("%lld! = %lld.\n", val, fact);

  system("pause");

  _asm
  {
    mov EAX, 1
  }

	return 0;
}