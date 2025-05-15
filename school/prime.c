#include <stdio.h>

int main() {
  int notprime=0;
  int a=0, b=0, x=0;
  scanf("%d %d", &a, &b);
  for(int x=a; x<=b; x++) {
    notprime=0;
    for(int i=0; i<x; i++) {
      for(int j=i; j<x; j++) {
        if(j*i==x) {
          notprime=1;
          break;
        }
      }
      if(notprime) break;
    }
    if(!notprime)
      printf("%d is prime\n", x);
  }
  return 0;
}
