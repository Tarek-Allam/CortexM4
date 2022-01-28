#include <stdio.h>
#include <stdlib.h>
void displayBits (unsigned value);
int n;
int main(void)
{
unsigned int x;
unsigned char op;
printf( "Enter a hex value: " );
scanf( "%x", &x );
displayBits(x);
unsigned int y = ((x>>0)&0x01);
printf( "result: \n" );
displayBits(y);
printf("enter the number of shift \n");
scanf( "%d", &n );
int N = n%32;
printf("the shift direction \n");
scanf(" %c",&op);
switch(op)
{
             case '<' :  x= (x<<N); break;
             case '>' :  x=(x>>N);break;
             default :  printf("error");
}
displayBits(x);

  return 0;
}
/* display bits of an unsigned integer value */
void displayBits (unsigned int value)
{

  unsigned int mask= (1<<31);/*// generate bitmask for the integr 1 is left shift by 31*/
  /* loop for n bits */
  unsigned int c ; /*counter*/
  for(c=1;c<=32;c++)
  {
  putchar( value & mask ? '1' : '0' );
  /* shift the value by 1 or divide by 2 each time */
  value = value << 1;
  /* output space after 8 bits */
  if (c%8==0)
  {
    putchar(' ');
  } /* end for if */
}/*end for loop*/
  putchar('\n');

} /* end of the function displaybit */
