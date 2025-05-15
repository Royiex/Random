#include <stdio.h>

int main() {
  int a=0, b=0, y=0;
  scanf("%d %d", &a, &b);
  for(int x=a; x<=b; x++) {
    y=0;
    for(int i=1; i<x; i++) {
      if(x%i==0) y+=i;
    }
    if(x==y) printf("%d is perfect\n", x);
  }
  return 0;
}
