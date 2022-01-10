#include<stdio.h>
#include<conio.h>
int main(void){
    char p[20];
    int i;
  for (i = 0;; i++)
 {
  p[i] = getch();
  switch (p[i])
  {
  case '\b':
   p[--i] = '\0';
   i--;
   printf("\b \b");
   break;
  case '\r':
   p[i] = '\0';
   putchar('\n');
   break;
  default:
   putchar('*');
   break;
  }
  if (p[i] == '\0') break;
 }
 return 0;
}
